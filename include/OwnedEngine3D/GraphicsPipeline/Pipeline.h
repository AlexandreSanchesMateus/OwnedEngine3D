#pragma once
#include "OwnedEngine3D/Export.h"

class GPUDevice;
class Window;
class Shader;
struct SDL_GPUGraphicsPipeline;

struct OWNED_ENGINE_API PipelineDescriptor
{
	std::shared_ptr<Shader> vertexShader;
	std::shared_ptr<Shader> fragmentShader;

	// VERTEX LAYOUT
};

class OWNED_ENGINE_API Pipeline
{
public:
	Pipeline(GPUDevice* device, Window* window, const PipelineDescriptor& descriptor);
	~Pipeline();

	SDL_GPUGraphicsPipeline* GetHandle() const;

private:
	GPUDevice* m_device;
	SDL_GPUGraphicsPipeline* m_graphicsPipeline;
};