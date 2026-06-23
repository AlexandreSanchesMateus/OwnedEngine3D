#pragma once
#include "OwnedEngine3D/Export.h"
#include <string>
#include <filesystem>

class GPUDevice;
struct SDL_GPUShader;

class OWNED_ENGINE_API Shader
{
public:
	explicit Shader(GPUDevice* device, const std::filesystem::path& file, const std::string& entryPoint, bool isVertexSatge, int numSamplers, int numStorageBuffers, int numStorageTextures, int numUniformBuffers);
	~Shader();

	SDL_GPUShader* GetHandle() const;

private:
	//int GetShaderFormat(const std::string& extension);

	GPUDevice* m_device;
	SDL_GPUShader* m_shader;
};