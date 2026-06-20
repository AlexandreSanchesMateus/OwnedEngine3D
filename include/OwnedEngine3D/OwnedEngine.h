#pragma once

#include "OwnedEngine3D/Export.h"

class OWNED_ENGINE_API OwnedEngine
{
public:
	OwnedEngine();
	~OwnedEngine();

	void Run();

private:
	void DrawScreen();

};