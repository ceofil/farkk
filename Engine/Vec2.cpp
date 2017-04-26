#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float xin, float yin)
{
	x = xin;
	y = yin;
}

Vec2 Vec2::operator+(const Vec2 & right) const
{
	return Vec2(x + right.x, y + right.y);
}

Vec2 & Vec2::operator+=(const Vec2 & right)
{
	return *this = *this + right;
}

Vec2 Vec2::operator*(const float right) const
{
	return Vec2(x*right,y*right);
}

Vec2 & Vec2::operator*=(const float right)
{
	
	return *this = *this * right; 
}

Vec2 Vec2::operator-(const Vec2 & right) const
{
	return Vec2(x-right.x,y-right.y);
}

Vec2 & Vec2::operator-=(const Vec2 & right)
{
	return *this = *this - right;
}

float Vec2::getLength() const
{
	return std::sqrt (getLengthSq());
}

float Vec2::getLengthSq() const
{
	return	x * x + y * y;
}

Vec2 & Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float len = getLength();
	if(len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}
