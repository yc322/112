#include <iostream>

using namespace std;
#include "stack.h" //Attention especially for template

int main()
{
   int n;
   double item;
   MyStack<double> numbers;  //  declares and initializes a stack of double numbers
   cout << " Type in an integer n followed by n decimal numbers." << endl
        << " The numbers will be printed in reverse order." << endl;
   cin  >> n;
   for (int i = 0; i < n; i++) {
      cin >> item;
      numbers.push(item);
   }
   cout << endl << endl;
   while (!numbers.empty()) {
	numbers.top(item);
      	cout << item << " ";
      	numbers.pop();
   }
   cout << endl;
}
