#pragma once

#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/Transform.h"
#include "OwnedEngine3D/Math.h"

struct TransformComponent
{
	explicit TransformComponent(const Vec3& position, const Vec3& eulerAngleRad, const Vec3& scale);

	Transform transform;

	//SERIALIZE
	//UNSERIALIZE

	//POPULATE
	//MULTI_POPULATE
};