#ifndef SHAPE_BASE_H
#define SHAPE_BASE_H

#include <iostream>

class Shape {
public:
    friend std::ostream& operator << (std::ostream&, const Shape&);

    struct Point {
        int x {0};
        int y {0};
        bool operator == (const Point& rhs)
        { return x == rhs.x && y == rhs.y; }
    };
    Point GetCentre() const
    { return centre; }

    double GetArea() const
    { return area; }

protected:
    Point centre;
    double area{0};

private:
    virtual Point Centre() const = 0;
    virtual double Area() const = 0;
    virtual std::ostream& print(std::ostream&) const = 0;
};

class Triangle : public Shape {
public:
    Triangle () { }
    Triangle (std::istream&);

    Point Centre() const override;
    double Area() const override;
    std::ostream& print(std::ostream&) const override;
private:
    Point p[3];
};

class Rectangle : public Shape {
public:
    Rectangle () { }
    Rectangle (std::istream&);

    Point Centre() const override;
    double Area() const override;
    std::ostream& print(std::ostream&) const override;
private:
    Point p[4];
};

class Square : public Shape {
public:
    Square () { }
    Square (std::istream&);

    Point Centre() const override;
    double Area() const override;
    std::ostream& print(std::ostream&) const override;

private:
    Point p[4];
};

#endif