#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include "binary tree.h"
enum Error_code {success,duplicate_error,not_present};


template <class Record>
class AVL_Tree:public Binary_tree<Record>
{
public:
    Error_code insert(const Record &new_data);
    Error_code remove(Record &data);
    void init();
private:
    Error_code avl_insert(Binary_node<Record>*&sub_root,const Record &new_data,bool &taller);
    void rotate_left(Binary_node<Record>*&sub_root);
    void rotate_right(Binary_node<Record>*&sub_root);
    void right_balance(Binary_node<Record>*&sub_root);
    void left_balance(Binary_node<Record>*& sub_root);
    Error_code avl_delete(Binary_node<Record>*&sub_root,Record &data,bool &shorter);
};

using namespace std;

/*template<class Record>
void AVL_Tree<Record>::init()
{
    Record x;
    Binary_node<Record> *sub_root=this->root;
    for(int i=0;i<3;i++){
        cout<<"input a number";
        cin>>x;
        Binary_node<Record>*temp=new Binary_node<Record>(x);
        sub_root->left=temp;
        sub_root=sub_root->left;
    }
    sub_root=this->root;
    for(int i=0;i<3;i++){
        cout<<"input number:"<<endl;
        cin>>x;
        Binary_node<Record>*temp=new Binary_node<Record>(x);
        sub_root->right=temp;
        sub_root=sub_root->right;
    }
}*/


template <class Record>
void Binary_node<Record>::set_balance(Balance_factor b)
{
    balance=b;
}

template <class Record>
Balance_factor Binary_node<Record>::get_balance()const
{
    return balance;
}

//the External interface
template <class Record>
Error_code AVL_Tree<Record>::insert(const Record &new_data)
{
    bool taller;
    return avl_insert(this->root,new_data,taller);
}

//*&指针的引用
//insert a new node
template <class Record>
Error_code AVL_Tree<Record>::avl_insert(Binary_node<Record>*&sub_root,const Record &new_data,bool &taller)
{
    Error_code result =success;
    //find the position to insert a node
    if(sub_root==NULL)
    {
        sub_root=new Binary_node<Record>(new_data);
        taller=true;//the high of the subtree is change
    }
    //the data is exist
    else if(new_data==sub_root->data)
    {
        result=duplicate_error;
        taller=false;
    }
    else if(sub_root->data>new_data)
    {
        result=avl_insert(sub_root->left,new_data,taller);//find the position in left subtree
        if(taller==true)
        {
            switch(sub_root->get_balance())
            {
            case left_higher:
                left_balance(sub_root);//rotation
                taller=false;
                break;
            case right_higher:
                sub_root->set_balance(equal_height);
                taller=false;//the tree must balance
                break;
            case equal_height:
                sub_root->set_balance(left_higher);
                break;
            }
        }
    }
    else if(sub_root->data<new_data)
    {
        result=avl_insert(sub_root->right,new_data,taller);
        if(taller==true)
        {
            switch(sub_root->get_balance())
            {
            case left_higher:
                sub_root->set_balance(equal_height);
                taller=false;
                break;
            case right_higher:
                right_balance(sub_root);
                taller=false;
                break;
            case equal_height:
                sub_root->set_balance(right_higher);
                break;
            }
        }
    }
    return result;
}

template <class Record>
void AVL_Tree<Record>::rotate_left(Binary_node<Record>*&sub_root)
{
    if(sub_root==NULL || sub_root->right==NULL)//imposible case
        cout<<"WARNING:program error detected in rotate left"<<endl;
    else
    {
        Binary_node<Record>*right_tree=sub_root->right;
        sub_root->right=right_tree->left;
        right_tree->left=sub_root;
        sub_root=right_tree;
    }
}

template <class Record>
void AVL_Tree<Record>::rotate_right(Binary_node<Record>*&sub_root)
{
    if(sub_root==NULL || sub_root->left==NULL)
        cout<<"WARNING:program error detected in rotate right"<<endl;
    else
    {
        Binary_node<Record>*left_tree=sub_root->left;
        sub_root->left=left_tree->right;
        left_tree->right=sub_root;
        sub_root=left_tree;
    }
}

//the right subtree is higher
template <class Record>
void AVL_Tree<Record>::right_balance(Binary_node<Record>*&sub_root)
{
    Binary_node<Record>*&right_tree=sub_root->right;
    switch(right_tree->get_balance())
    {
    case right_higher:
        sub_root->set_balance(equal_height);
        right_tree->set_balance(equal_height);
        rotate_left(sub_root);
        break;
    //the right subtree is higher but the the height of two sub tree is the same
    case equal_height:
        cout<<"WARNING:program error detected in right_balance"<<endl;
    case left_higher:
        Binary_node<Record>*sub_tree=right_tree->left;
        //set the balance factor of different cases
        switch (sub_tree->get_balance())
        {
        case equal_height:
            sub_root->set_balance(equal_height);
            right_tree->set_balance(equal_height);
            break;
        case left_higher:
            sub_root->set_balance(equal_height);
            right_tree->set_balance(right_higher);
            break;
        case right_higher:
            sub_root->set_balance(left_higher);
            right_tree->set_balance(equal_height);
            break;
        }
        sub_tree->set_balance(equal_height);
        rotate_right(right_tree);
        rotate_left(sub_root);
        break;
    }
}

template <class Record>
void AVL_Tree<Record>::left_balance(Binary_node<Record>*& sub_root)
{
    if(sub_root!=NULL) cout<<sub_root->data<<endl;
    Binary_node<Record>*left_tree =sub_root->left;
    switch(left_tree->get_balance())
    {
    case left_higher:
        sub_root->set_balance(equal_height);
        left_tree->set_balance(equal_height);
        rotate_right(sub_root);
        break;
    case equal_height:
        cout<<"WARNING:program error detected in left_balance"<<endl;
    case right_higher:
        Binary_node<Record>*&sub_tree=left_tree->right;
        switch(sub_tree->get_balance())
        {
        case equal_height:
            sub_root->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            break;
        case right_higher:
            left_tree->set_balance(equal_height);
            sub_root->set_balance(right_higher);
            break;
        case left_higher:
            left_tree->set_balance(equal_height);
            sub_root->set_balance(right_higher);
            break;
        }
        sub_tree->set_balance(equal_height);
        if(sub_root!=NULL) cout<<sub_root->left->data<<endl;
        rotate_left(left_tree);
        if(sub_root!=NULL) cout<<sub_root->left->data<<endl;
        rotate_right(sub_root);
        break;
    }
}

template <class Record>
Error_code AVL_Tree<Record>::remove(Record &data)
{
    bool shorter=true;
    return avl_delete(this->root,data,shorter);
}

template <class Record>
Error_code AVL_Tree<Record>::avl_delete(Binary_node<Record>*&sub_root,Record &data,bool &shorter)
{
    if(sub_root!=NULL) cout<<"mmp"<<sub_root->data<<endl;
    Error_code result=success;
    Record sub_record=0;
    if(sub_root==NULL)
    {
        shorter=false;
        return not_present;
    }
    else if(sub_root->data==data)
    {
        cout<<"Find it"<<endl;
        Binary_node<Record>* delete_tree=sub_root;
        if(sub_root->right==NULL)
        {
            sub_root=sub_root->left;
            shorter=true;
            delete(delete_tree);
            return success;
        }
        else if(sub_root->left==NULL)
        {
            sub_root=sub_root->right;
            shorter=true;
            delete(delete_tree);
            return success;
        }
        else
        {
            delete_tree=sub_root->left;
            Binary_node<Record>* delete_p=delete_tree;
            while(delete_tree->right!=NULL)
            {
                delete_p=delete_tree;
                delete_tree=delete_tree->right;
            }
            cout<<"the change data:"<<delete_tree->data<<endl;
            swap(delete_tree->data,sub_root->data);//change the data of sub_root and it's predecessor
            if(delete_tree->left!=NULL)
            {
                delete_p->right=delete_tree->left;
            }
            else
            {
                delete_p->right=NULL;
            }
            delete(delete_tree);
        }
    }
    else
    {
        if(data<sub_root->data)
        {
            result=avl_delete(sub_root->left,data,shorter);
            //cout<<"&&&&&"<<endl;
            if(shorter==true)
            {
                //cout<<"&&&&&"<<endl;
                switch(sub_root->get_balance())
                {
                case equal_height:
                    cout<<"1:"<<endl;
                    sub_root->set_balance(right_higher);
                    shorter=false;
                    break;
                case left_higher:
                    sub_root->set_balance(equal_height);
                    break;
                case right_higher:
                    cout<<"&&&&&"<<endl;
                    right_balance(sub_root);
                    shorter=false;
                    break;
                }
            }
        }
        else
        {
            result=avl_delete(sub_root->right,data,shorter);
            cout<<"*******"<<endl;
            if(shorter==true)
            {
                switch(sub_root->get_balance())
                {
                case equal_height:
                    cout<<"case 1"<<endl;
                    sub_root->set_balance(left_higher);
                    shorter=false;
                    break;
                case right_higher:
                    cout<<"case 2"<<endl;
                    sub_root->set_balance(equal_height);
                    break;
                case left_higher:
                    cout<<"turn right"<<endl;
                    left_balance(sub_root);
                    shorter=false;
                    break;
                }
            }
        }
    }
}



#endif // AVL_H_INCLUDED
