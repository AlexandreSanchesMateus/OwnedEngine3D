#pragma once

#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/Render/IRenderer.h"

class MeshRenderer : public IRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Render(SDL_GPURenderPass* renderPass, entt::registry* registry) override;
	unsigned int Priority() const override;

private:
	
};