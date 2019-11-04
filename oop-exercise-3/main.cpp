/*
Вариант 1:
Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure.
Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:
1.   	Вычисление геометрического центра фигуры;
2.   	Вывод в стандартный поток вывода std::cout координат вершин фигуры; 3. Вычисление площади фигуры;

Создать программу, которая позволяет:
•       Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
•       Сохранять созданные фигуры в динамический массив std::vector<Figure*>
•   	Вызывать для всего массива общие функции (1-3 см. выше).
Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.

•       Необходимо уметь вычислять общую площадь фигур в массиве.
•       Удалять из массива фигуру по индексу;


Ефимов Александр Владимирович
M8O-201Б
*/


#include <vector>
#include <string>
#include <exception>
#include "Shape.h"
using namespace std;

struct list_empty : public std::exception
{
	const char* what() const throw ()
	{
		return "The list is currently empty";
	}
};

void PrintVec(const vector<Shape* >& l)
{
	int num = 1;
	for (auto &e : l)
	{
		cout << num << ". " << *e << endl;
		++num;
	}
}

double TotalArea(const vector<Shape* >& l)
{
	double res = 0;
	for (auto &e : l)
	{
		res += e->GetArea();
	}
	return res;
}

int main()
{
	vector<Shape* > ShapeVec;
	int k = 1, num;
	cout
		<< "1. Add shape\n"
		<< "2. Print all shapes\n"
		<< "3. Print total area of all shapes\n"
		<< "4. Print this menu\n"
		<< "5. Delete shape\n"
		<< "6. Delete all shapes\n"
		<< "0. Exit\n"
		<< flush;
	do
	{
		cout << "---------------\nMenu choice: ";
		try
		{
			cin >> k;
			if (!cin) throw runtime_error("Failed to get input");
			switch (k)
			{
			case 1 :
				cout << "1. Triangle\n"
					 << "2. Rectangle\n"
					 << "3. Square\n"
					 << "Any other number returns to menu\n"
					 << "Pick the type of shape: ";
				cin >> k;
				if (k >= 1 && k <= 3)
				{
					switch (k)
					{
					case 1:
						ShapeVec.push_back(new Triangle(cin));
						break;
					case 2:
						ShapeVec.push_back(new Rectangle(cin));
						break;
					case 3:
						ShapeVec.push_back(new Square(cin));
						break;
					}
				}
				k = 1;
				break;
			case 2 :
				if (ShapeVec.empty()) throw list_empty();
				PrintVec(ShapeVec);
				break;
			case 3 :
				if (ShapeVec.empty()) throw list_empty();
				cout << "The total area of all shapes is " << TotalArea(ShapeVec) << endl;
				break;
			case 4 :
				cout
					<< "1. Add shape\n"
					<< "2. Print all shapes\n"
					<< "3. Print total area of all shapes\n"
					<< "4. Print this menu\n"
					<< "5. Delete shape\n"
					<< "6. Delete all shapes\n"
					<< "0. Exit\n"
					<< endl;
				break;
			case 5 :
				if (ShapeVec.empty()) throw list_empty();
				cout << "Number of the shape: ";
				cin >> num;
				if (num < 1 || num > ShapeVec.size()) throw runtime_error("Incorrect index");
				delete ShapeVec[--num];
				ShapeVec.erase(ShapeVec.begin() + num);
				break;
			case 6 :
				if (ShapeVec.empty()) throw list_empty();
				for (auto &e : ShapeVec)
				{ delete e; }
				ShapeVec.erase(ShapeVec.begin(), ShapeVec.end());
				cout << "Vector is now empty" << endl;
				break;
			case 0 :
				break;
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
			cerr << "Exception thrown, but undefined. Please open an issue at GitHub with steps to reproduce ." << endl;
		}
	} while (k);
	return 0;
}
