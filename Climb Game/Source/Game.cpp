#include "Game.h"
#include "ActorManager.h"
#include "Actor.h"
#include "Character.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "Climbable.h"
#include "WallPlacer.h"

Game::Game()
{
	window = nullptr;
	test = nullptr;
	actorManager = nullptr;
}

Game::~Game()
{
	delete window;
	delete actorManager;
	
	colliders.clear();
	renderables.clear();
}

bool Game::Initialize()
{
	window = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT, 32), "Climber", sf::Style::Titlebar | sf::Style::Close);
	if (window == nullptr)
	{
		return false;
	}
	window->setVerticalSyncEnabled(true);

	actorManager = new ActorManager();
	wallPlacer = new WallPlacer();

	view.reset(sf::FloatRect(0, 0, 800, 600));
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(3.0f);
	window->setView(view);

	clock.restart();
	
	return true;
}

// Handles running the main loop
void Game::Run()
{
	float deltaTime;
	LoadGame();

	while (IsRunning())
	{
		deltaTime = clock.restart().asSeconds();
		GetInputs();
		Update(deltaTime);
		Render();
		CheckForGameOver();
	}
}

void Game::EndGame()
{
	std::cout << "Game over!" << std::endl;

	// Delete all generated walls
	wallPlacer->RemoveWallsBelowHeight(this, INT_MAX);
	delete character;

	LoadGame();
}

const bool Game::IsRunning() const
{
	return window->isOpen();
}

void Game::AddActor(Actor* actor)
{
	actorManager->AddActor(actor);
}

void Game::RemoveActor(Actor* actor)
{
	actorManager->RemoveActor(actor);
}

// Adds a renderable to the list of renderables
void Game::AddRenderable(RenderComponent* renderable)
{
	renderables.push_back(renderable);
}

// Adds a collider to the list of colliders
void Game::AddCollider(CollisionComponent* collider)
{
	colliders.push_back(collider);
}

// Remove a renderable from the list of renderables
void Game::RemoveRenderable(RenderComponent* renderable)
{
	auto iter = std::find(renderables.begin(), renderables.end(), renderable);
	renderables.erase(iter);
}

// Remove collider from the list of colliders
void Game::RemoveCollider(CollisionComponent* collider)
{
	auto iter = std::find(colliders.begin(), colliders.end(), collider);
	colliders.erase(iter);
}

void Game::LoadGame()
{
	character = new Character(this);
	character->Reset();
	character->SetLocation(sf::Vector2f(0.0, 3.0));
	
	wallPlacer->GenerateStart(this);
  	wallPlacer->GenerateWalls(this, 100);

	currentPlayerHeight = 0.0;
	wallHeightToPurge = 50.0;

	sf::Vector2f characterLocation = character->GetLocation();
	view.setCenter(characterLocation.x * 50, characterLocation.y * -50);
}

// Handles receiving inputs from the player
void Game::GetInputs()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		default:
			break;
		}
		
		character->ProcessInput(event);
	}

}

void Game::Update(float deltaTime)
{
	actorManager->Update(deltaTime);

	 // Remove walls that are way below the player and prompt generation of new ones
	currentPlayerHeight = character->GetPlayerHeight();
	if (character->GetPlayerHeight() > wallHeightToPurge)
	{
		wallPlacer->RemoveWallsBelowHeight(this, wallHeightToPurge - 10);
		wallHeightToPurge += 50;

		wallPlacer->GenerateWalls(this, wallHeightToPurge + 50);
	}

	// Update players max height
	if (currentPlayerHeight > maxPlayerHeight)
	{
		maxPlayerHeight = currentPlayerHeight;
	}

	for (auto collider : pendingColliders)
	{
		colliders.push_back(collider);
	}
	pendingColliders.clear();

	for (auto renderable : pendingRenderable)
	{
		renderables.push_back(renderable);
	}
	pendingRenderable.clear();

}

// Renders any game objects
void Game::Render()
{
	const int HEIGHT = GAME_HEIGHT;
	const sf::Transform transform = [HEIGHT] {
		sf::Transformable transformation;
		transformation.setOrigin(0, HEIGHT);
		transformation.setScale(1.f, -1.f);
		return transformation.getTransform();
	}();

	// Clear the old frame so we can draw the next one
	window->clear(sf::Color(133, 204, 196, 255));
	window->setView(view);

	//Draw objects
	for (auto renderable : renderables)
	{
		renderable->Render(window, transform);
	}

	character->MoveCamera(view);
	window->display();
}

void Game::CheckForGameOver()
{
	if (!character->IsAlive())
	{
		EndGame();
	}
}

