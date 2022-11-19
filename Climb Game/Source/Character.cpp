#include "Character.h"
#include "Game.h"
#include "ClimbMath.h"
#include "RigidBodyComponent.h"
#include "RectangleComponent.h"
#include "CollisionComponent.h"
#include "Collision.h"

Character::Character(Game* game)
	:Actor(game)
{
	rb = new RigidBodyComponent(this);
	if (rb)
	{
		rb->SetMass(10.0f);
		rb->SetVelocity(0.0f, 0.0f);
		rb->SetAcceleration(sf::Vector2f(0.0f, -9.8f));
	}

	rect = new RectangleComponent(this);
	if (rect)
	{
		rect->setDimensions(sf::Vector2f(2, 2));
		rect->setPosition(sf::Vector2f(0, 1));
		rect->setColor(sf::Color::Red);
	}

	sf::Vector2f colliderBound = sf::Vector2f(2.2f, 2.2f);
	collider = new CollisionComponent(this, transform.location, colliderBound);
}

void Character::UpdateActor(float deltaTime)
{
	CheckCollisions();

	// Attached to wall behavior
	if (bAttachedToWall)
	{
		fallTimer = MAX_FALL_TIME;

		if (wallHangTimer < 0)
		{
			rb->AddForce(hangGravityForce);
		}
	}
	else
	{
		rb->AddForce(regularGravityForce);

		// Player is falling
		if (!bJumping && !bDoubleJumping)
		{
			fallTimer -= deltaTime;
		}
	}


	if (wallHangTimer > 0)
	{
		wallHangTimer -= deltaTime;
	}

	if (jumpHoldTimer > 0)
	{
		jumpHoldTimer -= deltaTime;
	}
	else
	{
		bJumping = false;
		bDoubleJumping = false;
	}

	if (fallTimer <= 0)
	{
		isAlive = false;
	}
}

// Reset some player data;
void Character::Reset()
{
	fallTimer = MAX_FALL_TIME * 5;

	isAlive = true;
	bAttachedToWall = false;
	bCanJump = false;
	bCanDoubleJump = false;
	bFacingRight = true;
	bJumping = false;
	bDoubleJumping = false;

	rb->ClearAccelerationAndVelocity();
}

void Character::ProcessInput(sf::Event& event)
{
	sf::Vector2f vel = rb->GetVelocity();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (bAttachedToWall && bCanJump)
		{
			jumpHoldTimer = MAX_JUMP_HOLD_TIME;
			Jump(sf::Vector2f(1, 1));
			bAttachedToWall = false;
			bCanJump = false;
			bCanDoubleJump = true;
		}
		else if (bCanJump && bCanDoubleJump)
		{
			jumpHoldTimer = MAX_JUMP_HOLD_TIME;
			DoubleJump(sf::Vector2f(1, 1));
			bCanJump = false;
			bCanDoubleJump = false;
		}

		// Check for hold jumping
		if (jumpHoldTimer > 0.0)
		{
			if (bJumping)
			{
				Jump(sf::Vector2f(1, 1));
			}
			else
			{
				DoubleJump(sf::Vector2f(1, 1));
			}
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			bCanJump = true;
		}
	}
}

// Handles moving the camera along the x axis unless moving passed the extents of the box.
void Character::MoveCamera(sf::View& view)
{
	sf::Vector2f cameraPos = view.getCenter();
	cameraPos.x /= 50;
	cameraPos.y /= 50;
	sf::Vector2f newCameraPos = cameraPos;
	
	// Only move the camera along if traveling upward
	if (rb->GetVelocity().y >= 0)
	{
		newCameraPos.y = -transform.location.y;
	}


	if (transform.location.x > cameraPos.x + MAX_X_OFFSET)
	{
		int i = 0;
	}

	float xDistanceFromCenter = transform.location.x - (cameraPos.x);
	if (std::abs(xDistanceFromCenter) > MAX_X_OFFSET)
	{
		float xAmountToMove = std::abs(xDistanceFromCenter) - MAX_X_OFFSET;
		if (transform.location.x < cameraPos.x)
		{
			xAmountToMove *= -1;
		}
		else if (transform.location.x > cameraPos.x)
		{
			xAmountToMove;
		}
		
		xAmountToMove = CMath::Clamp(-0.05, 0.05, xAmountToMove);
		newCameraPos.x = cameraPos.x + xAmountToMove;
	}

	view.setCenter(newCameraPos.x * 50, newCameraPos.y * 50);
}

void Character::Move(sf::Vector2f offset)
{

}

void Character::Jump(sf::Vector2f jumpDir)
{
	bJumping = true;
	if (bFacingRight)
	{
		rb->SetVelocity({ jumpDir.x * JUMP_HEIGHT, jumpDir.y * JUMP_HEIGHT });
	}
	else
	{
		rb->SetVelocity({ -jumpDir.x * JUMP_HEIGHT, jumpDir.y * JUMP_HEIGHT });
	}

	OnWallRelease();
}

void Character::DoubleJump(sf::Vector2f jumpDir)
{
	bDoubleJumping = true;
	bJumping = false;
	rb->ClearAccelerationAndVelocity();
	if (bFacingRight)
	{
		rb->SetVelocity({ -jumpDir.x * JUMP_HEIGHT, jumpDir.y * JUMP_HEIGHT });
	}
	else
	{
		rb->SetVelocity({ jumpDir.x * JUMP_HEIGHT, jumpDir.y * JUMP_HEIGHT });
	}

	OnWallRelease();
}

void Character::CheckCollisions()
{
	if (!collider)
	{
		return;
	}

	std::vector<CollisionComponent*> rects = game->getColliders();
	for (int i = 0; i < rects.size(); i++)
	{
		CollisionComponent* rect = rects[i];
		if (rects[i] == collider)
		{
			continue;
		}

		AABB a = collider->getAABB();
		AABB b = rect->getAABB();
		HitResult hitResult;

		// Small optimization, not even worth checking objects above the player
		if (a.maximum.y < b.minimum.y)
		{
			break;
		}

		if(TestAABB(a, b, hitResult))
		{
			bFacingRight = true;
			if (!bAttachedToWall)
			{
 				if(hitResult.normal.y < 0.1)
				{
					OnWallAttach();
				}
			}

			if (!CMath::NearlyZero(hitResult.normal.y))
			{
				if (hitResult.normal.y > 0)
				{
					// Let the player grab on if they hit the bottom
					transform.location.y += 0.4;
					float xOffset = b.minimum.x - a.minimum.x;
					float aXLength = a.maximum.x - a.minimum.x;
					float bXLength = b.maximum.x - b.minimum.x;

					// When character is to the left of the object
					if (xOffset >= 0)
					{
						transform.location.x -= (a.maximum.x - b.minimum.x) - 0.5;
					}
					else
					{
						transform.location.x += b.maximum.x - a.minimum.x + 0.5;
					}

					// Set positions and velocity, let the collision check handle the rest
					rb->SetPosition(transform.location);
					sf::Vector2f vel = rb->GetVelocity();
					vel.x = -vel.x;
					rb->SetVelocity(vel);
					hitResult.normal.y = 0;
				}
			}

			// Check if character hit a wall
			if (!CMath::NearlyZero(hitResult.normal.x))
			{
				
				// Check if the character should be facing left or right
				if (hitResult.normal.x >= 0)
				{
					bFacingRight = false;
				}
				else
				{
					bFacingRight = true;
				}
			}

			sf::Vector2f velocity = -rb->GetVelocity();

			float normalVel = CMath::Dot(velocity, hitResult.normal);
			
			// Move the body to resolve the collision
			sf::Vector2f totalOffset = sf::Vector2f(hitResult.delta.x * hitResult.normal.x, hitResult.delta.y * hitResult.normal.y);
			transform.location += totalOffset;

			// Apply impulse 
			rb->ApplyImpulse(normalVel, hitResult.normal);
		}
	}
}

void Character::OnWallAttach()
{
	bAttachedToWall = true;
	bJumping = false;
	bDoubleJumping = false;
	rb->ClearAccelerationAndVelocity();
	wallHangTimer = MAX_WALL_HANG_TIME;
}

void Character::OnWallRelease()
{
	bAttachedToWall = false;
	wallHangTimer = 0;
}

