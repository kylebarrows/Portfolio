#include "ClimbMath.h"

namespace CMath
{

	bool NearlyZero(float f)
	{
		return std::abs(f) < SMALL_NUMBER;
	}

	float GetLength(sf::Vector2f v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	float Clamp(float min, float max, float f)
	{
		if (f > max)
		{
			return max;
		}
		else if (f < min)
		{
			return min;
		}

		return f;
	}

	float Dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}

	sf::Vector2f Normalize(sf::Vector2f v)
	{
		float length = GetLength(v);
		if (length == 0)
		{
			return sf::Vector2f(0, 0);
		}
		return v / length;
	}

}