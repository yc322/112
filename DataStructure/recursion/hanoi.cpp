#include <iostream>

using namespace std;

void move(int count,char start,char finish,char temp);


int main()
{
    int count;
    cin>>count;
    move(count,'A','C','B');
    return 0;
}


void move(int count,char start,char finish,char temp)
{
    if(count>0)
    {
        move(count-1,start,temp,finish);//将初始塔上的n-1个盘子用目的塔移动到借助塔
        cout<<"move disk "<<start<<" to "<<finish<<endl;
        move(count-1,temp,finish,start);//将借助塔上的n-1个移动到目的塔
    }
}
