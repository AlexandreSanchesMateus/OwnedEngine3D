#pragma once
#include "OwnedEngine3D/Export.h"
#include <entt/entt.hpp>
#include <vector>

class OWNED_ENGINE_API EntitiesManager
{
public:
	EntitiesManager();
	~EntitiesManager();

	entt::registry* GetRegister();
	entt::handle CreateEntity(const std::string& name);

	void ClearRegistry();

private:
	entt::registry m_registry;

	std::vector<std::string> m_tagsName;   // TODO
	std::vector<std::string> m_layerName;  // TODO
};