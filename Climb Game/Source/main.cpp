#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;

	bool success = game.Initialize();
	if (success)
	{
		game.Run();
	}

	//sf::CircleShape shape(100.f);;;
	//shape.setFillColor(sf::Color::Green);

	return 0;
}