#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Actor;

class BoxCollisionComponent : Component
{
public:
	BoxCollisionComponent(Actor* owner, sf::Vector2f center, float* r);

private:
	class AABB box;
};
