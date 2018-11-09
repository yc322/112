#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED
#define N 1001
typedef struct coordinate
{
    int x;
    int y;
}point;

typedef struct Bound
{
    int ymin,xmin;
    int ymax,xmax;
}rectangle;

struct QuadNode
{
private:
    //rectangle bound;//the space's bound
    //point p;
    //point data[N];
    //int length;
    int pos;
public:
    rectangle bound;//the space's bound
    point p;
    point data[N];
    QuadNode *child[4];
    void print_value();
    int flag;//is the node have child
    QuadNode(int x1,int y1,int x2,int y2);
    QuadNode (int x1,int y1,int x2,int y2,point parent);
    void split();
    bool contain(point x);
    void insert(point x);
    int length;
    int dis;
    void increase_data(point input);
    void distance(point input);
    int low_distance(point input);
};

class QuadTree
{
private:
//    QuadNode* root;
public:
    QuadNode* root;
    QuadTree(int x1,int y1,int x2,int y2);
    void Insert(QuadNode *parent,point p);
    void Key_Insert(point p);
    void Print();
    void Print_Node(QuadNode *p);
};

#endif // QUADTREE_H_INCLUDED
