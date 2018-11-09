#include <iostream>
#include <stack>

using namespace std;


int main()
{
    char a[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    stack<char> trans;
    int n;
    cin>>n;
    int num;
    cin>>num;
    int temp;
    while(num>=n)
    {
        temp=a[num%n];
        num=num/n;
        trans.push(temp);
    }
    trans.push(a[num]);
    while(!trans.empty())
    {
        char b=trans.top();
        trans.pop();
        cout<<b;
    }
    return 0;
}
