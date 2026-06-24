#pragma once

#include "OwnedEngine3D/Export.h"
#include <string>

class OWNED_ENGINE_API EntityInfo
{
public :
	EntityInfo();
	EntityInfo(const std::string& name, std::uint16_t tag, std::uint16_t layer);

	//SERIALIZE
	//UNSERIALIZE

	//POPULATE
	//MULTI_POPULATE

private:
	std::string m_name;

	std::uint16_t m_layer;
	std::uint16_t m_tag;
};
