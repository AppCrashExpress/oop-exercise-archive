#include <cmath>
#include <exception>
#include "Shape.h"
typedef Shape::Point Point;

    //Auxiliary fuctions
bool IsRight(Point a, Point b, Point c)
{
    Point vec1 = {b.x - a.x, b.y - a.y}, vec2 = {c.x - a.x, c.y - a.y};
    if ( (vec1.x * vec2.x + vec1.y * vec2.y) == 0 ) return true;
    return false;
}

bool IsRectangle(Point p[4])
{
    if (
        IsRight(p[2], p[1], p[3]) &&
        IsRight(p[3], p[2], p[0]) &&
        IsRight(p[1], p[0], p[2]) &&
        IsRight(p[0], p[3], p[1])
    ) return true;
    return false;
}

inline int distance(Point a, Point b)
{
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

bool IsSquare(Point p[4])
{
	if (
		distance(p[0], p[1]) == distance(p[1], p[2]) &&
		distance(p[1], p[2]) == distance(p[2], p[3]) &&
		distance(p[2], p[3]) == distance(p[3], p[0]) &&
		distance(p[3], p[0]) == distance(p[0], p[1])
		) return true;
	return false;
}

    // Declaring the printing operator for all
std::ostream& operator << (std::ostream& os, const Shape& shape)
{
    shape.print(os);
    return os;
}

std::ostream& operator << (std::ostream& os, const Point& p)
{
    os << '(' << p.x << " , " << p.y << ')';
    return os;
}


    //Defining the triangle
Triangle::Triangle(std::istream& is)
{
    std::cout << "Input point coordinates\nA: ";
    is >> p[0].x >> p[0].y;
    std::cout <<"B: ";
    is >> p[1].x >> p[1].y;
    std::cout <<"C: ";
    is >> p[2].x >> p[2].y;

    if (
        p[0] == p[1] || p[0] == p[2] || p[1] == p[2]
    ) throw std::runtime_error("Coordinates do not create triangle");

    centre = Centre();
    area = Area();
}


Point Triangle::Centre() const
{
    Point o;
    o.x = (p[0].x + p[1].x + p[2].x) / 3;
    o.y = (p[0].y + p[1].y + p[2].y) / 3;
    return o;
}

double Triangle::Area() const
{
    double area = (double) (p[0].x * (p[1].y - p[2].y) + p[1].x * (p[2].y - p[0].y) + p[2].x * (p[0].y - p[1].y)) / 2;
    return area < 0 ? -area : area;
}

std::ostream& Triangle::print(std::ostream& os) const
{
    os << "Triangle: " << p[0] << "; " << p[1] << "; " << p[2] << "; Centre = " << centre << "; Area = " << area;
    return os;
}


    //Defining the rectangle
Rectangle::Rectangle(std::istream& is)
{
    std::cout << "Input point coordinates clockwise or counter clockwise\nA: ";
    is >> p[0].x >> p[0].y;
    std::cout <<"B: ";
    is >> p[1].x >> p[1].y;
    std::cout <<"C: ";
    is >> p[2].x >> p[2].y;
    std::cout <<"D: ";
    is >> p[3].x >> p[3].y;

    centre = Centre();
    area = Area();

    if (!IsRectangle(p)) throw std::runtime_error("Coordinates do not create rectangle");

}

Point Rectangle::Centre() const
{
    Point o;
    o.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
    o.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4; 
    return o;  
}

double Rectangle::Area() const
{
	return sqrt( distance(p[0], p[1]) * distance(p[1], p[2]) );
}

std::ostream& Rectangle::print(std::ostream& os) const
{
    os << "Rectangle: " << p[0] << "; " << p[1] << "; " << p[2] << "; " << p[3] << "; Centre = " << centre << "; Area = " << area;
    return os;
}

    //Defining square
Square::Square (std::istream& is)
{
    std::cout << "Input point coordinates clockwise or counter clockwise\nA: ";
    is >> p[0].x >> p[0].y;
    std::cout <<"B: ";
    is >> p[1].x >> p[1].y;
    std::cout <<"C: ";
    is >> p[2].x >> p[2].y;
    std::cout <<"D: ";
    is >> p[3].x >> p[3].y;
    centre = Centre();
    area = Area();

	if (!IsRectangle(p) || !IsSquare(p) ) throw std::runtime_error("Coordinates do not create square");
}
Point Square::Centre() const
{
    Point o;
    o.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
    o.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4; 
    return o;  
}

double Square::Area() const
{
	return sqrt( distance(p[0], p[1]) * distance(p[1], p[2]) );
}


std::ostream& Square::print(std::ostream& os) const
{
    os << "Square: " << p[0] << "; " << p[1] << "; " << p[2] << "; " << p[3] << "; Centre = " << centre << "; Area = " << area;
    return os;
}
