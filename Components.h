#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "Vec2.h"
#include <SFML/Graphics.hpp>

#ifndef ENUM_CTAG
#define ENUM_CTAG
enum CTag{
	default_tag,
	bullet,
	enemy,
	player,
	enemy_small,
	text
};
#endif

class CTransform{
	public:
		Vec2 pos = {0.0, 0.0};
		Vec2 velocity = {0.0, 0.0};
		float angle = 0.0;

		CTransform(Vec2 pos, Vec2 vel, float angle)
			: pos (pos), velocity (vel), angle (angle) {}
};

class CShape{
public:
	sf::CircleShape polygon;

	CShape(float radius, int points, const sf::Color & fill, const sf::Color& outline, float thickness)
		: polygon(radius, points) {

			polygon.setFillColor(fill);
			polygon.setOutlineColor(outline);
			polygon.setOutlineThickness(thickness);
			polygon.setOrigin(radius, radius);
		}
};

class CCollision{
public:
	float radius;

	CCollision(float radius)
		: radius (radius) {}
};

class CScore{
public:
	float score;
	CScore(float score)
		: score (score) {}
};

class CLifeSpan{
public:
	float initial;
	float remaining;

	CLifeSpan(float span)
		: remaining (span), initial (span) {}
};

class CInput{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;
	bool special = false;
	Vec2 aim = {0.0f, 0.0f};

	CInput() {}
};
#endif
