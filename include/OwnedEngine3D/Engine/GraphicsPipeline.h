#pragma once
#include "OwnedEngine3D/Export.h"

class GPUDevice;
class Window;
class ResourcesManager;
struct SDL_GPUGraphicsPipeline;

class OWNED_ENGINE_API GraphicsPipeline
{
public:
	GraphicsPipeline(GPUDevice* device, Window* window, ResourcesManager* resourcesManager);
	~GraphicsPipeline();

	SDL_GPUGraphicsPipeline* GetHandle() const;

private:
	GPUDevice* m_device;
	SDL_GPUGraphicsPipeline* m_graphicsPipeline;
};