#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

class Main
{
  private:
      int row,col;
      int flag[31][31];
      int height[30][30];
      int path[90];
      int maxlength;
  public:
    Main(int i,int j);
    void create();
    int max_len(int i,int j);
    void maxLength();
    void Print(int x,int y);



};
#endif // CLASS_H_INCLUDED
