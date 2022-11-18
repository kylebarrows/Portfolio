#include "ActorManager.h"
#include "Actor.h"
#include <algorithm>

ActorManager::ActorManager()
{

}

ActorManager::~ActorManager()
{
	while (!Actors.empty())
	{
		delete Actors.back();
	}
}

// Called each frame by the game
// adds any pending actors to the game for use and removes any inactive ones
void ActorManager::Update(float deltaTime)
{
	// First update all actors
	for (auto actor : Actors)
	{
		actor->Update(deltaTime);
	}

	// Then add any actors that have been created
	for (auto actor : PendingActors)
	{
		Actors.push_back(actor);
	}
	PendingActors.clear();

	// Finally remove all old actors
	for (auto actor : Actors)
	{
		//std::remove_if(Actors.begin(), Actors.end(), !actor->GetActive());
	}
}

void ActorManager::AddActor(Actor* actor)
{
	PendingActors.push_back(actor);
}

std::vector<Actor*>& ActorManager::GetActors()
{
	return Actors;
}


