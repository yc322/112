#include "class.h"
#include <iostream>
#include <string.h>

using namespace std;

Main::Main(int i,int j)
{
    this->row=i;
    this->col=j;
    create();
}

void Main::create()
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cin>>height[i][j];
            flag[i][j]=-1;
        }
    }

}

int Main::max_len(int i,int j)
{
    int len=0;
    int temp[4]={1,1,1,1};
    if(flag[i][j]!=-1) return flag[i][j];
    else{
        if(i>0 && height[i][j]>height[i-1][j])//move up
        {
            temp[0]=max_len(i-1,j)+1;
        }
        if(i<row-1 && height[i+1][j]<height[i][j])//move down
        {
            temp[1]=max_len(i-1,j)+1;
        }
        if(j>0 && height[i][j-1]<height[i][j])//move left
        {
            temp[2]=max_len(i,j-1)+1;
        }
        if(j<col-1 && height[i][j+1]<height[i][j])//move right
        {
            temp[3]=max_len(i,j+1)+1;
        }
        for(int k=0;k<4;k++)
        {
            if(len<temp[k])
                len=temp[k];
        }
        flag[i][j]=len;
        return len;
    }
}

void Main::maxLength()
{
    int x,y;
    maxlength=0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            // cout<<"max_len"<<i<<" "<<j<<" "<<max_len(i,j)<<endl;
            if(max_len(i,j)>maxlength)
            {
                maxlength=max_len(i,j);
                x=i;
                y=j;
            }
        }
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<flag[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"the maximum length is:"<<maxlength<<endl;
    cout<<"the longest path :"<<endl;
    Print(x,y);
}

void Main::Print(int a,int b)
{
    int i=a;
    int max_=0;
    int j=b;
    int x,y;
    int temp[row][col];
    memset(temp,0,sizeof(temp));//暂存上下左右四个方向滑行的长度和坐标
    while(maxlength--)
    {
        memset(temp,0,sizeof(temp));
        cout<<height[i][j]<<" ";
        if(j>0 && height[i][j-1]<height[i][j])
            temp[i][j-1]=flag[i][j-1];
        if(j<col-1 && height[i][j+1]<height[i][j])
            temp[i][j+1]=flag[i][j+1];
        if(i>0 && height[i-1][j]<height[i][j])
            temp[i-1][j]=flag[i-1][j];
        if(i<row-1 && height[i+1][j]<height[i][j])
            temp[i+1][j]=flag[i+1][j];
        for(int k=0;k<row;k++)//calculate the maximum length of four directions
        {
            for(int w=0;w<col;w++)
            {
                if(max_<temp[k][w])
                {
                    x=k;
                    y=w;
                    max_=temp[k][w];
                }
            }
        }
        i=x;
        j=y;
        max_=0;
    }

}
