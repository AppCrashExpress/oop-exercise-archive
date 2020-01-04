/*

������� ������ ������������ ���������, �������� �������� �������:
1.   	��������� ������ ���� ����������� � ������� ����� ���������� (std::shared_ptr, std::weak_ptr). ����������� ������������� std::unique_ptr;
2.   	� �������� ��������� ������� ��������� ������ ��������� ��� ������;
3.   	����������� forward_iterator �� ���������;
4.   	��������� ������ ���������� ��������� begin() �  end();
5.   	��������� ������ ��������� ����� ������� �� ������� ��������� insert(iterator);
6.   	��������� ������ ��������� ����� �������� �� ������� ��������� erase(iterator);
7.   	��� ���������� ������������ �������� (�������� ����� �� ������� ��������� ��� �������� �� ������������� ��������) ���������� ������������ ����������;
8.   	�������� ������ ���� ��������� �� ������������ ����������� (��������, std::count_if)
9.   	��������� ������ ��������� ����� �������:
            o ���� � pop, push, top; o ������� � pop, push, top;
            o ������, ������������ ������ � ������ � �������� �� ��������� [];
10.   	����������� ���������, �������:
            o ��������� ������� � ���������� ������ (� ����� int � �������� ��������� ������� ������) � ��������� � ���������;
            o ��������� ������� ������� �� ��������� �� ������ ��������; o ������� �� ����� ��������� ������ c ������� std::for_each;
            o ������� �� ����� ���������� ��������, � ������� ������� ������ �������� (� ������� std::count_if);

������� 1: �����������, �������, �������������.

������ ��������� ������������
M8O-201�
*/


#include <iostream>
#include <string>
#include <exception>
#include "Stack.h"
#include "Shape.h"
using namespace std;

struct stack_empty : public std::exception
{
    const char* what() const throw ()
    {
        return "The stack is currently empty";
    }
};

void PrintStack(const Stack< Square<int> >& stack)
{
    int num = 1;
    for_each(stack.begin(), stack.end(), [&num](auto& e)
    {
        cout << num << ". " << e << endl;
        ++num;
    });
}

int GetNum(void)
{
    int k;
    bool got = false;
    while (!got)
    {
        cin >> k;
        if (!cin.good())
        {
            cout << "Bad input ignored:  " << flush;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else got = true;
    }
    return k;
}

int main()
{
    Stack< Square<int> > SquareStack;
    Square<int> buff;
    int k = 1;
    size_t num;
    double MaxArea;
    cout
      << "\n1. Add square\n"
        << "2. Print all elements\n"
        << "3. Amount of squares, which have area less than\n"
        << "4. Print this menu\n"
        << "5. Delete element\n"
        << "6. Delete all elements\n"
        << "0. Exit\n"
        << flush;
    do
    {
        cout << "---------------\nMenu choice: ";
        try
        {
            k = GetNum();
            if (!cin) throw runtime_error("Failed to get input");
            switch (k)
            {
            case 1:
                cin >> buff;
                SquareStack.push(buff);
                k = 1;
                break;
            case 2:
                if (SquareStack.empty()) throw stack_empty();
                PrintStack(SquareStack);
                break;
            case 3:
                if (SquareStack.empty()) throw stack_empty();
                cout << "Max area: ";
                cin >> MaxArea;
                cout << "The amount of squares that are equal or lower is " << count_if( SquareStack.begin(), SquareStack.end(), [&MaxArea](auto& sqr) -> bool
                    {
                        return ( !sqr.abstract && (sqr.area < MaxArea || DoubleEqual(sqr.area, MaxArea)) );
                    }
                ) << endl;
                break;
            case 4:
                cout
                      << "1. Add square\n"
                      << "2. Print all elements\n"
                      << "3. Amount of squares, which have area less than\n"
                      << "4. Print this menu\n"
                      << "5. Delete element\n"
                      << "6. Delete all elements\n"
                      << "0. Exit\n"
                    << endl;
                break;
            case 5:
                if (SquareStack.empty()) throw stack_empty();
                cout << "Number of the square: ";
                num = GetNum();
                if (num < 1 || num > SquareStack.size()) throw runtime_error("Incorrect index");
                SquareStack.erase(num - 1);
                break;
            case 6:
                SquareStack.erase();
                cout << "Stack erased" << endl;
                break;
            case 0:
                break;
            default:
                cout << "No such number" << endl;
            }

        }
        catch (stack_empty& err)
        {
            cout << err.what() << endl;
        }
        catch (runtime_error& err)
        {
            cerr << err.what() << endl;
        }
        catch (logic_error & err)
        {
            cerr << "In stack: " << err.what() << endl;
        }
        catch (...)
        {
            cerr << "Exception thrown, but undefined. Please open an issue at GitHub with steps to reproduce ." << endl;
        }
    } while (k);
    return 0;
}
