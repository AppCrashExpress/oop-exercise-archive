#include "Shape.h"
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> IntStack;

    IntStack.push(5);
    cout << "Pushing 5 into IntStack, now " << IntStack.top() << " is its top element" << endl;
    IntStack.push(3.14);
    cout << "Pushing 3.14 into IntStack, now " << IntStack.top() << " is its top element" << endl;

    Stack<double> DoubleStack;

    DoubleStack.push(5);
    cout << "Pushing 5 into DoubleStack, now " << DoubleStack.top() << " is its top element" << endl;
    DoubleStack.push(3.14);
    cout << "Pushing 3.14 into DoubleStack, now " << DoubleStack.top() << " is its top element" << endl;

}
