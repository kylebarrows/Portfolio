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
	void Reset();

	// Get player inputs
	void ProcessInput(sf::Event& event);

	// Returns the players height, used for score keeping and generation
	float GetPlayerHeight() { return transform.location.y; }

	bool IsAlive() { return isAlive; }

	void MoveCamera(sf::View& view);

private:
	// Components
	RigidBodyComponent* rb;
	RectangleComponent* rect;
	CollisionComponent* collider;

	// Gameplay parameters
	const int JUMP_HEIGHT = 15;
	const int NUM_JUMPS = 2;
	const float MAX_WALL_HANG_TIME = 5.0;
	const float MAX_JUMP_HOLD_TIME = 0.2;
	const float MAX_FALL_TIME = 2.0;

	const sf::Vector2f hangGravityForce = sf::Vector2f(0.0, -5.0);
	const sf::Vector2f regularGravityForce = sf::Vector2f(0.0, -50.0);
	
	float wallHangTimer;
	float jumpHoldTimer;
	float fallTimer;

	bool bAttachedToWall;
	bool bCanJump;
	bool bCanDoubleJump;
	bool bFacingRight;
	bool bJumping;
	bool bDoubleJumping;

	bool isAlive;

	// Camera Movement parameters;
	const float MAX_X_OFFSET = 10;

	// Gameplay functions
	void Move(sf::Vector2f offset);
	void Jump(sf::Vector2f jumpDir);
	void DoubleJump(sf::Vector2f jumpDir);
	void CheckCollisions();

	void OnWallAttach();
	void OnWallRelease();
};