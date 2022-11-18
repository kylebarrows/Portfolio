#include "Climbable.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "RectangleComponent.h"

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
	sf::Vector2f min = sf::Vector2f(pos.x - dimensions.x, pos.y - dimensions.y);
	sf::Vector2f max = sf::Vector2f(pos.x + dimensions.x, pos.y + dimensions.y);
	collider = new CollisionComponent(this, -dimensions, dimensions);
	rectangle = new RectangleComponent(this);

	rectangle->setPosition(pos);
	rectangle->setDimensions(dimensions);
	rectangle->setColor(sf::Color::Green);

}
