#pragma once

#include <iostream>

class Color 
{
	
#define COL_OVERFLOW(i) (i / 255 != 0)
#define COL_CLAMP_HI(x, i) (COL_OVERFLOW(i) ? 255 : (x + i > 255) ? 255 : x + i)
#define COL_CLAMP_LO(x, i) (COL_OVERFLOW(i) ? 0 : (x - i < 0) ? 0 : x - i)
#define COL_CLAMP(x, i) (COL_CLAMP_HI(COL_CLAMP_LO(x, i), i))
#define COL_TIMES(x, f) (COL_CLAMP(x, (int)(x * f)))

public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	//CONSTRUCTORS
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//PRESETS
	static Color white() { return Color(255, 255, 255); }
	static Color black() { return Color(0, 0, 0); }
	static Color grey() { return Color(127, 127, 127); }
	static Color red() { return Color(255, 0, 0); }
	static Color green() { return Color(0, 255, 0); }
	static Color blue() { return Color(0, 0, 255); }

	//ASSIGNMENT AND EQUALITY
	inline Color & operator = (const Color & c) { r = c.r; g = c.g; b = c.b; a = c.a; return *this; }
	inline Color & operator - (void) { r = 255 - r; g = 255 - g; b = 255 - b; return *this; }
	inline bool operator == (const Color & c) const { return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a); }
	inline bool operator != (const Color & c) const { return !(*this == c); }

	//SCALAR TO COLOR
	inline const Color operator + (int i) const { return Color(COL_CLAMP_HI(r, i), COL_CLAMP_HI(g, i), COL_CLAMP_HI(b, i), a); }
	inline const Color operator - (int i) const { return Color(COL_CLAMP_LO(r, i), COL_CLAMP_LO(g, i), COL_CLAMP_LO(b, i), a); }
	inline const Color operator * (float f) const { return Color(COL_TIMES(r, f), COL_TIMES(g, f), COL_TIMES(b, f), a); }

	//SCALAR TO THIS
	inline Color & operator += (int i) { r = COL_CLAMP_HI(r, i); g = COL_CLAMP_HI(g, i); b = COL_CLAMP_HI(b, i); return *this; }
	inline Color & operator -= (int i) { r = COL_CLAMP_LO(r, i); g = COL_CLAMP_LO(g, i); b = COL_CLAMP_LO(b, i); return *this; }
	inline Color & operator *= (float f) { r = COL_TIMES(r, f); g = COL_TIMES(g, f); b = COL_TIMES(b, f); return *this; }

	//STREAM TO THIS
	friend std::ostream & operator <<(std::ostream& stream, const Color& c) { return stream << "(" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "," << (int)c.a << ")"; }
};