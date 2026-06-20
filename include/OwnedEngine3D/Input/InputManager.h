#pragma once
#include "OwnedEngine3D/Export.h"
#include <cstdint>

union SDL_Event;

class OWNED_ENGINE_API InputManager
{
public:
	InputManager();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	~InputManager();

	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	void HandleEvent(const SDL_Event& event, double deltaTime);
	void HandleLateEvent(double deltaTime);

private:

};