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
        move(count-1,start,temp,finish);//����ʼ���ϵ�n-1��������Ŀ�����ƶ���������
        cout<<"move disk "<<start<<" to "<<finish<<endl;
        move(count-1,temp,finish,start);//���������ϵ�n-1���ƶ���Ŀ����
    }
}
