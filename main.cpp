#include "Vec2.h"
#include "Game.h"

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

	Vec2 v3 = Vec2({3.0, 4.1});
	v3.print();

	Vec2 v4 = {2.0, 1.4};
	v4.print();

	Game game("lol");
	game.run();


	return 0;
}
