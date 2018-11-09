#include "head.h"
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
vector <string> sortable_list;

void Record::input()
{
    cout<<"please input the number of words you want to input"<<endl;
    cin>>size;
    string a;
    max_length=0;
    for(int i=0;i<size;i++){
        cin>>a;
        if(a.length()>max_length) max_length=a.length();
        reverse(a.begin(),a.end());
        sortable_list.push_back(a);
    }
    for(int i=0;i<size;i++){
        cout<<sortable_list[i]<<" ";
    }
    cout<<endl;
    cout<<max_length;
}

int Record::alphabetic_order(char c)
{
    if(c==' ') return 0;
    if('a'<=c && 'z'>=c) return c-'a'+1;
    if('A'<=c && c<='z') return c-'A'+1;
    return 27;
}

void clear(queue<string>&q)
{
    queue<string> empty;
    swap(empty,q);
}

queue<string>sequence[28];
void Record::my_sort()
{
    for(int i=0;i<max_length;i++){
        cout<<i<<endl;
        for(int p=0;p<28;p++){
            while(!sequence[p].empty()) sequence[p].pop();//clear the queue
        }
        cout<<"****"<<endl;
        for(int j=0;j<size ;j++){
            int temp=alphabetic_order(sortable_list[j][i]);
            cout<<temp<<" ";
            sequence[temp].push(sortable_list[j]);
        }
        sortable_list.clear();
        for(int k=0;k<28;k++){
            while(!sequence[k].empty()){
                sortable_list.push_back(sequence[k].front());
                sequence[k].pop();
            }
        }
        for(int p=0;p<size;p++){
        cout<<sortable_list[p]<<" ";}
    }
}

void Record::display()
{
    for(int i=0;i<size;i++){
        string temp;
        temp=sortable_list[i];
        reverse(temp.begin(),temp.end());
        cout<<temp<<" ";
    }
}
