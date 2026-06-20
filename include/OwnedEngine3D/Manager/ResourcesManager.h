#pragma once
#include "OwnedEngine3D/Export.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

class GPUDevice;
class Shader;

class OWNED_ENGINE_API ResourcesManager
{
public:
	ResourcesManager(GPUDevice* device);
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;
	~ResourcesManager();

	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;

	const std::shared_ptr<Shader>& GetShader(const std::string& shaderName);

	void Purge();
	void CleanAll();

private:
	GPUDevice* m_device;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_loadedShaders;
};