#include "CollisionComponent.h"
#include "Actor.h"
#include "Game.h"

CollisionComponent::CollisionComponent(class Actor* owner, int order /*= 100*/)
	:Component(owner)
{
	owner->GetGame()->AddCollider(this);
}

CollisionComponent::CollisionComponent(class Actor* owner, sf::Vector2f minimum, sf::Vector2f maximum)
	:Component(owner)
{
	setMin(minimum);
	setMax(maximum);

	owner->GetGame()->AddCollider(this);
}

CollisionComponent::~CollisionComponent()
{
	owner->GetGame()->RemoveCollider(this);
}

AABB CollisionComponent::getAABB()
{
	sf::Vector2f min = owner->GetLocation() + m_AABB.minimum;
	sf::Vector2f max = owner->GetLocation() + m_AABB.maximum;
	return AABB(min, max);
}
