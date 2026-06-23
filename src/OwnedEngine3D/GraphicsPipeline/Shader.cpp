#include "OwnedEngine3D/GraphicsPipeline/Shader.h"
#include "OwnedEngine3D/Engine/GPUDevice.h"
#include "SDL3/SDL_gpu.h"

Shader::Shader(GPUDevice* device, const std::filesystem::path& file, const std::string& entryPoint, bool isVertexSatge, int numSamplers, int numStorageBuffers, int numStorageTextures, int numUniformBuffers) : m_device(device)
{
	std::size_t size;
	std::u8string path = file.u8string();
	void* code = SDL_LoadFile(reinterpret_cast<const char*>(path.c_str()), &size);

	SDL_GPUShaderCreateInfo shaderInfo;
	shaderInfo.code = (Uint8*)code;
	shaderInfo.code_size = size;
	shaderInfo.entrypoint = entryPoint.c_str();
	shaderInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
	shaderInfo.stage = isVertexSatge ? SDL_GPU_SHADERSTAGE_VERTEX : SDL_GPU_SHADERSTAGE_FRAGMENT;
	shaderInfo.num_samplers = numSamplers;
	shaderInfo.num_storage_buffers = numStorageBuffers;
	shaderInfo.num_storage_textures = numStorageTextures;
	shaderInfo.num_uniform_buffers = numUniformBuffers;

	m_shader = SDL_CreateGPUShader(device->GetHandle(), &shaderInfo);
	SDL_free(code);
}

Shader::~Shader()
{
	SDL_ReleaseGPUShader(m_device->GetHandle(), m_shader);
}

SDL_GPUShader* Shader::GetHandle() const
{
	return m_shader;
}