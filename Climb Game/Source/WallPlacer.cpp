#include "WallPlacer.h"
#include "Climbable.h"
#include "Game.h"
#include "time.h"

WallPlacer::WallPlacer()
{
	highestWallSoFar = 0.0;
	lastWallX = 0.0;
}

void WallPlacer::GenerateWalls(Game* game, int targetHeight)
{
	// We need to generate walls until we reach the target height
	// since walls can have variable heights and starting points
	// it can take any number of walls to reach the end point although you'd
	// have to be really unlucky
	do{
		GenerateWall(game);
	} while (highestWallSoFar < targetHeight);
}

void WallPlacer::GenerateStart(Game* game)
{
	srand(time(NULL));
	sf::Vector2f groundPos = sf::Vector2f(-25.0, -10.0);
	sf::Vector2f groundDimensions = sf::Vector2f(50.0f, 10.0f);
	climbables.push_back(new Climbable(game, groundPos, groundDimensions));

	sf::Vector2f wallPos = sf::Vector2f(7.0, 0.0);
	sf::Vector2f wallDimensions = sf::Vector2f(1.0, 20.0f);
	climbables.push_back(new Climbable(game, wallPos, wallDimensions));
	highestWallSoFar = (wallPos.y, wallDimensions.y);
	lastWallX = wallPos.x;

	wallPos = sf::Vector2f(-7.0, 5.0);
	wallDimensions = sf::Vector2f(1.0, 20.0f);
	climbables.push_back(new Climbable(game, wallPos, wallDimensions));

	lastHeight = highestWallSoFar;
	highestWallSoFar = wallPos.y + wallDimensions.y;
	lastWallX = wallPos.x;
	lastSign = -1;
}



void WallPlacer::RemoveWallsBelowHeight(Game* game, int height)
{
	// Since the max height should be in ascending order, we can remove the first n elements
	// below the target height range
	auto iter = climbables.begin();
	for (; iter != climbables.end(); iter++)
	{
		if ((*iter)->getHighestPoint() > height)
		{
			break;
		}

	}

	for (auto j = climbables.begin(); j < iter; j++)
	{
		delete *j;
	}
	climbables.erase(climbables.begin(), iter);
}

float WallPlacer::selectWallHeight()
{
	return WALL_HEIGHTS[rand() % 8];
}

float WallPlacer::selectWallOffset()
{
	return WALL_X_OFFSETS[rand() % 3];
}

sf::Vector2f WallPlacer::generateWallPos()
{
	sf::Vector2f wallPos;
	int sign = rand() % 2 == 0 ? -1 : 1;

	float x, y;
	float xOffset = selectWallOffset();
	if (sign == lastSign)
	{
		x = lastWallX + (sign * WALL_H_S_SAME);
		y = highestWallSoFar + MAX_WALL_SEPARATION_HEIGHT;
	}
	else
	{
		x = lastWallX + (sign * WALL_HORIZONTAL_SEPARATION);
		y = lastHeight + MAX_WALL_SEPARATION_HEIGHT;
	}
	
	wallPos.x = x;
	wallPos.y = y;

	lastSign = sign;

	return wallPos;
}

sf::Vector2f WallPlacer::generateWallDimensions()
{
	sf::Vector2f wallDimensions;

	float x = WALL_WIDTH;
	float y = selectWallHeight();

	wallDimensions.x = x;
	wallDimensions.y = y;

	return wallDimensions;
}

void WallPlacer::GenerateWall(Game* game)
{
	sf::Vector2f wallPos = generateWallPos();
	sf::Vector2f wallDimensions = generateWallDimensions();

	lastHeight = highestWallSoFar;
	highestWallSoFar = wallPos.y + wallDimensions.y;

	float wallXDist = lastWallX - wallPos.x;
	if (std::abs(wallXDist) > MAX_WALL_SEPARATION_HEIGHT)
	{
		// Wall needs to move to left
		if (lastWallX < wallPos.x)
		{
			wallPos.x -= std::abs(wallXDist) - MAX_WALL_SEPARATION_HEIGHT;
		}
		else
		{
			wallPos.x += std::abs(wallXDist) - MAX_WALL_SEPARATION_HEIGHT;
		}
	}

	lastWallX = wallPos.x;
	if (highestWallSoFar < lastHeight)
	{
		highestWallSoFar = lastHeight;
	}

	climbables.push_back(new Climbable(game, wallPos, wallDimensions));
}

