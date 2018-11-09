#include <iostream>
#include "class.h"
using namespace std;

//int a[N][N];
int main()
{
    int m,n;
    //Main temp(m,n);
    cout<<"please input the size :"<<endl;
    cin>>m>>n;
    Main temp(m,n);
    temp.maxLength();
    return 0;
}

