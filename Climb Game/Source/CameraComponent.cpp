#include "CameraComponent.h"

CameraComponent::CameraComponent(class Actor* owner, int updateOrder /*= 200*/)
	:Component(owner)
{
	view = new sf::View;
	view->reset(sf::FloatRect(100, 100, 400, 200));
}
