#include <iostream>
#include <string.h>
#include <stdlib.h>
#define N 1001
void SubSet(int n ,int a[N],int cur);
void print_subset(int n,int a[N],int cur,int tmp);
int cmp(const void *a,const void *b);
void print(int n,int a[N]);
void subset_print(int n,int s,int a[N]);

using namespace std;

int b[N];

int main()
{
    int n,a[N];
    cout<<"please input the size of number:"<<endl;
    cin>>n;
    memset(b,0,sizeof(b));
    //for(int i=1;i<=n;i++) cin>>a[i];
    //qsort(a+1,n,sizeof(int),cmp);
    for(int i=1;i<=n;i++) cin>>a[i];
    SubSet(n,a,0);
    //print_subset(n,a,1,1);
    //print(n,a);
    return 0;
}

int cmp(const void *a,const void *b)
{
    return *(int*)a-*(int*)b;
}


//bfs
void SubSet(int n ,int a[N],int cur)
{
    if(cur==n)
    {
        for(int i=1;i<=n;i++)
        {
            if(b[i]==1) cout<<a[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        if(cur!=0 && a[cur+1]==a[cur])
        {
            if(b[cur]==1)
            {
                b[cur+1]=0;
                SubSet(n,a,cur+1);
                b[cur+1]=1;
                SubSet(n,a,cur+1);
            }
            else{
            b[cur+1]=0;
            SubSet(n,a,cur+1);}
        }
        else{
        b[cur+1]=1;
        SubSet(n,a,cur+1);
        b[cur+1]=0;
        SubSet(n,a,cur+1);}
    }
}

//int max=a>b?a:b;
//增量构造法
void print_subset(int n,int a[N],int cur,int tmp)
{
    for(int i=1;i<cur;i++)
    {
        cout<<b[i]<<" ";
        if(i==cur-1) cout<<endl;
    }
    //int s=cur?cur:1;
    for(int i=tmp;i<=n;i++)
    {
        b[cur]=a[i];
        print_subset(n,a,cur+1,i+1);
    }
}



//二进制法
void print(int n,int a[N])
{
    for(int i=0;i<((1<<n)-1);i++)
        subset_print(n,i,a);
}

void subset_print(int n,int s,int a[N])
{
    for(int i=0;i<n;i++)
        if(s&(1<<i)) cout<<a[i];
    cout<<endl;
}
