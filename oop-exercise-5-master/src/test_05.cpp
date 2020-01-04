#include "Shape.h"
#include "Stack.h"
using namespace std;

bool IsEven(int& e)
{
    return e % 2 == 0;
}

int main()
{
    Stack<int> IntStack;

    IntStack.push(0).push(1).push(2).push(3).push(4).push(5).push(6).push(7).push(8).push(9).push(10);

    cout << "Printing with for_each: ";
    for_each(IntStack.begin(), IntStack.end(), [](auto& e) {
        cout << e << " ";
        }
    );
    cout << endl;

    int amount = std::count_if(IntStack.begin(), IntStack.end(), IsEven);

    cout << "Amount of even elements: " << amount << endl;
}

