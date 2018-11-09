#include <iostream>
#include <stdlib.h>
#define N 101

using namespace std;

int cmp(const void* a,const void *b);
int  find_sum(int a[N],int n,int *res);

int main()
{
    int n,a[N];
    cout<<"please input the sizeof numebr:"<<endl;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    qsort(a,n,sizeof(int),cmp);
    int flag;
    int res;
    flag=find_sum(a,n,&res);
    if(flag==1) cout<<res<<endl;
    else cout<<"can't find the number"<<endl;
    for(int i=0;i<n;i++) cout<<a[i]<<" ";

    return 0;
}

int cmp(const void* a,const void *b)
{
    return (*(int*)a-*(int*)b);
}


int  find_sum(int a[N],int n,int *res)
{
    int flag=0;
    int left,right;
    for(int i=n-1;i>=1;i--)
    {
        left=0;
        right=i-1;
        while(left<=right)
        {
            if(a[left]+a[right]==a[i])
            {
                flag=1;
                *res=a[i];
                return flag;
            }
            else if(a[left]+a[right]>a[i]) right--;
            else left++;
        }
    }
    return flag;
}

