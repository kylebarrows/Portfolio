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
		rect->setPosition(sf::Vector2f(0, 4));
		rect->setColor(sf::Color::Red);
	}

	sf::Vector2f colliderBound = sf::Vector2f(0.1f, 0.1f);
	sf::Vector2f min = transform.location - colliderBound;
	sf::Vector2f max = transform.location + colliderBound;
	collider = new CollisionComponent(this, min, max);

	this->SetLocation(sf::Vector2f(0, 4));
}

void Character::UpdateActor(float deltaTime)
{
	CheckCollisions();

	// Attached to wall behavior
	if (bAttachedToWall)
	{
		if (wallHangTimer < 0)
		{
			rb->AddForce(hangGravityForce);
		}
	}
	else
	{
		rb->AddForce(regularGravityForce);
	}

	if (wallHangTimer > 0)
	{
		wallHangTimer -= deltaTime;
	}
}

void Character::ProcessInput(sf::Event& event)
{
	sf::Vector2f vel = rb->GetVelocity();
	vertical = 0.0;
	horizontal = 0.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (bAttachedToWall && bCanJump)
		{
			Jump(sf::Vector2f(1, 1));
			bAttachedToWall = false;
			bCanJump = false;
			bCanDoubleJump = true;
		}
		else if (bCanJump && bCanDoubleJump)
		{
			DoubleJump(sf::Vector2f(2, 1));
			bCanJump = false;
			bCanDoubleJump = false;
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

void Character::Move(sf::Vector2f offset)
{

}

void Character::Jump(sf::Vector2f jumpDir)
{
	if (bFacingRight)
	{
		rb->ApplyImpulse(JUMP_HEIGHT, jumpDir);
	}
	else
	{
		sf::Vector2f newDir = sf::Vector2f(-jumpDir.x, jumpDir.y);
		rb->ApplyImpulse(JUMP_HEIGHT, newDir);
	}

	OnWallRelease();
}

void Character::DoubleJump(sf::Vector2f jumpDir)
{
	if (bFacingRight)
	{
		sf::Vector2f newDir = sf::Vector2f(-jumpDir.x, jumpDir.y);
		rb->ApplyImpulse(JUMP_HEIGHT, newDir);
	}
	else
	{
		rb->ApplyImpulse(JUMP_HEIGHT, jumpDir);
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
		if(TestAABB(a, b, hitResult))
		{
			bFacingRight = true;
			if (!bAttachedToWall)
			{
				OnWallAttach();
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
	bCanJump = true;
	rb->ClearAccelerationAndVelocity();
	wallHangTimer = MAX_WALL_HANG_TIME;
}

void Character::OnWallRelease()
{
	bAttachedToWall = false;
	bCanDoubleJump = true;
	wallHangTimer = 0;
}

