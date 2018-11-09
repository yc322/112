#include <iostream>
#include "heap.h"
using namespace std;
template <class Record>
bool visit(Record x,Record y)
{
    if(x>y) return true;
    else return false;
}

template <class Record>
bool visit2(Record x,Record y)
{
    if(x<=y) return true;
    else return false;
}


int main()
{
    /*Heap<int> my_heap;
    int n;
    cin>>n;
    my_heap.Build_Heap(n,visit);
    my_heap.print();
    n=my_heap.Heap_Extract_top(visit);
    cout<<"max is"<<n<<endl;
    my_heap.print();
    cout<<endl<<"after inset 6"<<endl;
    my_heap.Max_Heap_Insert(6);
    my_heap.print();
    /*
    cout<<"please input the index you want to increase the key";
    cin>>n;
    cout<<"the key";
    int tmp;
    cin>>tmp;
    my_heap.Increase_Key(n,tmp);
    my_heap.print();

    cout<<"please input the number you want to delete:"<<endl;
    cin>>n;
    my_heap.Delete(n,visit);
    my_heap.print();
    my_heap.Heap_Sort(visit);
    my_heap.print();
*/
    int n;
    cout<<endl<<endl;
    Heap<int> min_heap;
    cout<<"please input the number"<<endl;
    cin>>n;
    min_heap.Build_Heap(n,visit2);
    min_heap.print();
    return 0;
}
