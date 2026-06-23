#pragma once
#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/Math.h"

struct OWNED_ENGINE_API DebugVertex
{
	Vec3 position;
	Vec4 color;
};

struct OWNED_ENGINE_API MeshVertex
{
	Vec3 position;
	Vec2 uv;

	Vec3 normal;
	Vec4 tangent;
};

struct OWNED_ENGINE_API AnimatedMeshVertex : public MeshVertex
{
	// Not sure
	std::uint32_t boneIds[4];
	float weights[4];
};