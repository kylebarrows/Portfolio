#pragma once

class Actor;

class Component
{
public:
	Component(class Actor* owner, int order = 100);

	virtual ~Component();

	virtual void Update(float deltaTime);

	int GetUpdateOrder() const { return updateOrder; }

protected:
	// Actor that this belongs to
	Actor* owner;

	// Order this component should update
	int updateOrder;
};