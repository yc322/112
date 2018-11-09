#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#define N 100
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <limits.h>
#include <vector>
#include <cstring>
using namespace std;

template<class Record>
class Heap
{
private:
   //vector<Record> h;
    Record h[N];
    int heap_size;
    int length;
    int maxSize;
protected:
    int left(int n);
    int right(int n);
    int p(int n);
public:
    Heap();
    void Build_Heap(int n,bool (*visit)(Record x,Record y));
    void Increase_Key(int i,Record key);
    void Delete(Record x,bool (*visit)(Record x,Record y));
    void Max_Heap_Insert(Record key);
    void Max_Heapify(int i,bool (*visit)(Record x,Record y));
    void print();
    Record get_top();
    Record Heap_Extract_top(bool(*visit)(Record x,Record y));
    void Heap_Sort(bool(*visit)(Record x,Record y));
};


template <class Record>
Heap<Record>::Heap()
{
    memset(h,0,sizeof(h));
    length=0;
    heap_size=0;
}

template <class Record>
Record Heap<Record>::get_top()
{
return h[1];
}

template <class Record>
void Heap<Record>::Delete(Record x,bool (*visit)(Record x,Record y))
{
    bool flag=false;
    int i;
    for(i=1;i<=heap_size;i++){
        if(h[i]==x){
            cout<<"index"<<i<<"number"<<h[i]<<endl;
            flag=true;
            swap(h[i],h[length]);
            length--;
            heap_size--;
            break;
        }
    }
    if(flag==true) Max_Heapify(i,visit);
    else cout<<"not find"<<endl;
}

template <class Record>
Record Heap<Record>::Heap_Extract_top(bool (*visit)(Record x,Record y))
{
    if(heap_size<1){
        cout<<"heap underflow"<<endl;
        exit(1);
    }
    Record x=h[1];
    h[1]=h[heap_size];
    heap_size--;
    length--;
    Max_Heapify(1,visit);
    return x;
}


template <class Record>
int Heap<Record>::left(int n)
{
    return 2*n;
}

template <class Record>
int Heap<Record>::right(int n)
{
    return 2*n+1;
}


template <class Record>
int Heap<Record>::p(int n)
{
    return floor(n/2);
}


template<class Record>
void Heap<Record>::Build_Heap(int n,bool (*visit)(Record x,Record y))
{
    if(n<0) cout<<"the size must bigger than 0"<<endl;
    else{
        heap_size=n;
        length=n;
        for(int i=1;i<=n;i++){
            cin>>h[i];
            }
        //h=malloc(n*sizeof(Record));
        for(int i=floor(n);i>=1;i--){
            Max_Heapify(i,visit);
            //print();
        }
    }
}

template <class Record>
void Heap<Record>::print()
{
    for(int i=1;i<=length;i++)
        cout<<h[i]<<"  ";
}

template <class Record>
void Heap<Record>::Max_Heapify(int i,bool (*visit)(Record x,Record y))
{
    int l=left(i);
    int r=right(i);
    int largest;
    if(l<=heap_size && (*visit)(h[l],h[i])) largest=l;
    else largest=i;
    if(r<=heap_size && (*visit)(h[r],h[largest]))largest=r;
    if(largest!=i){
        swap(h[i],h[largest]);
        Max_Heapify(largest,visit);
    }
}


template <class Record >
void Heap<Record>::Increase_Key(int i,Record key)
{
    if(key<h[i]) cout<<"error:new key is smaller than current key"<<endl;
    h[i]=key;
    while(i>1 && h[p(i)]<h[i]){
        swap(h[i],h[p(i)]);
        i=p(i);
    }
}

template <class Record>
void Heap<Record>::Heap_Sort(bool (*visit)(Record x,Record y))
{
    for(int i=heap_size;i>=2;i--){
        swap(h[1],h[i]);
        heap_size--;
        Max_Heapify(1,visit);
        print();
        cout<<endl;
    }
}

template <class Record>
void Heap<Record>::Max_Heap_Insert(Record key)
{
    length++;
    heap_size++;
    h[heap_size]=INT_MIN;
    Increase_Key(heap_size,key);
}

#endif // HEAP_H_INCLUDED
