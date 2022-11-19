#pragma once
#include "Actor.h"

class RectangleComponent;
class CollisionComponent;

// Climbable objects reprsent anything the player can climb on.
// They have a rectangle Component and collision component
class Climbable : public Actor {

public:
	Climbable(Game* game);
	Climbable(Game* game, sf::Vector2f min, sf::Vector2f max);
	~Climbable();

	float getHighestPoint() { return highestPoint; };

private:
	RectangleComponent* rectangle;
	CollisionComponent* collider;

	float highestPoint;

};
