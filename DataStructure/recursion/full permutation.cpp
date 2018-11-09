#include <iostream>
#define Maxsize 100
#include <string.h>

using namespace std;

int vis[Maxsize];
int element[Maxsize];
void Per(int c,int num);


int main()
{
    int num;
    cout<<"please input num"<<endl;
    cin>>num;
    memset(vis,0,sizeof(vis));
    /*for(int i=0;i<num;i++)
    {
        element[i]=i;
        vis[i]=0;
    }*/
    Per(1,num+1);
    return 0;
}

void Per(int c,int num)
{
    if(c==num)
    {
        for(int i=1;i<num;i++)
            cout<<element[i]<<" ";
        cout<<endl;
    }
    else
    {
        for(int i=1;i<num;i++)
        {
            if(vis[i]==0)
            {
                vis[i]=1;
                element[c]=i;
                Per(c+1,num);
                vis[i]=0;
            }
        }
    }
}
