#pragma once
#include <SFML/Graphics.hpp>

class ActorManager;
class Actor;
class RigidBodyComponent;
class Character;
class RenderComponent;
class CollisionComponent;
class Climbable;

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void Run();
	void EndGame();

	const bool IsRunning() const;

	void AddActor(Actor* actor);
	void AddRenderable(RenderComponent* renderable);
	void AddCollider(CollisionComponent* collider);
	void RemoveRenderable(RenderComponent* renderable);
	void RemoveCollider(CollisionComponent* colliders);

	std::vector<CollisionComponent*> getColliders() { return colliders; }

	void LoadGame();

private:
	sf::Clock clock;
	const int GAME_WIDTH = 800;
	const int GAME_HEIGHT = 600; 
	
	sf::RectangleShape* test;

	sf::RenderWindow* window;
	sf::View view;

	ActorManager* actorManager;
	std::vector<RenderComponent*> renderables;
	std::vector<CollisionComponent*> colliders;

	void GetInputs();
	void Render();

	Climbable* ground;
	Climbable* wall;
	Climbable* wall2;

	Character* character;
	RigidBodyComponent* rb;
};