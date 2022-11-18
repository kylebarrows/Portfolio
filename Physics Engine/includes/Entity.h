#pragma once
#include <SFML/Graphics.hpp>

// Entities are objects that can be rendered to the screen
class Entity
{
public:
	Entity();

	virtual void draw(sf::RenderWindow& window, sf::Transform transform);
	virtual void synchronize();
};
