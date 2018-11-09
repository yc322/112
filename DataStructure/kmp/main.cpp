#include <iostream>

using namespace std;
int KMP(char *str,int slen,char*ptr,int plen);
void cal_next(char *str,int *next,int len);

int main()
{
    char *str = "bacbababadababacambabacaddababacasdsd";
    char *ptr = "ababaca";
    int a = KMP(str, 36, ptr, 7);
    cout<<a<<endl;
    return 0;
}

int KMP(char *str,int slen,char*ptr,int plen)
{
    int *next=new int[plen];
    cal_next(ptr,next,plen);
    int k=-1; // k is the length that matching
    for(int i=0;i<slen;i++) //the index of the str
    {
        while(k>-1 && ptr[k+1]!=str[i]) k=next[k]; //move the ptr
        if(ptr[k+1]==str[i]) k++;
        if(k==plen-1) return i-plen+1; //find the index of substring
    }
    return -1;//not find the substring
}

void cal_next(char *str,int *next,int len)
{
    next[0]=-1;
    int k=-1;
    for(int q=1;q<=len-1;q++)
    {
        while(k>-1 && str[k+1]!=str[q])
        {
            k=next[k]; //if not the same compare the next[next[j]]
        }
        if(str[k+1]==str[q]) k++;//the same the length++
        next[q]=k;
    }
}

