#pragma once

#include "OwnedEngine3D/Export.h"

class OWNED_ENGINE_API IRenderer
{
public:
	virtual void Render() = 0;
};