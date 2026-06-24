#pragma once
#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/Math.h"
#include <vector>

class OWNED_ENGINE_API Transform
{
public:
	Transform();
	Transform(const Vec3& position, const Vec3& eulerAngleRad, const Vec3& scale);
	Transform(const Transform& other);
	Transform(Transform&& other) noexcept;
	~Transform();

	Transform& operator=(const Transform& other) = delete;
	Transform& operator=(Transform&& other) = delete;


	const Vec3& GetPosition() const;
	const Quat& GetRotation() const;
	const Vec3& GetEulerRotation() const;
	const Vec3& GetScale() const;
	
	const Vec3& GetWorldPosition() const;
	const Quat& GetWorldRotation() const;
	const Vec3& GetWorldEulerRotation() const;
	const Vec3& GetWorldScale() const;

	Transform* GetParent() const;
	const std::vector<Transform*>& GetChildren() const;

	void Translate(const Vec3& translation);
	void Rotate(const Vec3& eulerAngleRad);
	void Rotate(float angle, const Vec3& axis);
	void Rotate(const Quat& quaternion);
	void Scale(const Vec3& scale);
	void Scale(float scale);

	void SetParent(Transform* parent);

	void SetPosition(const Vec3& position);
	void SetRotation(const Vec3& eulerAngleRad);
	void SetRotation(const Quat& quaternion);
	void SetScale(const Vec3& scale);

	Vec3 TransformPoint(const Vec3& localPosition) const;
	Vec3 TransformInvertedPoint(const Vec3& localPosition) const;

	Mat4 GetTranslationMatrix() const;
	Mat4 GetRotationMatrix() const;
	Mat4 GetScaleMatrix() const;

	Mat4 GetTransformMatrix() const;
	Mat4 GetInvertMatrix() const;

	Mat4 GetWorldTransformMatrix() const;
	Mat4 GetWorldInvertMatrix() const;

	//SERIALIZE
	//UNSERIALIZE

	//POPULATE
	//MULTI_POPULATE

private:
	void AttachChild(Transform* transform);
	void DetachChild(Transform* transform);

	Transform* m_parent;
	std::vector<Transform*> m_children;
	
	Vec3 m_position;
	Quat m_rotation;
	Vec3 m_scale;
};
