#include "Component.h"
#include "Actor.h"

Component::Component(class Actor* owner, int order /*= 100*/)
{
	this->owner = owner;
	this->updateOrder = order;

	this->owner->AddComponent(this);
}

Component::~Component()
{
	owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
