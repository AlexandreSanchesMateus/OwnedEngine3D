#include "OwnedEngine3D/Manager/ResourcesManager.h"
#include "OwnedEngine3D/File.h"
#include <stdexcept>

#include "OwnedEngine3D/GraphicsPipeline/Shader.h"


ResourcesManager::ResourcesManager(GPUDevice* device): m_device(device)
{
}

ResourcesManager::~ResourcesManager()
{
	CleanAll();
}

const std::shared_ptr<Shader>& ResourcesManager::GetShader(const std::string& shaderName)
{
	if (!shaderName.ends_with(".shader"))
		throw std::runtime_error("[Resources Manager] GetShader: Invalide file extention. Should be .shader");

	std::unordered_map<std::string, std::shared_ptr<Shader>>::iterator shader = m_loadedShaders.find(shaderName);
	if (shader != m_loadedShaders.end())
		return shader->second;

	rapidjson::Document properties = fileutil::ReadJsonFile(paths::Shaders / shaderName);

	std::string file = properties["file"].GetString();
	std::string entryPoint = properties["entry_point"].GetString();
	bool vertexStage = properties["vertex_stage"].GetBool();
	int numberSamplers = properties["number_samples"].GetInt();
	int numberStorageTextures = properties["number_storage_textures"].GetInt();
	int numberStorageBuffers = properties["number_storage_buffers"].GetInt();
	int numberUniformBuffers = properties["number_uniform_buffers"].GetInt();

	std::shared_ptr<Shader> ptr = std::make_shared<Shader>(
		m_device,
		paths::CompiledShaders / file,
		entryPoint,
		vertexStage,
		numberSamplers,
		numberStorageBuffers,
		numberStorageTextures,
		numberUniformBuffers
	);

	m_loadedShaders.emplace(shaderName, ptr);
	return ptr;
}

void ResourcesManager::Purge()
{

}

void ResourcesManager::CleanAll()
{
	
}