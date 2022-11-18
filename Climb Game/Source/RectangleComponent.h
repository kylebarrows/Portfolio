#pragma once
#include "RenderComponent.h"

class RectangleComponent : public RenderComponent
{
public:
	RectangleComponent(Actor* owner, int order = 100);

	void Update(float deltaTime) override;

	void setDimensions(sf::Vector2f dimensions);
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);

	void Synchronize() override;
	void Render(sf::RenderWindow* window, sf::Transform transform) override;

private:
	sf::RectangleShape m_Shape;
};