#pragma once
#include <SFML/Graphics.hpp>

#define SMALL_NUMBER (0.0001);

namespace CMath
{
	bool NearlyZero(float f);

	float GetLength(sf::Vector2f v);

	float Clamp(float min, float max, float f);

	float Dot(sf::Vector2f a, sf::Vector2f b);

	sf::Vector2f Normalize(sf::Vector2f v);
}