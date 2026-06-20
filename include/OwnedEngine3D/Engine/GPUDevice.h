#pragma once
#include "OwnedEngine3D/Export.h"
#include <cstdint>

struct SDL_GPUDevice;

class OWNED_ENGINE_API GPUDevice
{
public:
	GPUDevice(std::uint32_t flags, bool debugMode);
	~GPUDevice();

	GPUDevice(const GPUDevice&) = delete;
	GPUDevice(GPUDevice&&) = delete;

	GPUDevice& operator=(const GPUDevice&) = delete;
	GPUDevice& operator=(GPUDevice&&) = delete;

	SDL_GPUDevice* GetHandle() const;

private:
	SDL_GPUDevice* m_gpuDevice;
};