#include "FileSystem.h"

using namespace std;

//superBlock
void FileSystem::getSuperBlock(SuperBlock *pSuper){
	if(fp==NULL || pSuper==NULL){
		return ;
	}
	fseek(fp,0,SEEK_SET);
	fread(pSuper,superBlockSize,1,fp);
}

void FileSystem::updateSuperBlock(SuperBlock super){
	if(fp==NULL){
		return;
	}
	fseek(fp,0,SEEK_SET);
	fwrite(&super,superBlockSize,1,fp);
}

//blockImage
//find a unused data block 0->root,return >0 is find
unsigned int FileSystem::getAvailableBlockId(){
	if(superBlock.blockFree <=0){
		cout<<"no free block"<<endl;
		return 0;
	}
	for(int i=0;i<BlockNum;i++){
		if(blockBitmap[i]==false){
			cout<<"find block "<<i<<endl;
			releaseBlock(i);
			return i;
		}
	}
	cout<<"no free block"<<endl;
	return 0;
}


void FileSystem::releaseBlock(unsigned int blockId)
{
	fseek(fp,bOffset+BlockSize*blockId,SEEK_SET);
	for(int i=0;i<BlockSize;i++){
		fputc(0,fp);
	}
	cout<<"release block"<<blockId<<endl;

}

void FileSystem::updateBlockBitmap(bool *bitmap,unsigned int index){
	this->updateBlockBitmap(bitmap,index,1);
}

void FileSystem::updateBlockBitmap(bool* bitmap,unsigned int start,unsigned count){
	if(fp==NULL){
		return;
	}
	fseek(fp,bbOffset+start,SEEK_SET);
	fwrite(bitmap+start,count,1,fp);
}

//inodeImage
//find unused inode
unsigned int FileSystem::getAvailableInodeId(){
	for(unsigned int i=0;i<BlockNum;i++){
		if(inodeBitmap[i]==false){
			//inodeBitmap[i]=true;
			cout<<"find inode "<<i<<endl;
			return i;
		}
	}
	return 0;
}

void FileSystem::updateInodeBitmap(bool *bitmap,unsigned int index){
	this->updateBlockBitmap(bitmap,index,1);
}

void FileSystem::updateInodeBitmap(bool* bitmap,unsigned int start,unsigned count){
	if(fp==NULL){
		return;
	}
	fseek(fp,ibOffset+start,SEEK_SET);
	fwrite(bitmap+start,count,1,fp);
}


void FileSystem::getInode(PInode pInode,unsigned int id)
{
	if(fp == NULL || pInode==NULL) return ;
	fseek(fp,iOffset+inodeSize * id,SEEK_SET);
	fread(pInode,inodeSize,1,fp);
}

void FileSystem::updateInode(Inode inode){
	if(fp==NULL) return ;
	fseek(fp,iOffset +inodeSize * inode.id,SEEK_SET);
	fwrite(&inode,inodeSize,1,fp);
}

void FileSystem::releaseInode(unsigned int id){
	if(fp==NULL) return;
	fseek(fp,iOffset +inodeSize*id,SEEK_SET);
	for(int i=0;i<inodeSize;i++){
		fputc(0,fp);
	}
}

void FileSystem::updateItem(unsigned int blockId,unsigned int index,unsigned int value){
	if(fp==NULL){
		return ;
	}
	fseek(fp,bOffset+blockId*BlockSize+itemSize*index,SEEK_SET);
	fwrite(&value,itemSize,1,fp);

}


unsigned int FileSystem::getItem(unsigned int blockId,unsigned int index)
{
	unsigned int value=0;
	if(fp==NULL){
		return value;
	}
	fseek(fp,bOffset+BlockSize*blockId+itemSize*index,SEEK_SET);
	fread(&value,itemSize,1,fp);
	return value;
}

void FileSystem::releaseItem(unsigned int blockId,unsigned int id)
{
	int itemTotal=BlockSize/itemSize;
	unsigned int itemId;
	fseek(fp,bOffset+BlockSize*blockId,SEEK_SET);
	for(int i=0;i<itemTotal;i++){
		printf("release item id=%d in %d\n",id,blockId);
		fseek(fp,-itemSize,SEEK_CUR);
		itemId=0;
		fwrite(&itemId,itemSize,1,fp);
		return ;
	}
}
unsigned int FileSystem::getAvailableFileItem(Inode& inode,unsigned int *availableIndex)
{
	unsigned int index;
	unsigned int blockId;
	unsigned int fileItem;
	Inode fileInode;
	const int itemTotal=BlockSize/itemSize;
	for(int i=0;i<11;i++){
		blockId=inode.addr[i];
		cout<<"in addr["<<i<<"]"<<"blockId is"<<blockId<<endl;
		if(blockId >0 ){
			cout<<"the direct data block exit"<<endl;
			for(index=0;index<itemTotal;index++){
				fileItem=getItem(blockId,index);
				cout<<"Index "<<index<<"fileItem is "<<fileItem<<endl;
				if(fileItem==0){
					*availableIndex=index;
					return blockId;
				}
			}
		}
		else{
			blockId = getAvailableBlockId();
			cout<<"getAvailableBlockId"<<blockId<<endl;
            if(blockId > 0) {
                superBlock.blockFree--;
                updateSuperBlock(superBlock);
                blockBitmap[blockId] = 1;
                updateBlockBitmap(blockBitmap, blockId);
                inode.addr[i] = blockId;
                updateInode(inode);
                *availableIndex = 0;
                return blockId;
            }
            else{
            	return 0;
            }
		}

	}

}


int FileSystem::getData(unsigned int blockId,char* buff,unsigned int size,unsigned int offset)
{
	int len=0;
	if(buff==NULL || offset >= BlockSize){
		return len;
	}
	fseek(fp,bOffset+BlockSize*blockId,SEEK_SET);
	if(size > BlockSize-offset) size=BlockSize-offset;
	len=fread(buff,size,1,fp);
	return len;
}


FileSystem::FileSystem()
{
	fp=NULL;
	curLink=NULL;
	blockBitmap=new bool[BlockNum+1];
	inodeBitmap=new bool[InodeNum+1];
	superBlockSize = sizeof(SuperBlock);
	inodeSize=sizeof(Inode);
	fcbSize = sizeof(Fcb);
	itemSize=sizeof(unsigned int);
	blockBitmapSize=BlockNum;
	inodeBitmapSize=BlockNum;

	strcpy(this->name,SYSTEM_NAME);

	bbOffset=sizeof(SuperBlock);
	ibOffset=bbOffset+blockBitmapSize;
	iOffset=ibOffset + inodeBitmapSize;
	bOffset=iOffset + sizeof(Inode)*InodeNum;
}

//fcblink
void FileSystem::getFcbLinkNode(FcbLink pNode,Inode inode)
{
	if(pNode==NULL) return ;
	pNode->fcb.id=inode.id;
	strcpy(pNode->fcb.name,inode.name);
	pNode->fcb.isDir=inode.isDir;
	pNode->fcb.blockId=inode.blockId;
	pNode->next=NULL;
}



void FileSystem::getFcbLink(FcbLink &curLink,Inode inode)
{
	if(curLink !=NULL){
		releaseFcbLink(curLink);
	}
	//cout<<"myoutput<< start read dir self inode"<<endl;
	curLink=new FcbLinkNode;
	getFcbLinkNode(curLink,inode);
	//cout<<"myoutput<< end read dir self inode"<<endl;
	if(inode.length<=0){
		return ;
	}	
}

void FileSystem::removeFcbLinkNode(FcbLink curLink,Inode inode)
{
	if(curLink==NULL || inode.id<0) return ;
	FcbLink link=curLink->next;
	FcbLink temp=curLink;
	while(link!=NULL){
		if(link->fcb.id==inode.id){
			temp->next=link->next;
			delete link;
			break;
		}
		temp=link;
		link=link->next;

	}
}

void removeFcbLinkNode(FcbLink curLink,char* name)
{
	if(curLink==NULL || name==NULL) return ;
	FcbLink link=curLink->next;
	FcbLink temp=curLink;
	while(link!=NULL){
		if(strcmp(link->fcb.name,name)==0){
			temp->next=link->next;
			delete link;
			break;
		}
		temp=link;
		link=link->next;
	}
}

void FileSystem::releaseFcbLink(FcbLink &curLink)
{
	FcbLink link=curLink;
	FcbLink temp;
	while(link != NULL){
		temp=link->next;
		delete link;
		link=temp;
	}
	curLink=NULL;
}

void FileSystem::appendFcbLinkNode(FcbLink curLink,Inode inode)
{
	if(curLink==NULL || inode.id<=0) return ;
	FcbLink link=curLink;
	while(link->next!=NULL){
		link=link->next;
	}
	FcbLink pNode=new FcbLinkNode();
	getFcbLinkNode(pNode,inode);
	link->next=pNode;
}


FileSystem::~FileSystem()
{
	if(blockBitmap != NULL){
		delete blockBitmap;
		blockBitmap=NULL;
	}
	if(inodeBitmap !=NULL){
		delete inodeBitmap;
		inodeBitmap=NULL;
	}
	if(curLink!=NULL){
		releaseFcbLink(curLink);
	}
}
/*
int FileSystem::init()
{
	openFileSystem();
	return 0;
}
*/
void FileSystem::my_mkfs()
{
	cout<<"create file system...\n";
	if((fp=fopen(name,"wb+"))==NULL){
		cout<<"open file error"<<endl;

	}
	//init superBlock
	superBlock.blockSize=BlockSize;
	superBlock.blockNum=BlockNum;
	superBlock.inodeNum=1;
	superBlock.blockFree = BlockNum-1;
	updateSuperBlock(superBlock);
	cout<<"myoutput<<free block num:"<<superBlock.blockFree<<endl;
	blockBitmap[0]=1;
	inodeBitmap[0]=1;
	unsigned long i;
	for(i=1;i<BlockNum;i++){
		blockBitmap[i]=false;
		//inodeBitmap[i]=false;
	}
	for(i=1;i<InodeNum;i++){
		inodeBitmap[i]=false;
	}
	updateBlockBitmap(blockBitmap,0,blockBitmapSize);
	updateInodeBitmap(inodeBitmap,0,inodeBitmapSize);

	//init inode and block
	long len=0;
	len +=inodeSize*InodeNum+BlockSize*BlockNum;
	for(i=0;i<len;i++){
		fputc(0,fp);
	}

	curInode.id=0;
	strcpy(curInode.name,"/");
	curInode.isDir=1;
	curInode.parent=inodeSize;	//root not need parent
	curInode.length=0;
	for(i=0;i<12;i++){
		curInode.addr[i]=0;
	}
	curInode.blockId=0;
	updateInode(curInode);
	fflush(fp);
	getFcbLink(curLink,curInode);
	user.OpenFileNum=0;
	curPath="/";
	printf("create file system %s finish.\n",this->name);
}

unsigned int FileSystem::findChildInode(FcbLink curLink,char *name)
{
	if(curLink==NULL || name==NULL) return 0;
	FcbLink temp=curLink->next;
	Fcb cur_fcb;
	while(temp!=NULL){
		cur_fcb=temp->fcb;
		cout<<"fcb.name"<<cur_fcb.name<<endl;
		if(strcmp(cur_fcb.name,name)==0){
			return cur_fcb.id;
		}
		temp=temp->next;
	}
	return 0;
}


int FileSystem::cd(char* name){
	cout<<"cd from"<<curInode.name<<"to child"<<name<<endl;
	unsigned int id;
	id=findChildInode(curLink,name);
	if(id > 0){
		getInode(&curInode,id);
		getFcbLink(curLink,curInode);
		curPath.append(name);
		curPath.append(1,'/');
		return 0;
	}
	else{
		cout<<"no such file or directory"<<endl;
		return -1;
	}
}

int FileSystem::my_rename(char* name ,char* newname)
{
	unsigned int id=findChildInode(curLink,name);
	printf("rename file %s in %s to %s\n",name,curInode.name,newname);
	if(id >0){
		Inode inode;
		getInode(&inode,id);
		strcpy(inode.name,newname);
		updateInode(inode);
		FcbLink link=curLink->next;
		while(link!=NULL){
			if(strcmp(link->fcb.name,name)==0){
				strcpy(link->fcb.name,newname);
				return 0;
			}
			link=link->next;
		}
	}
	else{
		cout<<"no such file or directory"<<name<<endl;
		return -1;
	}

}

int FileSystem::findPath(char* path)
{
	int count=0;
	int index=0;
	for(int i=0;i<strlen(path);i++){
		if(path[i]=='/') {
			count++;
			index=i;
		}
	}
	char* filepath;
	for(int i=0;i<index;i++){
		filepath[i]=path[i];
	}
	if(count>1){
		unsigned int temp=findChildInode(curLink,filepath);
		if (temp==0) {
			printf("the path %s no exist!\n",filepath);
			return -1;
		}
		else{
			getInode(&curInode,temp);
		}
	}
	else{
		getInode(&curInode,0);
	}
	return 1;
}


int FileSystem::my_mkdir(char* name)
{
	int flag=findPath(name);
	if(flag==-1) {
		printf("can't create a directory!\n");
		return -1;
	}
	int res=createFile(name,0);
	return res;
}

int FileSystem::my_create(char* name)
{
	int flag=findPath(name);
	if(flag==-1) {
		printf("can't create a directory!\n");
		return -1;
	}
	int res=createFile(name,1);
	return res;
}


int FileSystem::createFile(char* name ,bool isDir)
{
	if(name==NULL || strcmp(name,"")==0 || findChildInode(curLink,name)>0){
		cout<<"invalid file name : the name is empty,or the file has existed"<<endl;
		return -1;
	}
	printf("create file %s(isDir=%d) in %s\n",name,isDir,curInode.name);
	unsigned int index;
	cout<<"myoutput<<getAvailableFileItem"<<endl;
	unsigned int dirBlockId = getAvailableFileItem(curInode,&index);

	if(dirBlockId >0 || curInode.id==0){
		unsigned int blockId=getAvailableBlockId();
		if(blockId>0){
			superBlock.blockFree--;
			superBlock.inodeNum++;
			blockBitmap[blockId]=true;
			updateBlockBitmap(blockBitmap,blockId);
			cout<<"myoutput<<getAvailableInodeId"<<endl;
			unsigned int id = getAvailableInodeId();
			PInode pInode =new Inode();
			pInode->id=id;
			strcpy(pInode->name,name);
			pInode->isDir = isDir;
			pInode->parent = curInode.id;
			pInode->length=0;
			pInode->addr[0]=blockId;
			for(int i=1;i<12;i++) pInode->addr[i]=0;
			pInode->blockId=dirBlockId;
			updateInode(*pInode);
			inodeBitmap[id]=true;
			updateInodeBitmap(inodeBitmap,id);
			printf("myoutput<< %d register in dir %d [%d]\n",id,dirBlockId,index);
			updateItem(dirBlockId,index,id);
			curInode.length++;
			updateInode(curInode);
			appendFcbLinkNode(curLink ,*pInode);
			cout<<"delete pInode"<<endl;
			delete pInode;
			return 0;

		}
		else{
			cout<<"myoutput<<storage space is not enough"<<blockId<<endl;
			return -1;
		}
	}	
	else{
		cout<<"myoutput<<the directory can't append file item"<<dirBlockId<<endl;
		return -1;
	}
}


int FileSystem::del(char* name)
{
	cout<<"delete file "<<name<<" in "<<curInode.name<<endl;
	unsigned int id=findChildInode(curLink,name);
	if(id > 0){
		PInode pInode=new Inode();
		getInode(pInode,id);
		if(pInode->isDir==0){
			unsigned int blockId;
			for(int i=0;i<11;i++){
				blockId=pInode->addr[i];
				if(blockId>0){
					superBlock.blockFree++;
					updateSuperBlock(superBlock);
					releaseBlock(blockId);
					blockBitmap[blockId]=false;
					updateBlockBitmap(blockBitmap,blockId);
				}
			}
			releaseInode(pInode->id);
			superBlock.inodeNum--;
			updateSuperBlock(superBlock);
			inodeBitmap[pInode->id]=false;
			updateInodeBitmap(inodeBitmap,pInode->id);
			
		}
		else{
			/*
			cd(name);
			FcbLink link=curLink->next;
			while(link!=NULL){
				del(link->fcb.name);
				link=link->nextl
			}
			*/
			for(int i = 0; i < 11; i++)
            {
                unsigned int blockId = pInode->addr[i];
                if(blockId > 0)
                {
                    //更新superBlock
                    superBlock.blockFree++;
                    updateSuperBlock(superBlock);
                    //释放block
                    releaseBlock(blockId);
                    //更新blockBitmap
                    blockBitmap[blockId] = 0;
                    updateBlockBitmap(blockBitmap, blockId);
                }
            }
             //释放i节点
            releaseInode(pInode->id);
            //更新superBlock
            superBlock.inodeNum--;
            updateSuperBlock(superBlock);
            //更新inodeBitmap
            inodeBitmap[pInode->id] = false;
            updateInodeBitmap(inodeBitmap, pInode->id);
            //释放目录文件项
            releaseItem(pInode->blockId, pInode->id);
            printf("delete dir %s\n", pInode->name);
		}
		curInode.length--;
		updateInode(curInode);
		removeFcbLinkNode(curLink,*pInode);
		delete pInode;
		return 0;
	}	
	else{
		cout<<"myoutput<<no such file or directory"<<endl;
		return -1;
	}
}

int FileSystem::my_open(char*name)
{
	unsigned int id=findChildInode(curLink,name);

	if(id>0){
		PInode pInode=new Inode();
		getInode(pInode,id);
		if(pInode->isDir!=0){
			printf("is a directory\n");
			return -1;
		}
		if(user.OpenFileNum>=MAX_OPEN_FILE){
			cout<<"the max open file num is "<<MAX_OPEN_FILE<<endl;
			cout<<"can't open a new file!"<<endl;
			return -1;
		}
		user.user_fd[user.OpenFileNum]=id;
		user.OpenFileNum++;
		return id;
	}
	printf("no file name %s\n",name);
	return -1;
}

int FileSystem::my_close(int fd)
{
	for(int i=0;i<MAX_OPEN_FILE;i++){
		if(user.user_fd[i]==fd){
			user_fd[i]=0;
			return 1;
		}
	}
	return 0;
}

int FileSystem::my_read(int fd,void* buf,int count)
{
	bool flag=false;
	int len=count;
	int read_size;
	int num=0;
	for(int i=0;i<MAX_OPEN_FILE;i++){
		if(user.user_fd[i]==fd){
			flag=true;
			PInode pInode=new Inode();
			getInode(pInode,fd);

			//unsigned long len=pInode->length;
			char *buff=new char[BlockSize+1];
			int i;
			unsigned int blockId;
			
			for(i=0;i<11;i++){
				blockId=pInode->addr[i];
				printf("read blockId %d\n",blockId);

				if(blockId>0){
					if(len>BlockSize){
						read_size=BlockSize;
						len-=getData(blockId,buff,BlockSize,0);
						printf("%s\n",buff);
						for(int i=0;i<strlen(buff),i++){
							(char*)buf[num*blockSize+i]=buff[i];
						}
						memset(buff,0,sizeof(buff));

					}
					
					else{
						read_size=len;
						printf("read_size=%d\n",read_size);
						len-=getData(blockId,buff,read_size,0);
						printf("%s\n",buff);
						for(int i=0;i<strlen(buff),i++){
							(char*)buf[num*blockSize+i]=buff[i];
						}
						delete buff;
						return count;
					}
				}
				else{
					printf("\n");
					delete buff;
					return count-len;
				}
			}
			if(len<=0){
				printf("\n");
				delete buff;
				return 0;
			}
		}
	}
	if(flag=false){
		cout<<"fd "<<fd<<"is not open"<<endl;
		return -1;
	}
}


int FileSystem::writeData(unsigned int blockId,void* buff,unsigned int size,unsigned int offset)
{
	int len=0;
	if(buff==NULL || offset >= BlockSize) return len;
	fseek(fp,bOffset+BlockSize*blockId,SEEK_SET);
	if(size > BlockSize-offset) size=BlockSize-offset;
	len=fwrite(buff,size,1,fp);
	return len;
}


int FileSystem::my_write(int fd,void* buff,int count)
{
	unsigned long len=0;//the total write size
	int num=count;
	int write_size;
	PInode pInode = new Inode();
	getInode(pInode,fd);
	//char* buff=new char[BlockSize+1];
	//char* buff="hello  world";
	unsigned int blockId;
	for(int i=0;i<12;i++){
		if(num > BlockSize){
			write_size=BlockSize;
			blockId=pInode->addr[i];
			if(blockId>0){
				writeData(blockId,buff,write_size,0);
				num-=BlockSize;
				len+=BlockSize;
				
			}
			else{
				blockId=getAvailableBlockId();
				if(blockId>0){
					superBlock.blockFree--;
					updateSuperBlock(superBlock);
					blockBitmap[blockId]=1;
					pInode->length=BlockSize;
					updateInode(*pInode);
					writeData(blockId,buff,write_size,0);
					num-=BlockSize;
					len+=BlockSize;	
				}
			}
		}
		else{
			write_size=num;
			blockId=pInode->addr[i];
			if(blockId>0){
				writeData(blockId,buff,write_size,0);
				len+=num;
				printf("write_size=%d\n",write_size);
				pInode->length=len;
				updateInode(*pInode);
				//delete buff;
				return len;
			}
			else{
				blockId=getAvailableBlockId();
				if(blockId>0){
					superBlock.blockFree--;
					updateSuperBlock(superBlock);
					blockBitmap[blockId]=1;
					//updateInode(*pInode);
					printf("write_size is %d\n",write_size);
					writeData(blockId,buff,write_size,0);
					len+=num;
					pInode->length=len;
					updateInode(*pInode);
					delete buff;
					return len;
				}
			}

		}
	}
}