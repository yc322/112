#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
//typedef double Stack_entry;
enum Error_code{underflow_error,overflow_error,success};
const int maxstack=10;

template <class Stack_entry>
class MyStack
{
public:
    MyStack();
    bool empty()const;
    Error_code push(const Stack_entry&item);
    Error_code pop();
    Error_code top(Stack_entry &item)const;
private:
    int count;
    Stack_entry entry[maxstack];
};

template <class Stack_entry>
MyStack<Stack_entry>::MyStack()
{
    count=0;
}

template <class Stack_entry>
bool MyStack<Stack_entry>::empty()const//can't modify data of class,can't call fuc without const
{
    bool outcome=true;
    if(count>0) outcome=false;
    return outcome;
}

template <class Stack_entry>
Error_code MyStack<Stack_entry>::push(const Stack_entry &item)
{
    Error_code outcome=success;
    if(count>=maxstack)
        outcome=overflow_error;
    else
        entry[count++]=item;
    return outcome;
}

template <class Stack_entry>
Error_code MyStack<Stack_entry>::pop()
{
    Error_code outcome=success;
    if(count==0)
        outcome=underflow_error;
    else --count;
    return outcome;
}

template <class Stack_entry>
Error_code MyStack<Stack_entry>::top(Stack_entry &item)const
{
    Error_code outcome=success;
    if(count==0) outcome=underflow_error;
    else
        item=entry[count-1];
    return outcome;
}



#endif // STACK_H_INCLUDED
