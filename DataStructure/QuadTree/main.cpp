#include <iostream>
#include "QuadTree.h"
#include <cmath>
#include <queue>
using namespace std;
void K_Tops(point p,int k);

int point_distance(point p,point t)
{
    cout<<"#########"<<endl;
    cout<<"p"<<p.x<<"  "<<p.y<<endl;
    cout<<"t"<<t.x<<"  "<<t.x<<endl;
    int dis=sqrt((p.x-t.x)*(p.x-t.x)+(p.y-t.y)*(p.y-t.y));
    cout<<"distance:"<<dis<<endl;
    return dis;
}

struct point_position
{
    int priority;
    point node;
    point_position(point p,point input_node)
    {
        priority=point_distance(p,input_node);
        node=input_node;
    }
    friend bool operator < (point_position n1, point_position n2)
    {
        return n1.priority < n2.priority;
    }
};

struct rectangle_position
{
    int priority;
    QuadNode *node;
    rectangle_position(point p,QuadNode *input)
    {
        priority=input->low_distance(p);
        node=input;
    }
    friend bool operator < (rectangle_position n1, rectangle_position n2)
    {
        return n1.priority > n2.priority;
    }
};

QuadTree mytree(-128,-128,128,128);

int main()
{
   //QuadTree mytree(-128,-128,128,128);
    int input[14][2]={{100,125},{25,-30},{-55,80},{125,-60},{80,80},{-80,-8},
                   {-12,-112},{-48,-112},{16,72},{60,100},{48,48},{36,8},{4,60},{28,30}};

    for(int i=0;i<14;i++){
        cout<<"i="<<i<<endl;
        point temp;
        temp.x=input[i][0];
        cout<<input[i][0]<<endl;
        cout<<input[i][1]<<endl;
        temp.y=input[i][1];
        mytree.Key_Insert(temp);
    }

    cout<<"increase key finish"<<endl<<endl<<endl<<endl;
    mytree.Print();
    cout<<"print finish"<<endl<<endl<<endl;
    point p;
    //p.x=0;
    //p.y=0;

    cout<<"please input the index:"<<endl;
    cin>>p.x>>p.y;
    cout<<"please input k"<<endl;
    int k;
    cin>>k;
    K_Tops(p,k);
    //K_Tops(p,3);

    cout<<"************************"<<endl;
    cout<<"distance"<<endl;
    for(int i=0;i<14;i++){
        cout<<sqrt((input[i][0]-50)*(input[i][0]-50)+(input[i][1]-50)*(input[i][1]-50))<<endl;
    }
}

//priority_queue <struct point_position> max_heap;  //大顶堆，用来存放点
priority_queue <struct rectangle_position> min_heap; //小顶堆，用来存放矩形
priority_queue <struct point_position> my_max_heap;  //大顶堆，用来存放点

void K_Tops(point p,int k)
{
    QuadNode *root=mytree.root;
    //struct point_position(p,parent->p);
    struct rectangle_position temp(p,root);
    //struct rectangle_position parent;
    min_heap.push(temp);
    //my_max_heap.push()
    while(min_heap.size()!=0)
    {
        struct rectangle_position parent=min_heap.top();
        min_heap.pop();
        if(parent.node->child[0]!=NULL){
            for(int i=0;i<4;i++){
                struct rectangle_position temp(p,parent.node->child[i]);
                min_heap.push(temp);
            }
        }
        if(parent.node->length!=0){
            cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            cout<<parent.node->length<<endl;
            //int k=parent.node->length;
            cout<<parent.node->data[0].x<<"   "<<parent.node->data[0].y<<endl;
            cout<<"::"<<endl;
            cout<<parent.node->p.x<<"  "<<parent.node->p.y<<endl;
            struct point_position pos(p,parent.node->p);
            my_max_heap.push(pos);
        }
        cout<<"size"<<my_max_heap.size()<<endl;
    }
    //while(my_max_heap.size()>=0&&min_heap.size()>0 && min_heap.top().priority>my_max_heap.top().priority);
    cout<<"******************************"<<endl;

    while(!my_max_heap.empty()){
        cout<<"the point position:"<<"("<<my_max_heap.top().node.x<<","<<my_max_heap.top().node.y<<")"<<endl;
        cout<<"the distance is "<<my_max_heap.top().priority<<endl;
        my_max_heap.pop();
    }
}
