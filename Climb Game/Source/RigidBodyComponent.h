#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class RigidBodyComponent : Component
{
public:
	RigidBodyComponent(class Actor* owner, int order = 100);

	sf::Vector2f GetVelocity() { return velocity; }
	void SetVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	void SetVelocity(float x, float y) { velocity = sf::Vector2f(x, y); }
	sf::Vector2f GetAcceleration() { return acceleration; }
	void SetAcceleration(sf::Vector2f acceleration) { this->acceleration = acceleration; }
	sf::Vector2f GetPosition() { return position; }
	void SetPosition(sf::Vector2f pos) { position = pos; }

	float GetMass() { return mass; }
	void SetMass(float mass) { this->mass = mass; }

	void Update(float deltaTime);

	void ClearAccelerationAndVelocity();
	void ClearYVelocity();
	void AddForce(sf::Vector2f force);

	void ApplyImpulse(float normalVel, sf::Vector2f normal);
	
private:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f position;

	sf::Vector2f accumulatedForce;
	float mass;
};
