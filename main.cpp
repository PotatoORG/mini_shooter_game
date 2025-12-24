#include "Vec2.h"

int main(){
	Vec2 vec(3.0, 4.5);
	vec.print();

	Vec2 vec2(1, 3);
	(vec2 + vec).print();
	(vec2 - vec).print();
	vec2 += vec2;
	vec2.print();
	Vec2 vec1 = vec2*3 + vec*2;
	vec1.print();
	return 0;
}
