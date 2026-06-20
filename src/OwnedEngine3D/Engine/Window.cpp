#include "OwnedEngine3D/Engine/Window.h"
#include "OwnedEngine3D/Engine/GPUDevice.h"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_gpu.h>
#include <stdexcept>

Window::Window(const std::string& title, int wigth, int height, std::uint32_t flags) : m_device(nullptr)
{
	m_window = SDL_CreateWindow(title.c_str(), wigth, height, flags);

	if (!m_window)
		throw std::runtime_error(std::string("Failed to create window, ") + SDL_GetError());
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
}

void Window::ClaimWindowForGPUDevice(GPUDevice* device)
{
	if (!SDL_ClaimWindowForGPUDevice(device->GetHandle(), m_window))
		throw std::runtime_error(std::string("Failed to link GPU Device to Window, ") + SDL_GetError());

	m_device = device;
}

SDL_Window* Window::GetHandle() const
{
	return m_window;
}