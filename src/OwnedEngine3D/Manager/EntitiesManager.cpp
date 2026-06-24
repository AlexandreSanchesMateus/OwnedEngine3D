#include "OwnedEngine3D/Manager/EntitiesManager.h"
#include "OwnedEngine3D/File.h"
#include "OwnedEngine3D/Component/EntityInfo.h"


EntitiesManager::EntitiesManager() : m_registry(entt::registry())
{
	/*rapidjson::Document doc = fileutil::ReadJsonFile(paths::Configs / fileName);
	const rapidjson::Value& tagArray = doc["tags"];
	const rapidjson::Value& layerArray = doc["layers"];

	for (rapidjson::Value::ConstValueIterator it = tagArray.Begin(); it != tagArray.End(); ++it)
	{
		m_tagsName.push_back(it->GetString());
	}

	for (rapidjson::Value::ConstValueIterator it = layerArray.Begin(); it != layerArray.End(); ++it)
	{
		m_layerName.push_back(it->GetString());
	}*/
}

EntitiesManager::~EntitiesManager()
{
}

entt::registry* EntitiesManager::GetRegister()
{
	return &m_registry;
}

entt::handle EntitiesManager::CreateEntity(const std::string& name)
{
	entt::handle entity(m_registry, m_registry.create());
	entity.emplace<EntityInfo>(name, 0, 0);
	return entity;
}

void EntitiesManager::ClearRegistry()
{
	m_registry.clear();
}
