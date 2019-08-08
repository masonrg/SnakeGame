#pragma once

#include <iostream>

class Vector2
{
public:
	float x;
	float y;

	//CONSTRUCTORS
	Vector2();
	Vector2(float x, float y);

	//METHODS
	float magnitude() const;
	float sqrMagnitude() const;
	float distance(const Vector2 & v);
	float sqrDistance(const Vector2 & v);

	//ASSIGNMENT AND EQUALITY
	inline Vector2 & operator = (const Vector2 & v) { x = v.x; y = v.y; return *this; }
	inline Vector2 & operator = (const float & f) { x = f; y = f; return *this; }
	inline Vector2 & operator - (void) { x = -x; y = -y; return *this; }
	inline bool operator == (const Vector2 & v) const { return (x == v.x) && (y == v.y); }
	inline bool operator != (const Vector2 & v) const { return (x != v.x) || (y != v.y); }

	//VECTOR2 TO VECTOR2
	inline const Vector2 operator + (const Vector2 & v) const { return Vector2(x + v.x, y + v.y); }
	inline const Vector2 operator - (const Vector2 & v) const { return Vector2(x - v.x, y - v.y); }
	inline const Vector2 operator * (const Vector2 & v) const { return Vector2(x * v.x, y * v.y); }
	inline const Vector2 operator / (const Vector2 & v) const { return Vector2(x / v.x, y / v.y); }

	//VECTOR2 TO THIS
	inline Vector2 & operator += (const Vector2 & v) { x += v.x; y += v.y; return *this; }
	inline Vector2 & operator -= (const Vector2 & v) { x -= v.x; y -= v.y; return *this; }
	inline Vector2 & operator *= (const Vector2 & v) { x *= v.x; y *= v.y; return *this; }
	inline Vector2 & operator /= (const Vector2 & v) { x /= v.x; y /= v.y; return *this; }

	//SCALAR TO VECTOR2
	inline const Vector2 operator + (float v) const { return Vector2(x + v, y + v); }
	inline const Vector2 operator - (float v) const { return Vector2(x - v, y - v); }
	inline const Vector2 operator * (float v) const { return Vector2(x * v, y * v); }
	inline const Vector2 operator / (float v) const { return Vector2(x / v, y / v); }

	//SCALAR TO THIS
	inline Vector2 & operator += (float v) { x += v; y += v; return *this; }
	inline Vector2 & operator -= (float v) { x -= v; y -= v; return *this; }
	inline Vector2 & operator *= (float v) { x *= v; y *= v; return *this; }
	inline Vector2 & operator /= (float v) { x /= v; y /= v; return *this; }

	//STREAM TO THIS
	friend std::ostream & operator <<(std::ostream& stream, const Vector2& v) { return stream <<"(" << v.x << "," << v.y << ")"; }
};