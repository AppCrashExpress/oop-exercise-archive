#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
{
public:
	friend Vector sum(const Vector&, const Vector&);
	friend Vector sub(const Vector&, const Vector&);
	friend int    multScalar(const Vector&, const Vector&);
	friend Vector multVector(const Vector&, const Vector&);

	Vector(int X = 0, int Y = 0, int Z = 0) : x(X), y(Y), z(Z) {}
	Vector& setX(int);
	Vector& setY(int);
	Vector& setZ(int);

	Vector& sum(const Vector&);
	Vector& sub(const Vector&);
	Vector& multVector(const Vector&);
	Vector& multByNum(const int);

	std::ostream& printVec(std::ostream&);
	double length() const;
	bool   equals(Vector&) const;
	bool   equalLength(Vector&) const;
private:
	int x, y, z;
};

inline Vector& Vector::setX(int X) { x = X; return *this; }
inline Vector& Vector::setY(int Y) { y = Y; return *this; }
inline Vector& Vector::setZ(int Z) { z = Z; return *this; }

Vector sum(const Vector&, const Vector&);
Vector sub(const Vector&, const Vector&);
int    multScalar(const Vector&, const Vector&);
Vector multVector(const Vector&, const Vector&);
double angle(const Vector&, const Vector&);

#endif
