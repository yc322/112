#include <iostream>
#include <cstring>

#include "class.h"

using namespace std;

void Road::scan()
{
    int m,n;
    cout<<"please input the size of the maze:"<<endl;
    cin>>m>>n;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j].p;
            a[i][j].col=j;
            a[i][j].row=i;
            //a[i][j].di=1;
            a[i][j].vis=0;
        }
    }
    //let the blocks around what you input is 'X' that can not move to
    for(int i=0;i<=m+1;i++)
    {
        a[i][0].p='X';
        a[i][n+1].p='X';
        a[i][0].vis=0;
        a[i][n+1].vis=0;
    }
    for(int j=0;j<=n+1;j++)
    {
        a[0][j].p='X';
        a[m+1][j].p='X';
        //a[0][j].di=0;
        //a[m+1][j].di=0;
        a[0][j].vis=0;
        a[m+1][j].vis=0;

    }
    /*for(int i=0;i<=m+1;i++)
    {
        for(int j=0;j<=n+1;j++)
        {
            cout<<a[i][j].p;
        }
        cout<<endl;
    }*/
    cout<<"please input the start index:"<<endl;
    cin>>start1>>start2;
    cout<<"please input the end index:"<<endl;
    cin>>end1>>end2;
}

void Road::MazePath()//start1 is the start row ,start2 is the start col
{
    int flag=0;
    Maze temp;
    Path.push(a[start1][start2]);//push the start point in stack
    a[start1][start2].vis=1;//curstep=1;
    while(!Path.empty())
    {
        temp=Path.front();
        //cout<<temp.col<<temp.row<<endl;
        if(temp.row==end1 && temp.col==end2)
        {
            flag=1;
            break;
        }
        int m=temp.row,n=temp.col;
        Next(m,n);
        Path.pop();
    }
    if(flag==0) {cout<<"no path"<<endl;}
    else
    {
        cout<<"find the way"<<endl;
    }
}

void Road::Next(int m,int n)
{
    if(a[m+1][n].vis==0 && a[m+1][n].p!='X')
    {
        Path.push(a[m+1][n]);
        a[m+1][n].vis=1;
        a[m+1][n].pre_row=m;
        a[m+1][n].pre_col=n;
    }
    if(a[m-1][n].vis==0 && a[m-1][n].p!='X')
    {
        Path.push(a[m-1][n]);
        a[m-1][n].vis=1;
        a[m-1][n].pre_row=m;
        a[m-1][n].pre_col=n;
    }
    if(a[m][n-1].vis==0 && a[m][n-1].p!='X')
    {
        Path.push(a[m][n-1]);
        a[m][n-1].vis=1;
        a[m][n-1].pre_row=m;
        a[m][n-1].pre_col=n;
    }
    if(a[m][n+1].vis==0 && a[m][n+1].p!='X')
    {
        Path.push(a[m][n+1]);
        a[m][n+1].vis=1;
        a[m][n+1].pre_row=m;
        a[m][n+1].pre_col=n;
    }
}

void Road::Print()
{
    int m=a[end1][end2].pre_row;
    int n=a[end1][end2].pre_col;
    cout<<'('<<m<<','<<n<<')'<<"<-";
    while(m!=start1 || n!= start2)
    {
        int temp1=a[m][n].pre_row;
        int temp2=a[m][n].pre_col;
        m=temp1;
        n=temp2;
        cout<<'('<<m<<','<<n<<')';
        if(m!=start1 || n!=start2) cout<<"<-";
    }
}
