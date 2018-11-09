#include <iostream>
#include <set>

using namespace std;
int search();
int Init();
int find(int num);
int sign(int num);
void display(int num);
void Next(int num);
void merge(int a[9],int p,int q,int r);
void merge_sort(int a[9],int p,int r);

typedef struct node
{
    int pos[3][3];
    int bef;
}node;

node state[400000];
int global_count;
int count;
set<int> vis;

int main()
{
    count=0;
    vis.clear();
    int flag=Init();
    if(flag==1) search();
    return 0;
}


int  Init()
{
    int flag=0;
    cout<<"Please input the initial state:"<<endl;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        cin>>state[1].pos[i][j];
    vis.insert(sign(1));
    state[1].bef=-1;
    cout<<"please input the final state:"<<endl;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        cin>>state[0].pos[i][j];
    int temp1[9];
    int temp2[9];
    int count1,count2;
    int b=1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
          {if(state[1].pos[i][j]!=0){temp1[b]=state[1].pos[i][j];b++;}}
    }
    b=1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
          {if(state[0].pos[i][j]!=0){temp2[b]=state[0].pos[i][j];b++;}}
    }
    global_count=0;
    merge_sort(temp1,1,8);
    count1=global_count;
    global_count=0;
    merge_sort(temp2,1,8);
    count2=global_count;
    if(count1%2==count2%2) {cout<<"have result"<<endl;flag=1;}
    else {cout<<"unsolvable"<<endl;}
    count=count+2;
    return flag;
}

//find the position of 0
int find(int num)
{
    int i;
    for(i=0;i<9;i++)
    {
        if(state[num].pos[i/3][i%3]==0)
        return i;
    }
    return -1;
}

//create a sign for every states
int sign(int num)
{
    int res=state[num].pos[0][0]*100000000+state[num].pos[0][1]*10000000+state[num].pos[0][2]*1000000+state[num].pos[1][0]*100000+state[num].pos[1][1]*10000+state[num].pos[1][2]*1000+state[num].pos[2][0]*100+state[num].pos[2][1]*10+state[num].pos[2][2];
    return res;
}


void Next(int num)
{
    int loc=find(num);
    int d[][2]={{-1,0},{1,0},{0,-1},{0,1}};
    for(int i=0;i<4;i++){
        state[count]=state[num];
        if(i==0 && loc/3!=0)swap(state[count].pos[loc/3][loc%3],state[count].pos[loc/3+d[0][0]][loc%3+d[0][1]]);
        if(i==1 && loc/3!=2)swap(state[count].pos[loc/3][loc%3],state[count].pos[loc/3+d[1][0]][loc%3+d[1][1]]);
        if(i==2 && loc%3!=0)swap(state[count].pos[loc/3][loc%3],state[count].pos[loc/3+d[2][0]][loc%3+d[2][1]]);
        if(i==3 && loc%3!=2)swap(state[count].pos[loc/3][loc%3],state[count].pos[loc/3+d[3][0]][loc%3+d[3][1]]);
        state[count].bef=num;
        if(vis.find(sign(count))==vis.end()){
            vis.insert(sign(count));
            count++;
        }
    }
}

void merge_sort(int a[9],int p,int r)
{
    int q;
    if(p<r){
        q=(p+r)/2;
        merge_sort(a,p,q);
        merge_sort(a,q+1,r);
        merge(a,p,q,r);
    }
}

void merge(int a[9],int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1];
    int R[n2+1];
    int i,j,k;
    for(i=1;i<=n1;i++) L[i]=a[i+p-1];
    L[n1+1]=INT_MAX;
    for(j=1;j<=n2;j++) R[j]=a[j+q];
    R[n2+1]=INT_MAX;
    i=1,j=1;
    for(k=p;k<=r;k++)
    {
        if(L[i]<R[j]){a[k]=L[i];i+=1;}
        else
        {
            a[k]=R[j];
            j+=1;
            global_count+=(q-p-i+2);
         }
    }
}


void display(int num)
{
    while(state[num].bef!=-1){
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            cout<<state[num].pos[i][j];
        cout<<endl;
    }
    //cout<<state[num].bef;
    cout<<endl;
    num=state[num].bef;}
}

int  search()
{
    int i=1;
    while(1){
        if(sign(i)==sign(0)){
            cout<<"find the result"<<i<<endl;
            display(i);
            return i;
        }
        Next(i);
        i++;
    }
}

