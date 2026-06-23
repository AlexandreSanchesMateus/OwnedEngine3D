#include "OwnedEngine3D/OwnedEngine.h"
#include "OwnedEngine3D/File.h"
#include <thread>
#include <SDL3/SDL.h>

#include "OwnedEngine3D/Render/IRenderer.h"

std::chrono::milliseconds OwnedEngine::timestep = std::chrono::milliseconds(5);          // around 200 fps
std::chrono::milliseconds OwnedEngine::fixedTimestep = std::chrono::milliseconds(16);    // around 60 fps

#ifdef WITH_EDITOR
#define DEBUG_GPU_MODE true
#else 
#define DEBUG_GPU_MODE false
#endif


OwnedEngine::OwnedEngine(const EngineDescriptor& descriptor)
	: m_core(),
	m_window(descriptor.windowName, descriptor.windowWidth, descriptor.windowHeight, descriptor.windowFlags),
	m_gpuDevice(descriptor.shaderFormat, DEBUG_GPU_MODE),
	m_resourcesManager(&m_gpuDevice),
	m_entityManager(),
	m_inputManager()
{
	timestep = std::chrono::milliseconds((long)descriptor.timestep);
	fixedTimestep = std::chrono::milliseconds((long)descriptor.fixeTimestep);

	// Load Pipelines (or renderer)

}

void OwnedEngine::Run()
{
	std::chrono::nanoseconds lag(0);
	auto lateTime = std::chrono::high_resolution_clock::now();

	bool running = true;
	while (running)
	{
		auto time = std::chrono::high_resolution_clock::now();
		auto deltaTime = time - lateTime;
		double deltaTimeSecond = std::chrono::duration<double>(deltaTime).count();

		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
		lateTime = time;

		// Fixed Update (timestep)
		while (lag >= fixedTimestep)
		{
			lag -= fixedTimestep;
		}

		SDL_Event event;
		while (Core::PollEvent(&event))
		{
			m_inputManager.HandleEvent(event, deltaTimeSecond);

			if (event.type == SDL_EVENT_QUIT)
				running = false;
		}

		m_inputManager.HandleLateEvent(deltaTimeSecond);


		// Update (delta_time, interpolation)
		// double interp = (double)lag.count() / (double)fixed_timestep.count(); // Between 0 and 1
		// Render frame whith interpolation if necessery


		// Draw
		DrawScreen();


		// Frame cap
		auto endTime = std::chrono::high_resolution_clock::now();
		auto sleepTime = time + timestep - endTime;

		if (sleepTime > std::chrono::milliseconds(0))
			std::this_thread::sleep_for(sleepTime);
	}
}

EngineDescriptor OwnedEngine::PaseDescriptorFromFile(const std::string& configName)
{
	// TODO
	// Parse Json File

	EngineDescriptor descriptor{
		"Owned Engine 3D",
		1280,
		720,
		NULL,
		SDL_GPU_SHADERFORMAT_SPIRV
	};

	return descriptor;
}




void OwnedEngine::DrawScreen()
{
	SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(m_gpuDevice.GetHandle());

	SDL_GPUTexture* swapchainTexture;
	Uint32 width, height;
	SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, m_window.GetHandle(), &swapchainTexture, &width, &height);


	if (!swapchainTexture)
	{
		SDL_SubmitGPUCommandBuffer(commandBuffer);
		return;
	}

	// Clear screen
	SDL_GPUColorTargetInfo colorTargetInfo{};
	colorTargetInfo.clear_color = { 0.f, 0.f, 0.f };
	colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
	colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
	colorTargetInfo.texture = swapchainTexture;


	SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, NULL);


	// Uniform buffer
	// Récupère la caméra
	// Projection * View

	for (std::vector<std::unique_ptr<IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); ++it)
	{
		// Need to reference RenderPass and ECS registry
		// BindPipeline
		// DrawPrimitives
		(*it)->Render();
	}

	SDL_EndGPURenderPass(renderPass);
	SDL_SubmitGPUCommandBuffer(commandBuffer);
}
