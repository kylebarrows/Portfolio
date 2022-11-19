#include "CollisionComponent.h"
#include "Actor.h"
#include "Game.h"

CollisionComponent::CollisionComponent(class Actor* owner, int order /*= 100*/)
	:Component(owner)
{
	owner->GetGame()->AddCollider(this);
}

CollisionComponent::CollisionComponent(class Actor* owner, sf::Vector2f minimum, sf::Vector2f extents)
	:Component(owner)
{ 
	setMin(minimum);
	setMax(minimum + extents);

	owner->GetGame()->AddCollider(this);
}

CollisionComponent::~CollisionComponent()
{
	owner->GetGame()->RemoveCollider(this);
}

AABB CollisionComponent::getAABB()
{
	sf::Vector2f extents = m_AABB.maximum - m_AABB.minimum;
	sf::Vector2f min = owner->GetLocation();
	sf::Vector2f max = min + extents;
	return AABB(min, max);
}
