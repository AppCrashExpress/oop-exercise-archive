#include "Vector3D.h"
#include <cmath>

//---------------------------------------In-class functions

Vector& Vector::sum(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector& Vector::sub(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector& Vector::multVector(const Vector& rhs)
{
	x = y * rhs.z - z * rhs.y;
	y = z * rhs.x - x * rhs.z;
	z = x * rhs.y - y * rhs.x;
	return *this;
}
Vector& Vector::multByNum(const int v)
{
	x *= v; y *= v; z *= v;
	return *this;
}

double Vector::length() const
{
	return sqrt(x * x + y * y + z * z);
}

std::ostream& Vector::printVec(std::ostream& os)
{
	os << "( " << x << ", " << y << ", " << z << " )";
	return os;
}

bool Vector::equals(Vector& rhs) const
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

bool Vector::equalLength(Vector& rhs) const
{
	return std::abs(length() - rhs.length()) < 0.001;
}

//---------------------------------------Oustide class functions definition

Vector sum(const Vector& lhs, const Vector& rhs)
{
	Vector result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return result;
}

Vector sub(const Vector& lhs, const Vector& rhs)
{
	Vector result;
	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return result;
}

int multScalar(const Vector& lhs, const Vector& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}


Vector multVector(const Vector& lhs, const Vector& rhs)
{
	Vector result;
	result.x = lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

double angle(const Vector& lhs, const Vector& rhs)
{
	return acos( (double)multScalar(lhs, rhs) / (lhs.length() * rhs.length()) ) * 180 / M_PI;
}

