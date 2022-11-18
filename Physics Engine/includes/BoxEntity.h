#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "RigidBody.h"
#include "Entity.h";
#include "World.h"

class BoxEntity : public Entity
{
public:
	BoxEntity();
	BoxEntity(nbp::Vector2 pos, nbp::Vector2 extents, nbp::World* world);

	void setColor(sf::Color color);

	void draw(sf::RenderWindow& window, sf::Transform transform) override;
	void synchronize() override;

	nbp::RigidBody* m_rb;
	sf::RectangleShape m_shape;

};