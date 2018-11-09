#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

class Record
{
public:
    void input();
    int alphabetic_order(char c);
    void my_sort();
    void display();
private:
    int size;
    int max_length;
};


#endif // HEAD_H_INCLUDED
