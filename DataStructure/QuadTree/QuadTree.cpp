#include "QuadTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
using namespace std;
void QuadTree::Key_Insert(point p)
{
    Insert(root,p);
}

QuadNode::QuadNode(int x1,int y1,int x2,int y2)
{
    for(int i=0;i<4;i++){
        child[i]=NULL;
    }
    bound.xmin=x1;
    bound.ymin=y1;
    bound.xmax=x2;
    bound.ymax=y2;
    flag=0;
    length=0;
    dis=0;
}

QuadNode::QuadNode(int x1,int y1,int x2,int y2,point parent)
{
    for(int i=0;i<4;i++)
    {
        child[i]=NULL;
    }
    bound.xmin=x1;
    bound.ymin=y1;
    bound.xmax=x2;
    bound.ymax=y2;
    if((parent.x>=x1 && parent.x<=x2)&&(parent.y>=y1&&parent.y<=y2)){
        flag=1;
        p=parent;
    }
    else flag=0;
}

bool QuadNode::contain(point parent)
{
    cout<<bound.xmin<<"   "<<bound.xmax<<"   "<<bound.ymin<<"   "<<bound.ymax<<endl;
    if((parent.x>=bound.xmin && parent.x<=bound.xmax)&&(parent.y>=bound.ymin&&parent.y<=bound.ymax)) return true;
    else return false;
}



/******************
   0    |     1
   -------------
   3    |    4
*******************/
void QuadNode::split()
{
    int half_x=(bound.xmax+bound.xmin)/2;
    int half_y=(bound.ymax+bound.ymin)/2;
    QuadNode *nw=new QuadNode(bound.xmin,half_y,half_x,bound.ymax);
    QuadNode *ne=new QuadNode(half_x,half_y,bound.xmax,bound.ymax);
    QuadNode *sw=new QuadNode(bound.xmin,bound.xmin,half_x,half_y);
    QuadNode *se=new QuadNode (half_x,bound.ymin,bound.xmax,half_y);
    child[0]=nw;
    child[1]=ne;
    child[2]=se;
    child[3]=sw;
}

void QuadNode::insert(point input)
{
    p.x=input.x;
    p.y=input.y;
    flag=1;
}

void QuadNode::increase_data(point input)
{
    data[length]=input;
    length++;
}

QuadTree::QuadTree(int x1,int y1,int x2,int y2)
{
    QuadNode *temp=new QuadNode(x1,y1,x2, y2);
    root=temp;
}


void QuadTree::Print()
{
    /*for(int i=0;i<root->length;i++){
        cout<<root->data[i].x<<"  "<<root->data[i].y<<"  ";
    }*/
    cout<<endl;
    Print_Node(root);
}

void QuadNode::print_value()
{
    cout<<"new node"<<endl;
    cout<<"length"<<length<<endl;
    for(int i=1;i<=length;i++){
        cout<<data[i].x<<"  "<<data[i].y<<endl;
    }
    cout<<endl;
    cout<<"parent->P"<<endl;
    cout<<p.x<<"  "<<p.y<<endl;
    //for(int i=0;i<4;i++){
    //if(length==2) cout<<p.x<<"  "<<p.y<<endl;
}

void QuadTree::Print_Node(QuadNode *p)
{
    QuadNode*t;
    p->print_value();
    if(p->child[0]!=NULL){
        for(int i=0;i<4;i++) {t=p->child[i];Print_Node(t);}
    }
}

void QuadTree::Insert(QuadNode *parent,point p)
{
    if(parent->contain(p)==false) {cout<<"not include"<<endl;return ;}
    if(parent->length==0 && parent->contain(p)){
        cout<<"insert in parent"<<endl;
        parent->insert(p);
        parent->increase_data(p);
    }
    else{
        parent->increase_data(p);
        if(parent->child[0]==NULL){
            parent->split();
        }
        if(parent->child[0]!=NULL){
            for(int i=0;i<4;i++){
                Insert(parent->child[i],p);
            }
        }
    }
}

int QuadNode::low_distance(point input)
{
    int xmin=bound.xmin;
    int xmax=bound.xmax;
    int ymin=bound.ymin;
    int ymax=bound.ymax;
    if(contain(input)) return 0;
    else if(input.x<xmax && input.x>=xmin){
        return min(abs(ymin-input.y),abs(ymax-input.y));
    }
    else if(input.y<ymax && input.y>=ymin){
        return min(abs(xmax-input.x),abs(xmin-input.x));
    }
    else{
        int a=sqrt((input.x-xmax)*(input.x-xmax)+(input.y-ymax)*(input.y-ymax));
        int b=sqrt((input.x-xmin)*(input.x-xmin)+(input.y-ymin)*(input.y-ymin));
        int c=sqrt((input.x-xmax)*(input.x-xmax)+(input.y-ymin)*(input.y-ymin));
        int d=sqrt((input.x-xmin)*(input.x-xmin)+(input.y-ymax)*(input.y-ymax));
        return min(min(a,b),min(c,d));
    }
}








