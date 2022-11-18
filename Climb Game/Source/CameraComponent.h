#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class CameraComponent : Component
{
public:
	CameraComponent(class Actor* owner, int updateOrder = 200);

private:
	sf::View* view;
};