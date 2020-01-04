#include "Shape.h"
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> IntStack;

    IntStack.push(1).push(7).push(7).push(0).push(1).push(3);

    for (auto begin = IntStack.begin(), end = IntStack.end(); begin != end; ++begin)
        cout << *(begin) << " ";
    cout << endl;

    try
    {
        cout << "Trying to insert an element in seventh position: ";
        IntStack.insert(9, 7);
    }
    catch (std::logic_error &err)
    {
        cout << err.what() << endl;
    }

    try
    {
        cout << "Trying to erase an element in negative first position: ";
        IntStack.erase(-1);
    }
    catch (std::logic_error &err)
    {
        cout << err.what() << endl;
    }
}

