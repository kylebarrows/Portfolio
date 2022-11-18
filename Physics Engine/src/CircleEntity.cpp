#include "../includes/CircleEntity.h"
#include "../includes/collisions/Circle.h"

CircleEntity::CircleEntity()
{

}

CircleEntity::CircleEntity(nbp::Vector2 pos, float radius, nbp::World* world)
{
	sf::Vector2f position = sf::Vector2f(pos.x * 50, pos.y * 50);
	float r = radius * 50;
	m_shape = sf::CircleShape(r);
	m_shape.setOrigin(r, r);
	m_shape.setPosition(position);
	m_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

	m_rb = new nbp::RigidBody();
	m_rb->setPos(pos);

	nbp::Circle* circle = new nbp::Circle(radius, pos);
	m_rb->setCollider(circle);
	world->registerBody(m_rb);
}

void CircleEntity::draw(sf::RenderWindow& window, sf::Transform transform)
{
	window.draw(m_shape, transform);
}

void CircleEntity::synchronize()
{
	nbp::Vector2 newPos = m_rb->getPos();
	m_shape.setPosition(newPos.x * 50, newPos.y * 50);
	m_shape.setRotation(m_rb->getRotation());
}
