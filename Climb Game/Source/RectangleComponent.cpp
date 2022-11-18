#include "RectangleComponent.h"
#include "Actor.h"

RectangleComponent::RectangleComponent(Actor* owner, int order /*= 100*/)
	:RenderComponent(owner)
{
	m_Shape = sf::RectangleShape();
}

void RectangleComponent::Update(float deltaTime)
{
	setPosition(owner->GetLocation());
}

void RectangleComponent::setDimensions(sf::Vector2f dimensions)
{
	m_Shape.setSize(sf::Vector2f(dimensions.x * 50, dimensions.y * 50));
}

void RectangleComponent::setPosition(sf::Vector2f position)
{
	m_Shape.setPosition(position.x, position.y);
}

void RectangleComponent::setColor(sf::Color color)
{
	m_Shape.setFillColor(color);
}

// Convert the owning actors world coordinates to screen coordinates and set the position
void RectangleComponent::Synchronize()
{
	sf::Vector2f screenPos = owner->GetLocation() * 50.0f;
	setPosition(screenPos);
}

void RectangleComponent::Render(sf::RenderWindow* window, sf::Transform transform)
{
	Synchronize();
	window->draw(m_Shape, transform);
}


