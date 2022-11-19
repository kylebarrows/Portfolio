#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Climbable;
class Game;

class WallPlacer
{
public:
	WallPlacer();
	
	void GenerateWalls(Game* game, int targetHeight);
	void GenerateStart(Game* game);

	void RemoveWallsBelowHeight(Game* game, int height);

private:
	const float WALL_WIDTH = 1.0f;
	const float MIN_WALL_HEIGHT = 4.0f;
	const float MAX_WALL_HEIGHT = 20.0f;
	const float WALL_HORIZONTAL_SEPARATION = 12.0f;
	const float WALL_H_S_SAME = 7.0f;
	const float MIN_WALL_SEPARATION_HEIGHT = 2.0f;
	const float MAX_WALL_SEPARATION_HEIGHT = 8.0f;

	const float WALL_HEIGHTS[8] = { 5.0, 7.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0 };
	const float WALL_X_OFFSETS[3] = { -7.0, 0.0, 14.0 };

	float highestWallSoFar;
	float lastHeight;

	// Keep track of whether or not a wall was placed to the left or right
	int lastSign;

	// Last x position a wall was placed in
	float lastWallX;
	float lastLeftWallHeight;
	float lastRightWallHeight;

	std::vector<Climbable*> climbables;

	float selectWallHeight();
	float selectWallOffset();
	sf::Vector2f generateWallPos();
	sf::Vector2f generateWallDimensions();
	void GenerateWall(Game* game);


};