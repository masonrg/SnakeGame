#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{ 
	this->x = x;
	this->y = y;
}

float Vector2::magnitude() const
{
	return sqrt(sqrMagnitude());
}

float Vector2::sqrMagnitude() const
{
	return x * x + y * y;
}

float Vector2::distance(const Vector2 & v)
{
	return (v - *this).magnitude();
}

float Vector2::sqrDistance(const Vector2 & v)
{
	return (v - *this).sqrMagnitude();
}
