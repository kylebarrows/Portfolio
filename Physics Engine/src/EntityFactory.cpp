#include "../includes/EntityFactory.h"

EntityFactory::EntityFactory()
{

}

BoxEntity* EntityFactory::makeBoxEntity(nbp::Vector2 pos, nbp::Vector2 extents, nbp::World* world)
{
	BoxEntity* box = new BoxEntity(pos, extents, world);
	return box;
}

CircleEntity* EntityFactory::makeCircleEntity(nbp::Vector2 pos, float radius, nbp::World* world)
{
	CircleEntity* circle = new CircleEntity(pos, radius, world);
	return circle;
}
