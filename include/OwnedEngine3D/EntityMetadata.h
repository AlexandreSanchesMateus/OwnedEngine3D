#pragma once

#include "OwnedEngine3D/Export.h"
#include <string>

struct OWNED_ENGINE_API EntityMetadata
{
	std::string name;
	std::uint8_t tag;
	std::uint16_t layer;
};