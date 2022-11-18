#pragma once
#include "Vector2.h"
#include "CircleEntity.h"
#include "BoxEntity.h"
#include "World.h"

// Handles creating different entities
class EntityFactory
{
public:
	EntityFactory();

	BoxEntity* makeBoxEntity(nbp::Vector2 pos, nbp::Vector2 extents, nbp::World* world);
	CircleEntity* makeCircleEntity(nbp::Vector2 pos, float radius, nbp::World* world);
};