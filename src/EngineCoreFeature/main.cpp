#include <thread>
#include <chrono>

#include "OwnedEngine3D/Engine/Core.h"
#include "OwnedEngine3D/Engine/GPUDevice.h"
#include "OwnedEngine3D/Engine/Window.h"
#include "OwnedEngine3D/Engine/GraphicsPipeline.h"

#include "OwnedEngine3D/Manager/ResourcesManager.h"
#include "OwnedEngine3D/Engine/GraphicsPipeline.h"
#include "OwnedEngine3D/Input/InputManager.h"

// Tempo
#include <SDL3/SDL.h>
#include "OwnedEngine3D/GraphicsPipeline/Vertex.h"
#include "OwnedEngine3D/Transform.h"

#include "OwnedEngine3D/Logger/Logger.h"
#include "OwnedEngine3D/Logger/LoggerInstance.h"

#include "OwnedEngine3D/Mesh.h"


static DebugVertex vertices[3]
{
	{{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},   // top vertex
	{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}}, // bottom left vertex
	{{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}},  // bottom right vertex
};


int main(int argc, char* argv[])
{
#if 0

	

#else

	// Engine core
	Core core;
	Window window("Owned Engine 3D", 1280, 720, 0);
	GPUDevice device(SDL_GPU_SHADERFORMAT_SPIRV, false);

	window.ClaimWindowForGPUDevice(&device);

	ResourcesManager resources(&device);
	InputManager inputManager;

	// ##################### RENDER TESTING #####################

	Logger::SetLog(std::make_unique<ConsoleLogger>());

	std::vector<MeshVertex> vert = {
		{{-1, -1, 0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{1, -1, 0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{-1, 1, 0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{1, 1, 0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{-1, -1, -0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{1, -1, -0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{-1, 1, -0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
		{{1, 1, -0.5f}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}},
	};

	std::vector<int> ind = {
		//Top
		2, 6, 7,
		2, 3, 7,

		//Bottom
		0, 4, 5,
		0, 1, 5,

		//Left
		0, 2, 6,
		0, 4, 6,

		//Right
		1, 3, 7,
		1, 5, 7,

		//Front
		0, 2, 3,
		0, 1, 3,

		//Back
		4, 6, 7,
		4, 5, 7
	};

	Mesh cube(std::move(vert), std::move(ind));


	GraphicsPipeline graphicsPipeline(&device, &window, &resources);

	SDL_GPUBuffer* vertexBuffer;
	SDL_GPUTransferBuffer* transferBuffer;

	Transform triangleTrs;
	DebugVertex trsVertices[3];
	memcpy(trsVertices, vertices, sizeof(vertices));


	float angle = 0;
	Transform camera;
	bool keys[4] = {false, false, false, false};

	Mat4 perspectiveMatrix = glm::perspective(60.0f, 1280.0f / 720, 0.1f, 1000.0f);

	{
		// create the vertex buffer
		SDL_GPUBufferCreateInfo bufferInfo{};
		bufferInfo.size = sizeof(trsVertices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
		vertexBuffer = SDL_CreateGPUBuffer(device.GetHandle(), &bufferInfo);

		// create a transfer buffer to upload to the vertex buffer
		SDL_GPUTransferBufferCreateInfo transferInfo{};
		transferInfo.size = sizeof(trsVertices);
		transferInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
		transferBuffer = SDL_CreateGPUTransferBuffer(device.GetHandle(), &transferInfo);

		// fill the transfer buffer
		DebugVertex* data = (DebugVertex*)SDL_MapGPUTransferBuffer(device.GetHandle(), transferBuffer, false);
		SDL_memcpy(data, vertices, sizeof(vertices));
		SDL_UnmapGPUTransferBuffer(device.GetHandle(), transferBuffer);

		// start a copy pass
		SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device.GetHandle());
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);

		// where is the data
		SDL_GPUTransferBufferLocation location{};
		location.transfer_buffer = transferBuffer;
		location.offset = 0;

		// where to upload the data
		SDL_GPUBufferRegion region{};
		region.buffer = vertexBuffer;
		region.size = sizeof(vertices);
		region.offset = 0;

		// upload the data
		SDL_UploadToGPUBuffer(copyPass, &location, &region, true);

		// end the copy pass
		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(commandBuffer);
	}
	
	// #############################################################

	


	const std::chrono::milliseconds timestep(5); // around 200 fps
	const std::chrono::milliseconds fixedTimestep(16); // around 60 fps

	std::chrono::nanoseconds lag(0);
	auto lateTime =  std::chrono::high_resolution_clock::now();

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
			// Process gamplay event (keyboard / mouse + gamepad)
			inputManager.HandleEvent(event, deltaTimeSecond);

			if (event.type == SDL_EVENT_QUIT)
				running = false;

			if (event.type == SDL_EVENT_KEY_DOWN)
			{
				if (event.key.key == SDLK_LEFT)
					keys[0] = true;

				if (event.key.key == SDLK_RIGHT)
					keys[1] = true;
				
				if (event.key.key == SDLK_UP)
					keys[2] = true;

				if (event.key.key == SDLK_DOWN)
					keys[3] = true;

			}

			if (event.type == SDL_EVENT_KEY_UP)
			{
				if (event.key.key == SDLK_LEFT)
					keys[0] = false;

				if (event.key.key == SDLK_RIGHT)
					keys[1] = false;

				if (event.key.key == SDLK_UP)
					keys[2] = false;

				if (event.key.key == SDLK_DOWN)
					keys[3] = false;
			}
		}
		
		inputManager.HandleLateEvent(deltaTimeSecond);

		
		
		// Update (delta_time, interpolation)

		//double interp = (double)lag.count() / (double)fixed_timestep.count(); // Between 0 and 1
		// Render frame whith interpolation if necessery


		// ##################### RENDER TESTING #####################
		

		if (keys[0])
			camera.Translate({ 0.5f * deltaTimeSecond, 0, 0 });
		else if (keys[1])
			camera.Translate({ -0.5f * deltaTimeSecond, 0, 0 });

		if (keys[2])
			camera.Translate({ 0, 0,  0.5f * deltaTimeSecond });
		else if (keys[3])
			camera.Translate({ 0, 0,  -0.5f * deltaTimeSecond });


		bool keyPressed = keys[0] || keys[1] || keys[2] || keys[3];
		if (keyPressed)
		{
			Vec3 pos = camera.GetPosition();
			Logger::Log("Camera Position : {}, {}, {}", pos.x, pos.y, pos.z);
		}

		/*angle += deltaTimeSecond * 10.0f;
		camera.SetPosition({
			std::cos(glm::radians(angle)),
			0.0f,
			std::sin(glm::radians(angle))
			});

		Mat4 lookingAt = glm::lookAt(camera.GetPosition(), { 0, 0, 0 }, { 0, 1, 0 });*/
		
		// rotate triangle
		//triangleTrs.Rotate(Vec3(0, glm::radians(80 * deltaTimeSecond), 0));

		SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device.GetHandle());

		SDL_GPUTexture* swapchainTexture;
		Uint32 width, height;
		SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window.GetHandle(), &swapchainTexture, &width, &height);

		if (swapchainTexture == NULL)
		{
			// you must always submit the command buffer
			SDL_SubmitGPUCommandBuffer(commandBuffer);
		}
		else
		{

			// Recalculate each vertex positions
			Mat4 viewMatrix = camera.GetInvertMatrix();
			Mat4 modelMatrix = triangleTrs.GetTransformMatrix();

			Mat4 mvp = perspectiveMatrix * viewMatrix * modelMatrix;
			for (int i = 0; i < 3; ++i)
			{
				Vec4 p = mvp * Vec4(vertices[i].position, 1.0f);

				p.x /= p.w;
				p.y /= p.w;
				p.z /= p.w;

				trsVertices[i].position = Vec3(p);
			}


			// fill the rectangle buffer
			DebugVertex* data = (DebugVertex*)SDL_MapGPUTransferBuffer(device.GetHandle(), transferBuffer, false);
			SDL_memcpy(data, trsVertices, sizeof(trsVertices));
			SDL_UnmapGPUTransferBuffer(device.GetHandle(), transferBuffer);

			// start a copy pass
			SDL_GPUCommandBuffer* vertexCommandBuffer = SDL_AcquireGPUCommandBuffer(device.GetHandle());
			SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(vertexCommandBuffer);

			// where is the data
			SDL_GPUTransferBufferLocation location{};
			location.transfer_buffer = transferBuffer;
			location.offset = 0;

			// where to upload the data
			SDL_GPUBufferRegion region{};
			region.buffer = vertexBuffer;
			region.size = sizeof(trsVertices);
			region.offset = 0;

			// upload the data
			SDL_UploadToGPUBuffer(copyPass, &location, &region, true);

			// end the copy pass
			SDL_EndGPUCopyPass(copyPass);
			SDL_SubmitGPUCommandBuffer(vertexCommandBuffer);



			// Clear screen
			SDL_GPUColorTargetInfo colorTargetInfo{};
			colorTargetInfo.clear_color = { 240 / 255.0f, 240 / 255.0f, 240 / 255.0f, 255 / 255.0f };
			colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
			colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
			colorTargetInfo.texture = swapchainTexture;


			// DRAW CALLS
			
			// begin a render pass
			SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, NULL);

			// bind the pipeline
			SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline.GetHandle());

			// bind the vertex buffer
			SDL_GPUBufferBinding bufferBindings[1];
			bufferBindings[0].buffer = vertexBuffer;
			bufferBindings[0].offset = 0;

			SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings, 1);

			// issue a draw call
			SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

			// end the render pass
			SDL_EndGPURenderPass(renderPass);

			SDL_SubmitGPUCommandBuffer(commandBuffer);


		}
		// ##########################################################
		
		

		// Frame cap
		auto endTime = std::chrono::high_resolution_clock::now();
		auto sleepTime = time + timestep - endTime;

		if (sleepTime > std::chrono::milliseconds(0))
			std::this_thread::sleep_for(sleepTime);
	}


	// ##################### RENDER TESTING #####################
	SDL_ReleaseGPUBuffer(device.GetHandle(), vertexBuffer);
	SDL_ReleaseGPUTransferBuffer(device.GetHandle(), transferBuffer);
	// ##########################################################

#endif
	return 0;
}
