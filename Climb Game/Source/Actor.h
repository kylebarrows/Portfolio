#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Game;
class Component;

struct Transform
{
	// Where the actor is in the scene
	sf::Vector2f location;

	// How large the actor is
	sf::Vector2f scale;

	// Rotation in degrees
	float rotation;
};

class Actor
{
public:
	Actor(Game* game);
	//Actor(const std::string tag, const int id);
	virtual ~Actor();

	// Called once a frame to update the actor
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);

	virtual void UpdateActor(float deltaTime);

	// Getters and setters
	bool GetActive() { return active; }
	void SetActive(bool active) { this->active = active; }
	sf::Vector2f GetLocation() { return transform.location; }
	void SetLocation(sf::Vector2f newLoc) { transform.location = newLoc; }
	sf::Vector2f GetScale() { return transform.scale; }
	void SetScale (sf::Vector2f newScale) { transform.scale = newScale; }
	float GetRotation() { return transform.rotation; }
	void SetRotation(float rotation) { transform.rotation = rotation; }

	Game* GetGame() const { return game; }

	// Adds a component to the actor
	void AddComponent(Component* component);

	// Removes component from the actor
	void RemoveComponent(Component* component);
protected:
	bool active;
	Transform transform;

	std::vector<Component*> components;
	Game* game;
};
