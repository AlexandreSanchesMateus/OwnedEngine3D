#pragma once

#include "OwnedEngine3D/Export.h"
#include <entt/fwd.hpp>

typedef struct SDL_GPURenderPass SDL_GPURenderPass;

class OWNED_ENGINE_API IRenderer
{
public:
	virtual void Render(SDL_GPURenderPass* renderPass, entt::registry* registry) = 0;
	virtual unsigned int Priority() const = 0;
};