#include "Climbable.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "RectangleComponent.h"
#include "Game.h"

Climbable::Climbable(Game* game)
	: Actor(game)
{
	rectangle = nullptr;
	collider = nullptr;
}

Climbable::Climbable(Game* game, sf::Vector2f pos, sf::Vector2f dimensions)
	:Actor(game)
{
	SetLocation(pos);
	collider = new CollisionComponent(this, pos, dimensions);
	rectangle = new RectangleComponent(this);

	rectangle->setPosition(collider->getAABB().minimum);
	rectangle->setDimensions(dimensions);
	rectangle->setColor(sf::Color(99, 70, 35));

	highestPoint = pos.y + dimensions.y;
}

Climbable::~Climbable()
{
}
