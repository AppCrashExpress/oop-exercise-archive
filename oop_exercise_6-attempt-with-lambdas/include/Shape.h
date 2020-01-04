#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <utility>
#include <cmath>

typedef std::pair<double, double> DoublePoint;

template <typename T>
class Square {
public:
    typedef std::pair<T, T> Point;

    Square() : centre(DoublePoint(0,0)), area(0)
    {
        for (int i = 0; i < 4; ++i)
            p[i].first = p[i].second = 0;
    }

    bool abstract = false;

    std::pair<double, double> centre;
    double area{ 0 };
    Point p[4];
};

//-----------------------------------------------------------------------------------------------------------

bool DoubleEqual(double lhs, double rhs)
{
    const double EPS = 0.00001;
    if (lhs > rhs)
        return (lhs - rhs) < EPS ? true : false;
    else
        return (rhs - lhs) < EPS ? true : false;
}

bool IsRight(std::pair<double, double> a, std::pair<double, double> b, std::pair<double, double> c)
{
    std::pair<double, double> vec1 = { b.first - a.first, b.second - a.second };
    std::pair<double, double> vec2 = { c.first - a.first, c.second - a.second };

    double result = vec1.first * vec2.first + vec1.second * vec2.second;
    if (DoubleEqual(result, 0)) return true;
    return false;
}

bool IsRight(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c)
{
    std::pair<int, int> vec1 = { b.first - a.first, b.second - a.second };
    std::pair<int, int> vec2 = { c.first - a.first, c.second - a.second };

    int result = vec1.first * vec2.first + vec1.second * vec2.second;
    if (result == 0) return true;
    return false;
}

//-----------------------------------------------------------------------------------------------------------

template <class T>
bool IsRectangle(std::pair<T, T> p[4])
{
    std::pair<T, T> null(0, 0);
    if (p[0] == null && p[1] == null && p[2] == null && p[3] == null) return false;

    if (
            IsRight(p[2], p[1], p[3]) &&
            IsRight(p[3], p[2], p[0]) &&
            IsRight(p[1], p[0], p[2]) &&
            IsRight(p[0], p[3], p[1])
        ) return true;
    return false;
}

//-----------------------------------------------------------------------------------------------------------

template <class T>
inline double distance(std::pair<T, T> a, std::pair<T, T> b)
{
    return (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
}

template <class T>
bool IsSquare(std::pair<T, T> p[4])
{
    if (
            IsRectangle(p) &&
            DoubleEqual(distance(p[0], p[1]), distance(p[1], p[2])) &&
            DoubleEqual(distance(p[1], p[2]), distance(p[2], p[3])) &&
            DoubleEqual(distance(p[2], p[3]), distance(p[3], p[0])) &&
            DoubleEqual(distance(p[3], p[0]), distance(p[0], p[1]))
        ) return true;
    return false;
}

//-----------------------------------------------------------------------------------------------------------

template <class T>
DoublePoint Centre(Square<T>& sqr)
{
    DoublePoint res(0, 0);
    for (int i = 0; i < 4; ++i)
    {
        res.first += sqr.p[i].first;
        res.second += sqr.p[i].second;
    }
    res.first /= 4;
    res.second /= 4;
    return res;
}

template <class T>
double Area(Square<T>& sqr)
{
    return sqrt(distance(sqr.p[0], sqr.p[1]) * distance(sqr.p[1], sqr.p[2]));
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::pair<T, T>& p)
{
    os << '(' << p.first << " , " << p.second << ')';
    return os;
}

template <class T>
std::ostream& operator << (std::ostream& os, Square<T>& sqr)
{
    if (sqr.abstract)
        os << "Abstract: ";
    else
        os << "Square: ";
    os << sqr.p[0] << "; " << sqr.p[1] << "; " << sqr.p[2] << "; " << sqr.p[3] << "; Centre = " << sqr.centre << "; Area = " << sqr.area;
    return os;
}

//-----------------------------------------------------------------------------------------------------------

bool operator == (std::pair<int, int> lhs, std::pair<int, int> rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

bool operator == (std::pair<double, double> lhs, std::pair<double, double> rhs)
{
    return DoubleEqual(lhs.first, rhs.first) && DoubleEqual(lhs.second, rhs.second);
}

template <class T>
std::istream& operator >> (std::istream& is, Square<T>& sqr)
{
    std::cout << "Input point coordinates clockwise or counter clockwise\nA: ";
    is >> sqr.p[0].first >> sqr.p[0].second;
    std::cout << "B: ";
    is >> sqr.p[1].first >> sqr.p[1].second;
    std::cout << "C: ";
    is >> sqr.p[2].first >> sqr.p[2].second;
    std::cout << "D: ";
    is >> sqr.p[3].first >> sqr.p[3].second;

    if (IsSquare(sqr.p)) sqr.abstract = false;
    else sqr.abstract = true;

    sqr.centre = Centre(sqr);
    sqr.area = Area(sqr);
    return is;
}

#endif
