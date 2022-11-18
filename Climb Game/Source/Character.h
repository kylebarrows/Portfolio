#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Game;
class RigidBodyComponent;
class RectangleComponent;
class CollisionComponent;

class Character : public Actor
{
public:
	Character(Game* game);

	// Update the actor each frame
	void UpdateActor(float deltaTime) override;

	// Get player inputs
	void ProcessInput(sf::Event& event);

private:
	// Components
	RigidBodyComponent* rb;
	RectangleComponent* rect;
	CollisionComponent* collider;

	// Gameplay parameters
	const int JUMP_HEIGHT = 10;
	const int NUM_JUMPS = 2;
	const float MAX_WALL_HANG_TIME = 5.0;

	const sf::Vector2f hangGravityForce = sf::Vector2f(0.0, -5.0);
	const sf::Vector2f regularGravityForce = sf::Vector2f(0.0, -18.0);
	
	float wallHangTimer;
	bool bWasAttachedToWall;
	bool bAttachedToWall;
	bool bCanJump;
	bool bCanDoubleJump;
	bool bFacingRight;
	float vertical;
	float horizontal;

	// Gameplay functions
	void Move(sf::Vector2f offset);
	void Jump(sf::Vector2f jumpDir);
	void DoubleJump(sf::Vector2f jumpDir);
	void CheckCollisions();

	void OnWallAttach();
	void OnWallRelease();


};