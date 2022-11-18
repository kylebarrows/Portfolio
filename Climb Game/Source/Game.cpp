#include "Game.h"
#include "ActorManager.h"
#include "Actor.h"
#include "Character.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "Climbable.h"

Game::Game()
{
	window = nullptr;
	test = nullptr;
	actorManager = nullptr;
	ground = nullptr;
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
		actorManager->Update(deltaTime);
		Render();
	}
}

void Game::EndGame()
{

}

const bool Game::IsRunning() const
{
	return window->isOpen();
}

void Game::AddActor(Actor* actor)
{
	actorManager->AddActor(actor);
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
	// Currently testing mechanics of the game, base stuff
	character = new Character(this);

	sf::Vector2f groundPos = sf::Vector2f(-25.0, -12.0);
	sf::Vector2f groundDimensions = sf::Vector2f(50.0f, 5.0f);
	ground = new Climbable(this, groundPos, groundDimensions);

	sf::Vector2f wallPos = sf::Vector2f(7.0, -10.0);
	sf::Vector2f wallDimensions = sf::Vector2f(2.0, 20.0f);
	wall = new Climbable(this, wallPos, wallDimensions);

	wallPos = sf::Vector2f(-7.0, 5.0);
	wallDimensions = sf::Vector2f(2.0, 20.0f);
	wall2 = new Climbable(this, wallPos, wallDimensions);

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

	sf::Vector2f characterLocation = character->GetLocation();
	view.setCenter(characterLocation.x * 50, characterLocation.y * -50);
	window->display();
}

