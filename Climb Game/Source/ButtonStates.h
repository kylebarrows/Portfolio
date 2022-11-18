#pragma once

class ButtonStates
{
public:
	bool isPressed;
	bool wasPressed;

	void Update(bool isPressed)
	{
		wasPressed = this->isPressed;
		this->isPressed = isPressed;
	}
};