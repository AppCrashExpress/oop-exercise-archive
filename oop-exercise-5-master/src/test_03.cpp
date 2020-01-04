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

    cout << "Inserting 5 after second 7 and before 0: ";
    IntStack.insert(3, 5); // Now it should have 5 after second 7 and before 0

    for (auto begin = IntStack.begin(), end = IntStack.end(); begin != end; ++begin)
        cout << *(begin) << " ";
    cout << endl;

    cout << "Deleting sixth element: ";
    IntStack.erase(5); // Now the sixth element, 1, will disappear with my stand, Za Hando da!

    for (auto begin = IntStack.begin(), end = IntStack.end(); begin != end; ++begin)
        cout << *(begin) << " ";
    cout << endl;
}

