#pragma once

#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/EntityMetadata.h"
#include <string>

struct OWNED_ENGINE_API MetadataComponant
{
	explicit MetadataComponant(const std::string& name, std::uint16_t tag, std::uint16_t layer);

	EntityMetadata metadata;

	//SERIALIZE
	//UNSERIALIZE

	//POPULATE
	//MULTI_POPULATE
};
