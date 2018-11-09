#include <iostream>
#include "binary tree.h"
#include "AVL.h"
using namespace std;

template <class Entry>
void print(Entry &x)
{
    cout<<x<<" ";
}

/*
int main()
{
    Binary_tree<int>mytree;
    //AVL_Tree<int> mytree;
    for(int i=0; i<10; i++)mytree.insert(i);
    cout<<"Tree size is: "<<mytree.size()<<endl;
    //cout<<"Tree height is: "<<mytree.height()<<endl;
    cout<<"Preorder:"<<endl;
    mytree.preorder(print);
    cout<<endl;
    cout<<"inorder:"<<endl;
    mytree.inorder(print);
    cout<<endl;
    cout<<"Postorder:"<<endl;
    mytree.postorder(print);
    cout<<endl;
    cin.get();
    return 0;
}
*/

int main(){
	AVL_Tree<int> mytree;
	mytree.insert(13);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(5);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(16);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(3);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(10);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(14);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(18);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(2);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(4);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(8);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(11);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(15);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(17);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(20);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(1);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(7);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(9);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(12);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(19);
	mytree.inorder(print);
	mytree.postorder(print);
	mytree.insert(6);
	cout<<"inorder"<<endl;
	mytree.inorder(print);
	cout<<"preorder"<<endl;
	mytree.preorder(print);
	mytree.postorder(print);
	/*int data=6;
	mytree.remove(data);
	cout<<"inorder"<<endl;
	mytree.inorder(print);
	cout<<"preorder"<<endl;
	mytree.preorder(print);
	cout<<"postorder"<<endl;
	mytree.postorder(print);*/
	int x=16;
	mytree.remove(x);
	cout<<"inorder"<<endl;
	mytree.inorder(print);
	cout<<"preorder"<<endl;
	mytree.preorder(print);
	cout<<"postorder"<<endl;
	mytree.postorder(print);

}

