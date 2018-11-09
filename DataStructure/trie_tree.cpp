#include<iostream>
#include<cstring>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/*******************************
*输入数据的第一部分是一张单词表,
每行一个单词,单词的长度不超过10,
它们代表的是老师交给Ignatius统计
的单词,一个空行代表单词表的结束.
第二部分是一连串的提问,每行一个
提问,每个提问都是一个字符串.
对于每个提问,给出以该字符串为前
缀的单词的数量.
Sample Input
banana
band
bee
absolute
acm

ba
b
band
abc


Sample Output
2
3
1
0
*******************************/

/*
typedef struct Trie_node
{
	int count;                    // 统计单词前缀出现的次数
	struct Trie_node* next[26];   // 指向各个子树的指针
	bool exist;                   // 标记该结点处是否构成单词
}TrieNode , *Trie;

TrieNode* createTrieNode()
{
	TrieNode* node = (TrieNode *)malloc(sizeof(TrieNode));
	node->count = 0;
	node->exist = false;
	memset(node->next , 0 , sizeof(node->next));    // 初始化为空指针
	return node;
}

void Trie_insert(Trie root, char* word)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		if(node->next[id] == NULL)
		{
			node->next[id] = createTrieNode();
		}
		node = node->next[id];  // 每插入一步，相当于有一个新串经过，指针向下移动
		++p;
		node->count += 1;      // 这行代码用于统计每个单词前缀出现的次数（也包括统计每个单词出现的次数）
	}
	node->exist = true;        // 单词结束的地方标记此处可以构成一个单词
}

int Trie_search(Trie root, char* word)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		node = node->next[id];
		++p;
		if(node == NULL)
			return 0;
	}
	return node->count;
}

int main(void)
{
    Trie root = createTrieNode();     // 初始化字典树的根节点
    char str[12] ;
	bool flag = false;
	while(gets(str))
	{
		if(flag)
			printf("%d\n",Trie_search(root , str));
		else
		{
			if(strlen(str) != 0)
			{
				Trie_insert(root , str);
			}
			else
				flag = true;
		}
	}

    return 0;
}
*/


















/**********************************************
http://acm.hdu.edu.cn/showproblem.php?pid=1075

The problem has only one test case,
the test case consists of two parts,
the dictionary part and the book part.
The dictionary part starts with a
single line contains a string "START",
this string should be ignored, then some
lines follow, each line contains two
strings, the first one is a word in English,
the second one is the corresponding word
in Martian's language. A line with a single
string "END" indicates the end of the directory
part, and this string should be ignored. The
book part starts with a single line contains
a string "START", this string should be ignored,
then an article written in Martian's language.
 You should translate the article into English
 with the dictionary. If you find the word in the
 dictionary you should translate it and write
 the new word into your translation, if you can't
 find the word in the dictionary you do not have
 to translate it, and just copy the old word to
 your translation. Space(' '), tab('\t'), enter('\n')
  and all the punctuation should not be translated.
  A line with a single string "END" indicates the
  end of the book part, and that's also the end of
  the input. All the words are in the lowercase,
and each word will contain at most 10 characters,
and each line will contain at most 3000 characters.
************************************************************/
#include<iostream>
#include<cstring>
using namespace std;

typedef struct Trie_node
{
	int count;                    // 统计单词前缀出现的次数
	struct Trie_node* next[26];   // 指向各个子树的指针
	bool exist;                   // 标记该结点处是否构成单词
	char trans[11];               // 翻译
}TrieNode , *Trie;

TrieNode* createTrieNode()
{
	TrieNode* node = (TrieNode *)malloc(sizeof(TrieNode));
	node->count = 0;
	node->exist = false;
	memset(node->next , 0 , sizeof(node->next));    // 初始化为空指针
	return node;
}

void Trie_insert(Trie root, char* word , char* trans)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		if(node->next[id] == NULL)
		{
			node->next[id] = createTrieNode();
		}
		node = node->next[id];  // 每插入一步，相当于有一个新串经过，指针向下移动
		++p;
		node->count += 1;      // 这行代码用于统计每个单词前缀出现的次数（也包括统计每个单词出现的次数）
	}
	node->exist = true;        // 单词结束的地方标记此处可以构成一个单词
	strcpy(node->trans , trans);
}

char* Trie_search(Trie root, char* word)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		node = node->next[id];
		++p;
		if(node == NULL)
			return 0;
	}
	if(node->exist)          // 查找成功
		return node->trans;
	else                     // 查找失败
		return NULL;
}

int main(void)
{
    Trie root = createTrieNode();     // 初始化字典树的根节点
    char str1[3003] , str2[3003] , str[3003] , *p;
	int i , k;

	scanf("%s",str1);
	while(scanf("%s",str1) && strcmp(str1 , "END") != 0)
	{
		scanf("%s",str2);
		Trie_insert(root , str2 , str1);
	}
	getchar();
	gets(str1);
	k = 0;
	while(gets(str1))
	{
		if(strcmp(str1 , "END") == 0)
			break;
		for(i = 0 ; str1[i] != '\0' ; ++i)
		{
			if(str1[i] >= 'a' && str1[i] <= 'z')
			{
				str[k++] = str1[i];
			}
			else
			{
				str[k] = '\0';
				p = Trie_search(root , str);
				if(p)
					printf("%s", p);
				else
					printf("%s", str);
				k = 0;
				printf("%c", str1[i]);
			}
		}
		printf("\n");
	}

    return 0;
}
