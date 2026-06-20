#pragma once
#include "OwnedEngine3D/Export.h"
#include <string>

class GPUDevice;
struct SDL_Window;

class OWNED_ENGINE_API Window
{
public:
	Window(const std::string& title, int wigth, int height, std::uint32_t flags = 0);
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	~Window();

	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	void ClaimWindowForGPUDevice(GPUDevice* device);

	SDL_Window* GetHandle() const;

private:
	GPUDevice* m_device;
	SDL_Window* m_window;
};