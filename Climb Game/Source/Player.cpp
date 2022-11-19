#include "Player.h"

Player::Player(Game* game)
	:Actor(game)
{
	reset();
}

void Player::UpdateActor(float deltaTime)
{
	
}

void Player::ProcessInput()
{

}

void Player::Jump()
{

}

void Player::DoubleJump()
{

}

void Player::reset()
{
	jumpStrength = 10;
	maxWallHangTime = 5.0;
	wallHangTimer = maxWallHangTime;

	bAttachedToWall = false;
	bCanJump = true;
	bCanDoubleJump = false;
}

