/*
Вариант 11:
Создать класс BitString для работы с 128-битовыми строками. Битовая строка должна быть представлена двумя полями типа unsigned long long.
Должны быть реализованы все традиционные операции для работы с битами: and, or, xor, not. 
Реализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное количество битов.
Реализовать операцию вычисления количества единичных битов, операции сравнения по количеству единичных битов. 
Реализовать операцию проверки включения.
Операции and, or, xor, not, >>, << , сравнения (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов.
Необходимо реализовать пользовательский литерал для работы с константами типа BitString.

Ефимов Александр Владимирович
M8O-201Б
*/


#include <list>
#include <string>
#include <exception>
#include "ByteString.h"
using namespace std;

struct list_empty : public std::exception
{
	const char* what() const throw ()
	{
		return "The list is currently empty";
	}
};

void printList(list<ByteString>& l, list<ByteString>::iterator& sel)
{
	int num = 1;
	for (auto i = l.begin(); i != l.end(); ++i)
	{
		if (i == sel) cout << "* " << num << ". ";
		else cout << "  " << num << ". ";
		cout << *i << endl;
		++num;
	}
	cout << flush;
}

int main()
{
	list<ByteString> listByte;
	listByte.emplace_back("101101"_b);
	ByteString temp;
	int k = 1, num1, num2,
		i = 0;
	list<ByteString>::iterator it, it2;
	it = it2 = listByte.end();
	cout
		<< "\n1. Add byte string\n"
		<< "2. Print list of byte strings\n"
		<< "3. Select byte string to manipulate\n"
		<< "4. Delete selected byte_string\n"
		<< "5. Add operation on byte strings to list\n"
		<< "6. Operate on selected byte string\n"
		<< "7. Compare two byte strings\n"
		<< "8. Print the list again\n"
		<< "9. Clear list of byte strings\n"
		<< endl;
	do
	{
		cout << "\n---------------\nMenu choice: ";
		try
		{
			cin >> k;
			if (!cin) throw runtime_error("Failed to get input");
			switch (k)
			{
			case 1:
				cout << "Input format (1 for numbers, 2 for string): ";
				if (cin >> k)
				{
					if (k == 1)
					{
						cout << "Input byte string in two numbers: ";
						cin >> num1 >> num2;
						if (!cin) throw runtime_error("Failed to get input");
						listByte.emplace_back(num1, num2);
					}
					else if (k == 2)
					{
						cout << "Input byte string in bits: ";
						if (cin >> temp) listByte.push_back(temp);
						else
						{
							k = 1;
							throw runtime_error("Failed to get input");
						}
					}
					k = 1;
				}
				else
				{
					k = 1;
					throw runtime_error("Failed to get input");
				}
				break;

			case 2:
				if (listByte.empty()) throw list_empty();
				printList(listByte, it);
				break;

			case 3:
				if (listByte.empty()) throw list_empty();
				it = listByte.begin();
				cout << "Type number of string (0 to deselect): ";
				cin >> i;
				if (cin && i > 0 && (unsigned)i <= listByte.size())
				{
					--i;
					advance(it, i);
				}
				else if (i == 0) it = listByte.end();
				else throw runtime_error("Incorrect number given");
				break;

			case 4:
				if (listByte.empty()) throw list_empty();
				if (it != listByte.end())
				{
					it = listByte.erase(it);
					cout << "Selected byte string deleted" << endl;
				}
				else throw runtime_error("Invalid element selected");
				break;

			case 5:
				if (listByte.empty()) throw list_empty();
				if (listByte.size() < 2) throw runtime_error("Less than 2 strings in list");
				cout
					<< "1. Shift bits left  result\n"
					<< "2. Shift bits right result\n"
					<< "3. AND of two byte strings\n"
					<< "4. OR  of two byte strings\n"
					<< "5. XOR of two byte strings\n"
					<< "Any other number returns to main menu automatically\n"
					<< "Choice: ";
				cin >> k;
				if (!cin) throw runtime_error("Failed to get input");
				if (k >= 1 && k <= 2)
				{
					printList(listByte, it);
					cout << "Select byte string: ";
					if (cin >> i && i > 0 && (unsigned)i <= listByte.size())
					{
						--i;
						it = listByte.begin();
						advance(it, i);
					}
					else throw runtime_error("Incorrect input");
				}
				else if (k <= 5 && k >= 3)
				{
					printList(listByte, it);
					if (it == listByte.end())
					{
						cout << "Select first byte string: ";
						if (cin >> i && i > 0 && (unsigned)i <= listByte.size())
						{
							--i;
							it = listByte.begin();
							advance(it, i);
						}
						else throw runtime_error("Incorrect input");
					}
					if (listByte.size() > 2)
					{
						cout << "Select a second byte string: ";
						it2 = listByte.end();
						do
						{
							it2 = listByte.end();
							if (cin >> i && i > 0 && (unsigned)i <= listByte.size())
							{
								--i;
								it2 = listByte.begin();
								advance(it2, i);
							}
							else throw runtime_error("Incorrect input");
							if (it2 == it) cout << "The same string was selected, select another: ";
						} while (it2 == listByte.end() || it2 == it);
					}
					else
					{
						for (it2 = listByte.begin(); it2 != listByte.end() && it2 == it; ++it2) {}
						cout << "Selecting the only byte string left" << endl;
					}
				}

				switch (k)
				{
				case 1:
					cout << "Shift by: ";
					cin >> num1;
					if (!cin) throw runtime_error("Failed to get input");
					listByte.push_back(*it << num1);
					break;
				case 2:
					cout << "Shift by: ";
					cin >> num1;
					if (!cin) throw runtime_error("Failed to get input");
					listByte.push_back(*it >> num1);
					break;
				case 3:
					listByte.push_back(*it & *it2);
					break;
				case 4:
					listByte.push_back(*it | *it2);
					break;
				case 5:
					listByte.push_back(*it ^ *it2);
					break;
				default:
					break;
				}
				k = 5;
				break;

			case 6:
				if (listByte.empty()) throw list_empty();
				if (it == listByte.end()) throw runtime_error("No byte string selected");
				cout
					<< "1. AND operation on selected byte string with another\n"
					<< "2. OR  operation on selected byte string with another\n"
					<< "3. XOR operation on selected byte string with another\n"
					<< "4. Check inclusion of another string in selected\n"
					<< "5. Check if amount of 1's in byte strings is equal\n"
					<< "6. Return amount of 1's in the string\n"
					<< "7. Shift bits left\n"
					<< "8. Shift bits right\n"
					<< "9. Flip bits on selected bit string\n"
					<< "Any other number returns to main menu automatically\n"
					<< "Choice: ";
				cin >> k;
				if (!cin) throw runtime_error("Failed to get input");
				if (k <= 5 && k >= 1)
				{
					if (listByte.size() < 2) throw runtime_error("Less than 2 byte strings in list");
					if (listByte.size() > 2)
					{
						printList(listByte, it);
						it2 = listByte.end();
						cout << "Select a second byte string: ";
						do
						{
							if (it2 == it) cout << "The same byte string selected, select another: " << endl;
							it2 = listByte.end();
							if (cin >> i && i > 0 && (unsigned)i <= listByte.size())
							{
								--i;
								it2 = listByte.begin();
								advance(it2, i);
							}
							else throw runtime_error("Incorrect input");
						} while (it2 == listByte.end() || it2 == it);
					}
					else
					{
						for (it2 = listByte.begin(); it2 != listByte.end() && it2 == it; ++it2) {}
						cout << "Selecting the only byte string left" << endl;
					}
				}

				switch (k)
				{
				case 1:
					*it &= *it2;
					break;
				case 2:
					*it |= *it2;
					break;
				case 3:
					*it ^= *it2;
					break;
				case 4:
					cout << "Selected string " << (it->includes(*it2) ? "includes" : "does not include") << " another string" << endl;
					break;
				case 5:
					cout << "Selected strings " << (CompareOnes(*it, *it2) ? "have" : "do not have") << " the same amount of 1's" << endl;
					break;
				case 6:
					cout << "Selected strings " << it->Ones() << " of 1's" << endl;
					break;
				case 7:
					cout << "Shift by: ";
					cin >> num1;
					if (!cin) throw runtime_error("Failed to get input");
					*it <<= num1;
					break;
				case 8:
					cout << "Shift by: ";
					cin >> num1;
					if (!cin) throw runtime_error("Failed to get input");
					*it >>= num1;
					break;
				case 9:
					~*it;
					break;
				default:
					break;
				}
				k = 6;
				break;

			case 7:
				if (listByte.size() < 2) throw runtime_error("Less than 2 strings in list");
				printList(listByte, it);
				if (it == listByte.end())
				{
					cout << "Select first byte string: ";
					if (cin >> i && i > 0 && (unsigned)i <= listByte.size())
					{
						--i;
						it = listByte.begin();
						advance(it, i);
					}
					else throw runtime_error("Incorrect input");
				}
				if (listByte.size() > 2)
				{
					cout << "Select a second byte string: ";
					do
					{
						it2 = listByte.end();
						if (cin >> i && i > 0 && (unsigned)i <= listByte.size())
						{
							--i;
							it2 = listByte.begin();
							advance(it2, i);
						}
						else throw runtime_error("Incorrect input");
						if (it2 == it) cout << "The same string was selected, select another: ";
					} while (it2 == listByte.end() || it2 == it);
				}
				else
				{
					for (it2 = listByte.begin(); it2 != listByte.end() && it2 == it; ++it2) {}
					cout << "Selecting the only vector left" << endl;
				}

				if (*it == *it2)
				{
					cout << "Selected byte strings are equal" << endl;
					break;
				}
				cout << (*it > * it2 ? "First" : "Second") << " string is bigger than the other" << endl;
				break;

			case 8:
				cout
					<< "1. Add byte string\n"
					<< "2. Print list of byte strings\n"
					<< "3. Select byte string to manipulate\n"
					<< "4. Delete selected byte_string\n"
					<< "5. Add operation on byte strings to list\n"
					<< "6. Operate on selected byte string\n"
					<< "7. Compare two byte strings\n"
					<< "8. Print the list again\n"
					<< "9. Clear list of byte strings\n"
					<< endl;
				break;

			case 9:
				if (listByte.empty()) throw list_empty();
				listByte.clear();
				it = it2 = listByte.end();
				cout << "List clear" << endl;
				break;

			case 0:
				break;

			default:
				cout << "Incorrect menu choice" << endl;
			}
		}
		catch (list_empty& err)
		{
			cout << err.what() << endl;
		}
		catch (runtime_error& err)
		{
			cerr << err.what() << endl;
		}
		catch (...)
		{
			cerr << "Exception thrown, but undefined. Please open an issue at GitHub." << endl;
		}
	} while (k);
	return 0;
}
