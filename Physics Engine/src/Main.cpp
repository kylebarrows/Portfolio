#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../includes/collisions/CollisionSolver.h"
#include "../includes/collisions/Box2D.h"
#include "../includes/World.h"
#include "../includes/collisions/Broadphase.h"
#include "../includes/EntityFactory.h"
#include "../includes/Entity.h"


int main()
{
	const int WIDTH = 1000;
	const int HEIGHT = 800;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics...");

	// Create physics World
	nbp::World* world = new nbp::World();

	std::vector<Entity*> entities;

	// Setup camera
	sf::View view;
	view.setSize(WIDTH, HEIGHT);

	sf::Clock clock;
	const sf::Transform transform = [HEIGHT] {
		sf::Transformable transformation;
		transformation.setOrigin(0, HEIGHT);
		transformation.setScale(1.f, -1.f);
		return transformation.getTransform();
	}();

	EntityFactory factory;

	// Create ground
	nbp::Vector2 groundPos = nbp::Vector2(8, 2);
	nbp::Vector2 groundExtents = nbp::Vector2(5, 0.5);
	BoxEntity* ground = factory.makeBoxEntity(groundPos, groundExtents, world);
	entities.push_back(ground);
	ground->m_rb->setType(nbp_static);

	groundPos = nbp::Vector2(3, 8);
	groundExtents = nbp::Vector2(2, 0.5);
	BoxEntity* ground2 = factory.makeBoxEntity(groundPos, groundExtents, world);
	entities.push_back(ground2);
	ground2->m_rb->setAngle(-20);
	ground2->m_rb->setType(nbp_static);

	bool lock_click = false;
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
		nbp::Vector2 mousePos = nbp::Vector2(worldPos.x * 0.02f, (HEIGHT - pixelPos.y) * 0.02f);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
			{
				CircleEntity* c = factory.makeCircleEntity(mousePos, 1, world);
				entities.push_back(c);
				c->m_rb->applyImpulse(nbp::Vector2(0.0, -1.0));

				lock_click = true;
			}

			if (event.mouseButton.button == sf::Mouse::Right && lock_click != true)
			{
				nbp::Vector2 boxDim = nbp::Vector2(0.5, 0.5);
				BoxEntity* b = factory.makeBoxEntity(mousePos, boxDim, world);
				entities.push_back(b);
				b->m_rb->applyImpulse(nbp::Vector2(0.0, -1.0));

				lock_click = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				lock_click = false;
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				lock_click = false;
			}
		}

		world->step(deltaTime);

		window.clear();
		window.setView(view);

		for (Entity* ent : entities)
		{
			ent->synchronize();
			ent->draw(window, transform);
		}

		window.display();

	}

	return 0;
}
