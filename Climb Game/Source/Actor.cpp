#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game)
	:active(true), game(game)
{
	transform.location = sf::Vector2f(0., 0.);
	transform.scale = sf::Vector2f(1., 1.);
	transform.rotation = 0.;

	game->AddActor(this);
}

Actor::~Actor()
{
	game->RemoveActor(this);

	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (active)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto component : components)
	{
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	int order = component->GetUpdateOrder();
	auto iter = components.begin();
	for (; iter != components.end(); iter++)
	{
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
	{
		components.erase(iter);
	}
}
