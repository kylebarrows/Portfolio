#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "RigidBody.h"
#include "Entity.h"
#include "World.h"

class CircleEntity : public Entity
{
public:
	CircleEntity();
	CircleEntity(nbp::Vector2 pos, float radius, nbp::World* world);

	void draw(sf::RenderWindow& window, sf::Transform transform) override;
	void synchronize() override;

	nbp::RigidBody* m_rb;
	sf::CircleShape m_shape;
};