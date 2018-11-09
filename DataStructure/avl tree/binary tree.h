#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED
#include <stack>
using namespace std;

enum Balance_factor{left_higher,right_higher,equal_height};
template <class Entry>
struct Binary_node{
    Entry data;
    Balance_factor balance;
    Binary_node<Entry> *left;
    Binary_node<Entry> *right;
    //Binary_node<Entry>* p;
    Binary_node();
    Binary_node(const Entry &x);
    virtual void set_balance(Balance_factor b);
    virtual Balance_factor get_balance()const;
};

template <class Entry>
class Binary_tree{
public:
    Binary_tree();
    bool empty()const;
    int size()const;
    void inorder(void(*visit)(Entry &));
    void preorder(void (*visit)(Entry &));
    void postorder(void (*visit)(Entry &));
    void insert(Entry &);
protected:
    int count;
    Binary_node<Entry>*root;
    void recursive_inorder(Binary_node<Entry>*sub_root,void (*visit)(Entry &));
    void recursive_preorder(Binary_node<Entry>*sub_root,void(*visit)(Entry &));
    void recursive_postorder(Binary_node<Entry>*sub_root,void(*visit)(Entry &));
};

template <class Entry>
int Binary_tree<Entry> :: size() const
{
    return count;
}


template<class Entry>
Binary_node<Entry>::Binary_node()
{
    left=right=NULL;
    balance=equal_height;
}

template <class Entry>
Binary_node<Entry>::Binary_node(const Entry &x)
{
    data=x;
    left=right=NULL;
    balance=equal_height;
}


template <class Entry>
Binary_tree<Entry>::Binary_tree()
{
    root=NULL;
    count=0;
}

template <class Entry>
bool Binary_tree<Entry>::empty()const
{
    return root==NULL;
}

template <class Entry>
void Binary_tree<Entry>::inorder(void(*visit)(Entry &))
{
    recursive_inorder(root,visit);
    cout<<endl;
}
/*
template <class Entry>
void visit(Entry &x)
{
    cout<<x<<" ";
}
*/

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry>*sub_root,void (*visit)(Entry &))
{
    if(sub_root!=NULL)
    {
        recursive_inorder(sub_root->left,visit);
        (*visit)(sub_root->data);
        recursive_inorder(sub_root->right,visit);
    }
}

template<class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
{
    recursive_preorder(root,visit);
    cout<<endl;
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry>*sub_root,void (*visit)(Entry &))
{
    if(sub_root!=NULL){
        (*visit)(sub_root->data);
        recursive_preorder(sub_root->left,visit);
        recursive_preorder(sub_root->right,visit);
    }
}

template <class Entry>
void Binary_tree<Entry>::postorder(void(*visit)(Entry &))
{
    recursive_postorder(root,visit);
    cout<<endl;
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry>*sub_root,void (*visit)(Entry &))
{
    if(sub_root!=NULL){
        recursive_postorder(sub_root->left,visit);
        recursive_postorder(sub_root->right,visit);
        (*visit)(sub_root->data);

    }
}
template <class Entry>
void Binary_tree<Entry> :: insert(Entry &x)
{
    if(empty())
    {
        root=new Binary_node<Entry>(x);
        count++;
        return;
    }
    stack<int> numbers;
    int item=0;
    int tmpcount=size();
    while(tmpcount>0)
    {
        if(tmpcount%2==0)
        {
            numbers.push(2);
        }
        else
        {
            numbers.push(1);
        }
        tmpcount=(tmpcount-1)/2;
    }
    Binary_node<Entry> *current=root;
    while (numbers.size()>1)
    {
        item=numbers.top();
        if(item==1)current=current->left;
        if(item==2)current=current->right;
        numbers.pop();
    }
    item=numbers.top();
    if(item==1)current->left=new Binary_node<Entry>(x);
    if(item==2)current->right=new Binary_node<Entry>(x);
    count++;
}



#endif // BINARY_TREE_H_INCLUDED
