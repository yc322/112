#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#define N 101
#include <queue>

using namespace std;

typedef struct{
    int vis;//is on the road or not
    int pre_col;
    int pre_row;
    int col;
    int row;
    char p;
}Maze;

class Road
{
    private:
    queue <Maze> Path;
    Maze a[N][N];
    public:
    void scan();
    int start1,start2,end1,end2;
    void MazePath();
    void Print();
    void Next(int m,int n);
};


#endif // CLASS_H_INCLUDED
