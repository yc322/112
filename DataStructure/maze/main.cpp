#include <iostream>

#include "class.h"

using namespace std;

int main()
{
    Road R;
    R.scan();
    R.MazePath();
    R.Print();
    return 0;
}

/*void MazePath(Maze a[N][N],int start1,int start2,int end1,int end2)//start1 is the start row ,start2 is the start col
{
    //a[start1][start2].vis=1;
    Path.push(a[start1][start2]);//push the start point in stack
    int i=start1;
    int j=start2;
    int pos;
    //curstep=1;
    while((i!=end1 || j!=end2)&&!Path.empty())
    {
        pos=Next(a,Path.top(),&i,&j);
        if(pos==0 && (i!=start1||j!=start2))//if this position haven't path to next and it is not the end,then move it
        {
            Path.pop();
        }
    }
    if(Path.empty()) printf("no path");
    else
    {
        print(a,start1,start2,end1,end2);
    }
}

//the next step if have no path return 0
int Next(Maze a[N][N],Maze b,int* row,int* col)
{
    int flag=4-a[*row][*col].di;
    int i=*row;
    int j=*col;
    while(flag--)
    {
        if(b.di==1)//move to the east
        {
            j++;
            if(a[i][j].p!='X' &&!a[i][j].vis)
            {
                //move the point
                *col=j;
                a[i][j].di++;
                Path.push(a[*row][*col]);
                flag=1;
                return 1;
            }
        }
        if(b.di==2)//move to south
        {
            i=i+1;
            if(a[i][j].p!='X' &&!(a[i][j].vis))
            {
                //move the point
                *row=i;
                a[i][j].di++;
                Path.push(a[*row][*col]);
                flag=1;
                return 1;
            }
        }
        if(b.di==3)//move to west
        {
            j=j-1;
            if(a[i][j].p!='X' && !a[i][j].vis)
            {
                //move the point
                *col=j;
                a[i][j].di++;
                Path.push(a[*row][*col]);
                return 1;
            }
        }
        if(b.di==4)
        {
            i++;
            if(a[i][j].p!='X'&& !a[i][j].vis)
            {
                *row=i;
                a[i][j].di++;
                Path.push(a[*row][*col]);
                return 1;
            }
        }

    }
    return 0;
}

//print the path
void print(Maze a[N][N],int i,int j,int end1,int end2)
{
    int step=0;//the step you move
    while(i!=end1 || j!=end2)
    {
        printf("(%d,%d) %d\n",i,j,step);
        if(a[i][j].di==2)
        {
            printf("move to east\n");
            j++;
            step++;
        }
        else if(a[i][j].di==3)
        {
            printf("move to north\n");
            i++;step++;
        }
        else if(a[i][j].di==4)
        {
            printf("move to west\n");
            j--;step++;
        }
        else
        {
            printf("move to north\n");
            i--;step++;
        }
    }
    printf("(%d,%d) %d",end1,end2,step);
    //printf("")

}*/
