#include "RigidBodyComponent.h"
#include "Actor.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner, int order)
	:Component(owner)
{
	velocity = sf::Vector2f(200, 0);
	acceleration = sf::Vector2f(0, 0.0);
	position = owner->GetLocation();
}

// Update the position of the body, and calculate the velocity for next frame
// using Newton Euler integration method.
void RigidBodyComponent::Update(float deltaTime)
{
	position += velocity * deltaTime;
	owner->SetLocation(position);
	
	velocity += acceleration * deltaTime;

	acceleration += accumulatedForce * (1/mass) * deltaTime;

	accumulatedForce = sf::Vector2f(0, 0);
}

void RigidBodyComponent::ClearAccelerationAndVelocity()
{
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
}

void RigidBodyComponent::ClearYVelocity()
{
	velocity.y = 0.0;
}

// Add force to the rigid body to be handled next frame
void RigidBodyComponent::AddForce(sf::Vector2f force)
{
	accumulatedForce += force * mass;
}

// Apply an impulse to the object, since for this game, the player can
// only interact with static objects for the time being, only
// worry about the mass of the this object.
void RigidBodyComponent::ApplyImpulse(float normalVel, sf::Vector2f normal)
{
	float j = -1 * normalVel * mass;

 	sf::Vector2f impulse = -j * normal;
	velocity += impulse / mass;
}

