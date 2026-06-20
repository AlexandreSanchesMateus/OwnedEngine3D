#pragma once
#include "OwnedEngine3D/Export.h"
#include <cstdint>
#include <SDL3/SDL.h>

class OWNED_ENGINE_API Core
{
public:
	Core(std::uint32_t flags = 0);
	Core(const Core&) = delete;
	Core(Core&&) = delete;
	~Core();

	Core& operator=(const Core&) = delete;
	Core& operator=(Core&&) = delete;

	static bool PollEvent(SDL_Event* event);
};