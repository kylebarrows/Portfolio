#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

// Objects that can be rendered to the screen
class RenderComponent : public Component
{
public:
	RenderComponent(class Actor* owner, int order = 100);
	~RenderComponent();

	virtual void Render(sf::RenderWindow* window, sf::Transform transform);
	virtual void Synchronize();

protected:

};