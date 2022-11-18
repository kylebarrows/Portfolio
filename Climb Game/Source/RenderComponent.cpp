#include "RenderComponent.h"
#include "Actor.h"
#include "Game.h"

RenderComponent::RenderComponent(class Actor* owner, int order /*= 100*/)
	:Component(owner)
{
	owner->GetGame()->AddRenderable(this);
}

RenderComponent::~RenderComponent()
{
	owner->GetGame()->RemoveRenderable(this);
}

void RenderComponent::Render(sf::RenderWindow* window, sf::Transform transform)
{

}

void RenderComponent::Synchronize()
{

}
