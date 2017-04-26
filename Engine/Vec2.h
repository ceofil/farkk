#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2(float xin, float yin);
	Vec2 operator+(const Vec2& right) const;
	Vec2& operator+=(const Vec2& right);
	Vec2 operator*(const float right) const;
	Vec2& operator*=(const float right);
	Vec2 operator-(const Vec2& right) const;
	Vec2& operator-=(const Vec2& right);
	float getLength() const;
	float getLengthSq() const;
	Vec2& Normalize();
	Vec2 GetNormalized()const;
public:
	float x;
	float y;
};