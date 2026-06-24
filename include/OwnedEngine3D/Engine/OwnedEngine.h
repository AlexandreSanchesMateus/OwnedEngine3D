#pragma once

#include "OwnedEngine3D/Export.h"
#include <chrono>
#include <memory>
#include <vector>

#include "OwnedEngine3D/Engine/Core.h"
#include "OwnedEngine3D/Engine/GPUDevice.h"
#include "OwnedEngine3D/Engine/Window.h"
#include "OwnedEngine3D/Manager/ResourcesManager.h"
#include "OwnedEngine3D/Manager/EntitiesManager.h"
#include "OwnedEngine3D/Manager/InputManager.h"


struct EngineDescriptor
{
	std::string windowName;
	int windowWidth;
	int windowHeight;
	std::uint64_t windowFlags;
	std::uint32_t shaderFormat;

	float timestep;
	float fixeTimestep;

	std::string firstScene;
};



class IRenderer;

class OWNED_ENGINE_API OwnedEngine
{
public:
	OwnedEngine(const EngineDescriptor& descriptor);
	~OwnedEngine() = default;

	void Run();

	static std::chrono::milliseconds timestep;
	static std::chrono::milliseconds fixedTimestep;

	static EngineDescriptor PaseDescriptorFromFile(const std::string& configName);

private:
	void DrawScreen();

	// Engine
	Core m_core;
	Window m_window;
	GPUDevice m_gpuDevice;

	// Renders
	std::vector<std::unique_ptr<IRenderer>> m_renderers;

	// Services
	ResourcesManager m_resourcesManager;
	EntitiesManager m_entityManager;
	InputManager m_inputManager;
};