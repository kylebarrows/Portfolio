#include "../includes/BoxEntity.h"
#include "../includes/collisions/Box2D.h"

BoxEntity::BoxEntity()
{

}

BoxEntity::BoxEntity(nbp::Vector2 pos, nbp::Vector2 extents, nbp::World* world)
{
	sf::Vector2f dimensions = sf::Vector2f(extents.x * 100, extents.y * 100);
	sf::Vector2f position = sf::Vector2f(pos.x * 50, pos.y * 50);
	m_shape = sf::RectangleShape(dimensions);
	m_shape.setOrigin(dimensions.x * 0.5f, dimensions.y * 0.5f);
	m_shape.setPosition(position);
	m_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

	m_rb = new nbp::RigidBody();
	m_rb->setPos(pos);

	nbp::Box2D* box = new nbp::Box2D(pos, extents, 0.0);
	m_rb->setCollider(box);
	world->registerBody(m_rb);
}

void BoxEntity::setColor(sf::Color color)
{
	m_shape.setFillColor(color);
}

void BoxEntity::draw(sf::RenderWindow& window, sf::Transform transform)
{
	window.draw(m_shape, transform);
}

void BoxEntity::synchronize()
{
	nbp::Vector2 newPos = m_rb->getPos();
	m_shape.setPosition(newPos.x * 50, newPos.y * 50);
	m_shape.setRotation(m_rb->getRotation());
}
