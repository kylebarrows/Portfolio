#pragma once
#include "Component.h"
#include "Collision.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner, int order = 100);
	CollisionComponent(class Actor* owner, sf::Vector2f minimum, sf::Vector2f extents);
	~CollisionComponent();

	AABB getAABB();

	void setMax(sf::Vector2f maximum) { m_AABB.maximum = maximum; }
	void setMin(sf::Vector2f minimum) { m_AABB.minimum = minimum; }
	sf::Vector2f getMax() { return m_AABB.maximum; }
	sf::Vector2f getMin() { return m_AABB.minimum; }

private:
	AABB m_AABB;
};