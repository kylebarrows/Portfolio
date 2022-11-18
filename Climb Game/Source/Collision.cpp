#include "Collision.h"
#include "ClimbMath.h"


AABB::AABB()
{
	minimum = maximum = sf::Vector2f(0.0, 0.0);
}


AABB::AABB(sf::Vector2f min, sf::Vector2f max)
{
	minimum = min;
	maximum = max;
}

bool TestAABB(const AABB& a, const AABB& b, HitResult& hitResult)
{
	float a_xLength = (a.maximum.x - a.minimum.x) / 2;
	float a_yLength = (a.maximum.y - a.minimum.y) / 2;
	sf::Vector2f aPos = a.maximum - sf::Vector2f(a_xLength, a_yLength);

	float b_xLength = (b.maximum.x - b.minimum.x) / 2;
	float b_yLength = (b.maximum.y - b.minimum.y) / 2;
	sf::Vector2f bPos = b.maximum - sf::Vector2f(b_xLength, b_yLength);

	float dx = bPos.x - aPos.x;
	float px = (b_xLength + a_xLength) - std::abs(dx);
	// Check for overlap on the X axis, giving it some leeway here cause of floating point inaccuracy
	if (px <= 0.1)
	{
		return false;
	}

	float dy = bPos.y - aPos.y;
	float py = (b_yLength + a_yLength) - std::abs(dy);
	// Check for overlap on the Y axis
	if (py <= 0.1)
	{
		return false;
	}

	// Calculate hit results
	if (px < py)
	{
		int s = dx < 0 ? -1 : 1;
		hitResult.delta.x = px * s;
		hitResult.normal.x = s;
		hitResult.pos.x = aPos.x + (a_xLength * s);
		hitResult.pos.y = bPos.y;
	}
	else
	{
		int s = dy < 0 ? -1 : 1;
		hitResult.delta.y = py * s;
		hitResult.normal.y = s;
		hitResult.pos.y = aPos.y + (a_yLength * s);
		hitResult.pos.x = bPos.x;
	}


	return true;
}
