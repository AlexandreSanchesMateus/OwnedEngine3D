#include "OwnedEngine3D/Engine/GPUDevice.h"
#include <SDL3/SDL_gpu.h>
#include <stdexcept>

GPUDevice::GPUDevice(std::uint32_t flags, bool debugMode)
{
	m_gpuDevice = SDL_CreateGPUDevice(flags, debugMode, NULL);
	if (!m_gpuDevice)
		throw std::runtime_error(std::string("Failed to create GPU Device, ") + SDL_GetError());
}

GPUDevice::~GPUDevice()
{
	SDL_DestroyGPUDevice(m_gpuDevice);
}

SDL_GPUDevice* GPUDevice::GetHandle() const
{
	return m_gpuDevice;
}