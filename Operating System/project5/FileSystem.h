#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string.h>
#include <string>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <block.c>

#define BlockSize 1024
#define BlockNum 256000 
#define InodeNum  1000
#define SYSTEM_NAME "simulated_device"

using namespace std;

typedef struct{
	unsigned short blockSize;
	unsigned int blockNum;//the number of file blocks
	unsigned int inodeNum;
	unsigned int blockFree;
}SuperBlock;

//100B
typedef struct{
	unsigned int id;//4B
	char name[30];//30B
	bool isDir;//1B 0-file 1-dir
	unsigned int parent;//4B
	unsigned int length;//4B
	unsigned int addr[13];//48B
	unsigned int blockId;//4B
	//int link;
}Inode,*PInode;

typedef struct{
	unsigned int id;	//4B
	char name[30];	//30B
	bool isDir; 	//1B
	unsigned int blockId;	//4B,the begin of fcb block
}Fcb,*PFcb;


typedef struct FCB_LINK_NODE{
	Fcb fcb;
	struct FCB_LINK_NODE *next;
}FcbLinkNode,*FcbLink;


#define MAX_OPEN_FILE 10
typedef struct user{
	unsigned int user_fd[MAX_OPEN_FILE];
	int OpenFileNum;

}User;
/*
#define dirTable_max_size 15
typedef struct dirTable{
	int dirUnitAmount;
	Fcb dirs[dirTable_max_size];
}dirTable;
*/
class FileSystem
{
public:
	FileSystem();
	virtual ~FileSystem();

	int init();
	void my_mkfs();
	void openFileSystem();
	int cd(char* name);

	//file operation
	int createFile(char*name,bool isDir);
	int my_read(int fd,void* buf,int count);
	int write(unsigned int fd);
	int del(char *name);
	int my_rename(char* name,char*newName);
	int my_open(char* name);
	int my_mkdir(char* path);
	int my_creat(char* path);
	int my_write(int fd,void* buf,int count);
	int my_close(int fd);
	int my_remove(char* path);
	int my_rmdir(char* path);
	//int test(int argc,char** argv);
	//static int test_file (char * path, char * buffer, int size, int max_size);
	//static void close_remove_file (char * path, int fd);
protected:
private:
	char name[30];
	bool *blockBitmap;
	bool *inodeBitmap;

	//size
	unsigned short superBlockSize;
	unsigned short blockBitmapSize;
	unsigned short inodeBitmapSize;
	unsigned short inodeSize;
	unsigned short fcbSize;
	unsigned short itemSize;

	//bias
	//unsigned long sbOffset;	//superBlock bias
	unsigned long bbOffset;	//blockBitmap bias
	unsigned long ibOffset;	//inodeBitmap bias
	unsigned long iOffset;	//the inode bias
	unsigned long bOffset;	//data area bias


	SuperBlock superBlock;
	string curPath;	//the filesystem block information
	Inode curInode;
	FcbLink curLink;	//the current file link 
	User user;


	FILE* fp;
	//superBlock
	void getSuperBlock(SuperBlock *pSuper);
	void updateSuperBlock(SuperBlock super);

	//blockBitmap
	unsigned int getAvailableBlockId();
	void getBlockBitmap(bool *bitmap);
	void updateBlockBitmap(bool* bitmap, unsigned int index);
    void updateBlockBitmap(bool* bitmap, unsigned int start, unsigned int count);

    //inodebitmap
    unsigned int getAvailableInodeId();
    void getInodeBitmap(bool *bitmap);
    void updateInodeBitmap(bool* bitmap, unsigned int index);
    void updateInodeBitmap(bool* bitmap, unsigned int start, unsigned int count);


    //inode block区域操作
    void getInode(PInode pInode, unsigned int id);
    void updateInode(Inode inode);
    void releaseInode(unsigned int id);

	//data block
	//index or file 
    unsigned int getAvailableFileItem(Inode& inode, unsigned int* availableIndex);
    unsigned int getItem(unsigned int blockId, unsigned int index);
    void updateItem(unsigned int blockId, unsigned int index, unsigned int value);
    void releaseItem(unsigned int blockId, unsigned int id);

    //the file context
    int getData(unsigned int blockId,char* buff,unsigned int size,unsigned int offset);
    int writeData(unsigned int blockId,void* buff,unsigned int size,unsigned int offset);
    void releaseBlock(unsigned int blockId);

    unsigned int findChildInode(FcbLink curLink,char *name);

    //Fcblink
    void getFcbLinkNode(FcbLink curLink,Inode inode);
    void getFcbLink(FcbLink& curLink,Inode inode);	//creat the directory information link
    void appendFcbLinkNode(FcbLink curLink, Inode inode);
    void removeFcbLinkNode(FcbLink curLink,Inode inode);
    void removeFcbLinkNode(FcbLink curLink,char* name);
    void releaseFcbLink(FcbLink &curLink);

    int findPath(char* path);
};
#endif  //FILESYSTEM_H 
