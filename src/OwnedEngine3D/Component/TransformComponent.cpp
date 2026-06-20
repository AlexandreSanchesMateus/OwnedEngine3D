#include "OwnedEngine3D/Component/TransformComponent.h"

TransformComponent::TransformComponent(const Vec3& position, const Vec3& eulerAngleRad, const Vec3& scale) : transform(position, eulerAngleRad, scale)
{
}
