#pragma once
#include "Actor.h"

class Game;

class Player : public Actor {
	Player(Game* game);

	void UpdateActor(float deltaTime) override;
	void ProcessInput();

	void Jump();
	void DoubleJump();

private:

	// How high the player can jump
	float jumpStrength;

	// Time before player starts sliding down wall
	float maxWallHangTime;
	float wallHangTimer;

	bool bAttachedToWall;
	bool bCanJump;
	bool bCanDoubleJump;

	void reset();
};
