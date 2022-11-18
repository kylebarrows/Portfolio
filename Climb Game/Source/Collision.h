#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

struct HitResult
{
	sf::Vector2f delta;
	sf::Vector2f normal;
	sf::Vector2f pos;
};

struct AABB
{
	// minimum and maximum points of the box
	sf::Vector2f maximum;
	sf::Vector2f minimum;

	AABB();
	AABB(sf::Vector2f min, sf::Vector2f max);
};

struct Sphere
{
	Sphere(const sf::Vector2f center, float radius);

	sf::Vector2f center;
	float radius;
};

bool TestAABB(const AABB& a, const AABB& b, HitResult& hitResult);
