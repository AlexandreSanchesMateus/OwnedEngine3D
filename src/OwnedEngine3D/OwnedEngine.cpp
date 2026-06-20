#include "OwnedEngine3D/OwnedEngine.h"
#include "OwnedEngine3D/Engine/Core.h"

#include <thread>
#include <chrono>
#include <SDL3/SDL.h>

OwnedEngine::OwnedEngine()
{
	// Load from config files

	// Init Window
	// Init GPU Device
	// Init Pipelines

	// Init Services
	// Ressources
	// Input
}

OwnedEngine::~OwnedEngine()
{
	// Uninitialize if needed
	// A lot of wrapper
}

void OwnedEngine::Run()
{
	// Should be a variable in the class
	// Loaded from config file
	const std::chrono::milliseconds timestep(5); // around 200 fps
	const std::chrono::milliseconds fixedTimestep(16); // around 60 fps


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
			// inputManager.HandleEvent(event, deltaTimeSecond);

			if (event.type == SDL_EVENT_QUIT)
				running = false;
		}

		// inputManager.HandleLateEvent(deltaTimeSecond);


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




void OwnedEngine::DrawScreen()
{
	/*SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device.GetHandle());

	SDL_GPUTexture* swapchainTexture;
	Uint32 width, height;
	SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window.GetHandle(), &swapchainTexture, &width, &height);


	if (!swapchainTexture)
	{
		SDL_SubmitGPUCommandBuffer(commandBuffer);
		return;
	}

	// Clear screen
	SDL_GPUColorTargetInfo colorTargetInfo{};
	colorTargetInfo.clear_color = { 240 / 255.0f, 240 / 255.0f, 240 / 255.0f, 255 / 255.0f };
	colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
	colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
	colorTargetInfo.texture = swapchainTexture;


	// Draw calls :
	//     BeginRenderPass
	//     BindPipeline
	//     DrawPrimitives
	//     EndRender¨Pass

	// For each pipeline (model, skelet animation, skybox, UI, ...)


	SDL_SubmitGPUCommandBuffer(commandBuffer);*/
}
