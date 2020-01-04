#include "Shape.h"
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> IntStack;

    IntStack.push(1).push(7).push(7).push(0).push(1).push(3);

    cout << "Using iterator to iterate through stack: ";
    for (auto begin = IntStack.begin(), end = IntStack.end(); begin != end; ++begin)
        cout << *(begin) << " ";
    cout << endl;
}
