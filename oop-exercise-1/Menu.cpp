#include "Vector3D.h"
#include <list>
#include <exception>
using namespace std;

struct list_empty : public std::exception
{
	const char* what() const throw ()
	{
		return "The list is currently empty";
	}
};

void printList(list<Vector>& l, list<Vector>::iterator& it)
{
	int i = 1;
	for (auto point = l.begin(); point != l.end(); ++point)
	{
		if (point == it) cout << "* " << i << ". ";
		else cout << "  " << i << ". ";
		point->printVec(cout) << "\n";
		++i;
	}
	cout << flush;
}

int main()
{
	list<Vector> listVect;
	int k = 1, x = 0, y = 0, z = 0,
		i = 0;
	list<Vector>::iterator it = listVect.end(), it2 = listVect.end();
	cout
		<< "\n1. Create vector\n"
		<< "2. Print list of vectors\n"
		<< "3. Select vector to manipulate\n"
		<< "4. Delete selected vector\n"
		<< "5. Add of operation on two vectors to list\n"
		<< "6. Operate on selected vector\n"
		<< "7. Print the list again\n"
		<< "9. Clear list of vectors\n"
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
				cout << "Input x, y, z in this order: ";
				cin >> x >> y >> z;
				if (!cin) throw runtime_error("Failed to get input");
				listVect.emplace_back(x, y, z);
				break;

			case 2:
				if (listVect.empty()) throw list_empty();
				printList(listVect, it);
				break;

			case 3:
				if (listVect.empty()) throw list_empty();
				it = listVect.begin();
				cout << "Type number of vector(0 to deselect): ";
				cin >> i;
				if (cin && i > 0 && (unsigned)i <= listVect.size())
				{
					--i;
					advance(it, i);
				}
				else if (i == 0) it = listVect.end();
				else throw runtime_error("Incorrect number given");
				break;

			case 4:
				if (listVect.empty()) throw list_empty();
				if (it != listVect.end())
        {
					it = listVect.erase(it);
          cout << "Selected vector deleted" << endl;
        }
				else throw runtime_error("Invalid element selected");
				break;

			case 5:
				if (listVect.size() < 2) throw runtime_error("Less than 2 vectors in list");
				cout
					<< "1. Summation of two vectors\n"
					<< "2. Subtraction of two vectors\n"
					<< "3. Cross product of two vectors\n"
					<< "Any other number returns to main menu automatically\n"
					<< "Choice: ";
				cin >> k;
				if (k < 4 && k > 0)
				{
          printList(listVect, it);
          if (it == listVect.end())
          {
            cout << "Select first vector: ";
            if (cin >> i && i > 0 && (unsigned)i <= listVect.size())
            {
              --i;
              it = listVect.begin();
              advance(it, i);
            }
            else throw runtime_error("Incorrect input");
          }
					if (listVect.size() > 2)
					{
						cout << "Select a second vector: ";
            do
            {
							it2 = listVect.end();
							if (cin >> i && i > 0 && (unsigned)i <= listVect.size())
							{
								--i;
								it2 = listVect.begin();
								advance(it2, i);
							}
							else throw runtime_error("Incorrect input");
							if (it2 == it) cout << "The same vector was selected, select another: ";
						} while (it2 == listVect.end() || it2 == it);
					}
					else
          {
						for (it2 = listVect.begin(); it2 != listVect.end() && it2 == it; ++it2) { }
            cout << "Selecting the only vector left" << endl;
          }
				}

				switch (k)
				{
				case 1:
					listVect.push_back(sum(*it, *it2));
					break;
				case 2:
					listVect.push_back(sub(*it, *it2));
					break;
				case 3:
					listVect.push_back(multVector(*it, *it2));
					break;
				default:
					break;
				}
				k = 5;
				break;

			case 6:
				if (listVect.empty()) throw list_empty();
				if (it == listVect.end()) throw runtime_error("No vector selected");
				cout
					<< "1. Add another vector to selected\n"
					<< "2. Sub from selected vector another\n"
					<< "3. Put cross product into current selected vector\n"
					<< "4. Get scalar value of two vectors\n"
					<< "5. Test if vector is equal to selected\n"
					<< "6. Test if vector length is equal to selected\n"
					<< "7. Angle between selected vector and another\n"
					<< "8. Get length of selected vector\n"
					<< "9. Multiply selected vector by number\n"
					<< "Any other number returns to main menu automatically\n"
					<< "Choice: ";
				cin >> k;
				if (!cin) throw runtime_error("Failed to get input");
				if (k < 8 && k > 0) // Last two don't need a second vector
				{
					if (listVect.size() < 2) throw runtime_error("Less than 2 vectors in list");
					if (listVect.size() > 2)
					{
						printList(listVect, it);
						cout << "Select a second vector: ";
            do
						{
							if (it2 == it) cout << "The same vector selected, select another" << endl;
							it2 = listVect.end();
							if (cin >> i && i > 0 && (unsigned)i <= listVect.size())
							{
								--i;
								it2 = listVect.begin();
								advance(it2, i);
							}
							else throw runtime_error("Incorrect input");
						} while (it2 == listVect.end() || it2 == it);
					}
					else
          {
						for (it2 = listVect.begin(); it2 != listVect.end() && it2 == it; ++it2) { }
            cout << "Selecting the only vector left" << endl;
          }
				}

				switch (k)
				{
				case 1:
					it->sum(*it2);
					break;
				case 2:
					it->sub(*it2);
					break;
				case 3:
					it->multVector(*it2);
					break;
				case 4:
					cout << "Scalar value of selected vectors is " << multScalar(*it, *it2) << endl;
					break;
				case 5:
					if (it->equals(*it2)) cout << "They are equal" << endl;
					else cout << "They are not equal" << endl;
					break;
				case 6:
					if (it->equalLength(*it2)) cout << "Their length is equal" << endl;
					else cout << "Their length is not equal" << endl;
					break;
				case 7:
					cout << angle(*it, *it2) << " degrees" << endl;
					break;
				case 8:
					cout << it->length() << " of desired unit" << endl;
					break;
				case 9:
					int temp;
					cout << "Multiply by ";
					cin >> temp;
					it->multByNum(temp);
					break;
				default:
					break;
				}
				k = 6;
				break;

			case 7:
				cout
					<< "1. Create vector\n"
					<< "2. Print list of vectors\n"
					<< "3. Select vector to manipulate\n"
					<< "4. Delete selected vector\n"
					<< "5. Add of operation on two vectors to list\n"
					<< "6. Operate on selected vector\n"
					<< "7. Print the list again\n"
					<< "9. Clear list of vectors\n"
					<< endl;

			case 9:
				if (listVect.empty()) throw list_empty();
				listVect.clear();
				it = it2 = listVect.end();
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
			cerr << "Exception thrown, but undefined. Instead we will provide you with a fact:\nThe Schrodinger's cat paradox outlines a situation in which a cat in a box must be considered, for all intents and purposes, simultaneously alive and dead. Schrodinger created this paradox as a justification for killing cats." << endl;
		}
	} while (k);
	return 0;
}
