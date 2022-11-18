#include "BoxCollisionComponent.h"
#include "Component.h"

BoxCollisionComponent::BoxCollisionComponent(Actor* owner, sf::Vector2f center, float* r)
	:Component(owner), box(center, r)
{

}

