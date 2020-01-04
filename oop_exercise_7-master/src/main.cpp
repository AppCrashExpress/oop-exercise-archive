//================================================//
// Ефимов А.В.                                    //
// M8O-201Б                                       //
// Вариант 1: Треугольник, Прямоугольник, Квадрат //
//================================================//

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <memory>

#include "Shape.h"
#include "Command.h"
using namespace std;

using WorkingType = int; 

void getMenu()
{
    cout
      << "\n1. Add shape\n"
        << "2. Print all elements\n"
        << "3. Delete element\n"
        << "4. Undo\n"
        << "5. Redo\n"
        << "6. Print this menu\n"
        << "7. Reload document\n"
        << "8. Load document\n"
        << "9. Save document\n"
        << "0. Exit" << endl;
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
    std::vector< std::shared_ptr<Shape<WorkingType>> > shapes;
    CommandManager<WorkingType> Commander(shapes);
    std::pair<WorkingType, WorkingType> points[4];

    int figNum = 1;
    int k = 1;

    getMenu();
    do
    {
        cout << "-----------------------\nMenu choice: ";
        try
        {
            k = GetNum();
            if (!cin) throw runtime_error("Failed to get input");
            switch (k)
            {
            case 1:
				cout
                    << "1. Triangle\n"
					<< "2. Rectangle\n"
					<< "3. Square\n"
					<< "Any other number returns to menu\n"
					<< "Pick the type of shape: ";
				k = GetNum();
				if (k >= 1 && k <= 3)
				{
                    --k;
                    switch (k)
                    {
                    case 0:
                        std::cout << "Input point coordinates\nA: ";
                        cin >> points[0].first >> points[0].second;
                        std::cout << "B: ";
                        cin >> points[1].first >> points[1].second;
                        std::cout << "C: ";
                        cin >> points[2].first >> points[2].second;
                        break;
                    
                    case 1:
                        // Intentionally empty

                    case 2:
                        std::cout << "Input point coordinates clockwise or counter clockwise\nA: ";
                        std::cin >> points[0].first >> points[0].second;
                        std::cout << "B: ";
                        std::cin >> points[1].first >> points[1].second;
                        std::cout << "C: ";
                        std::cin >> points[2].first >> points[2].second;
                        std::cout << "D: ";
                        std::cin >> points[3].first >> points[3].second;
                        break;
                    
                    default:
                        break;
                    }
                    Commander.add(make_shared< Add<WorkingType> >(shapes, k, points));
				}
				k = 1;
				break;
            case 2:
                if (shapes.empty())
                {
                    cout << "No shapes inserted" << endl;
                }
                else
                {
                    for (std::shared_ptr< Shape<WorkingType> > e : shapes)
                    {
                        std::cout << figNum++ << ". " << *e << "\n";
                    }
                    figNum = 1;
                }
                break;
            case 3:
                if (shapes.empty()) throw runtime_error("No shapes to delete");
                cout << "Number of the shape: ";
                k = GetNum();
                if (k < 1 || k > shapes.size()) throw runtime_error("Incorrect index");
                Commander.add(make_shared< Delete<WorkingType> >(shapes, --k));
                k = 5;
                break;
            case 4:
                Commander.undo();
                break;
            case 5:
                Commander.redo();
                break;
            case 6:
                getMenu();
                break;
            case 7:
                Commander.reload();
                std::cout << "Reload completed." << std::endl;
                break;
            case 8:
                Commander.load();
                break;
            case 9:
                Commander.save();
                break;
            case 0:
                break;
            default:
                cout << "No such number" << endl;
            }

        }
        catch (runtime_error& err)
        {
            cerr << err.what() << endl;
        }
        catch (commander_error& err)
        {
            cerr << "Commander: " << err.what() << endl;
        }
        catch (logic_error& err)
        {
            cerr << err.what() << endl;
        }
        catch (...)
        {
            cerr << "Exception thrown, but undefined." << endl;
        }
    } while (k);
    return 0;
}
