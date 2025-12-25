#ifndef VEC2_H
#define VEC2_H
class Vec2{
public:
	float x {0};
	float y {0};

	Vec2();
	Vec2(float xin, float yin);
	Vec2(float vec[2]);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const float& rhs) const;
 
	void operator += (const Vec2& rhs);
	void operator -= (const Vec2& rhs);
	void operator *= (const float& rhs);

	float distance(const Vec2& a) const;

	float length() const;
	
	void print() const;
};
#endif
