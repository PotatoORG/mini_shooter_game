#include "Vec2.h"
#include <cmath>
#include <iostream>


Vec2::Vec2() {}

Vec2::Vec2(float vec[2]){
	x = vec[0];
	y = vec[1];
}

Vec2::Vec2(float xin, float yin)
	: x (xin)
	, y (yin){
	}

bool Vec2::operator == (const Vec2& rhs) const{
	return ((x == rhs.x) && (y == rhs.y));
}

bool Vec2::operator != (const Vec2& rhs) const{
	return ((x != rhs.x) && (y != rhs.y));
}

Vec2 Vec2::operator + (const Vec2& rhs) const{
	return Vec2(x + rhs.x, y + rhs.y);
}


Vec2 Vec2::operator - (const Vec2& rhs) const{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float& rhs) const{
	return Vec2(x*rhs, y*rhs);
}


void Vec2::operator += (const Vec2& rhs){
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs){
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator *= (const float& rhs){
	x *= rhs;
	y *= rhs;
}

float Vec2::distance(const Vec2& a) const{
	return std::sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y));
}

float Vec2::length() const{
	return std::sqrt(x*x + y*y);
}

void Vec2::print() const{
	std::cout << "(" << x << ", " << y << ")\n";
}
