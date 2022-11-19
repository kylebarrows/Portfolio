#pragma once
#include <vector>
#include <map>
#include <iostream>

class Actor;

// Class to handle storage and updating all actors in the game
class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	void Update(float deltaTime);
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	std::vector<Actor*>& GetActors();

private:
	std::vector<Actor*> Actors;
	std::vector<Actor*> PendingActors;
	size_t totalEntitiesCreated = 0;

};