#include "OwnedEngine3D/Component/Transform.h"
#include <memory>
#include <glm/gtx/euler_angles.hpp>
#include <stdexcept>

Transform::Transform() : m_parent(nullptr), m_children(), m_position(0, 0, 0), m_rotation(1.0f, 0, 0, 0), m_scale(1, 1, 1)
{
}

Transform::Transform(const Vec3& position, const Vec3& eulerAngleRad, const Vec3& scale) : m_parent(nullptr), m_children(), m_position(position), m_rotation(eulerAngleRad), m_scale(scale)
{
}

Transform::Transform(const Transform& other) : m_parent(nullptr), m_children(), m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale)
{
	SetParent(other.m_parent);
}

Transform::Transform(Transform&& other) noexcept : m_parent(nullptr), m_children(std::move(other.m_children)), m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale)
{
	SetParent(other.m_parent);
	for (Transform* child : m_children)
		child->m_parent = this;
}

Transform::~Transform()
{
	if (m_parent)
		m_parent->DetachChild(this);

	for (Transform* child : m_children)
		child->m_parent = nullptr;
}

const Vec3& Transform::GetPosition() const
{
	return m_position;
}

const Quat& Transform::GetRotation() const
{
	return m_rotation;
}

const Vec3& Transform::GetEulerRotation() const
{
	return glm::eulerAngles(m_rotation);
}

const Vec3& Transform::GetScale() const
{
	return m_scale;
}

const Vec3& Transform::GetWorldPosition() const
{
	if (!m_parent)
		return m_position;

	return m_parent->TransformPoint(m_position);
}

const Quat& Transform::GetWorldRotation() const
{
	if (!m_parent)
		return m_rotation;

	return m_parent->GetWorldRotation() * m_rotation;
}

const Vec3& Transform::GetWorldEulerRotation() const
{
	return glm::eulerAngles(GetWorldRotation());
}

const Vec3& Transform::GetWorldScale() const
{
	if (!m_parent)
		return m_scale;

	return m_parent->GetWorldScale() * m_scale;
}

Transform* Transform::GetParent() const
{
	return m_parent;
}

const std::vector<Transform*>& Transform::GetChildren() const
{
	return m_children;
}

void Transform::Translate(const Vec3& translation)
{
	m_position += translation;
}

void Transform::Rotate(const Vec3& eulerAngle)
{
	Quat delta = Quat(eulerAngle);
	m_rotation = m_rotation * delta;
	m_rotation = glm::normalize(m_rotation);
}

void Transform::Rotate(float angle, const Vec3& axis)
{
	Quat delta = glm::angleAxis(angle, axis);
	m_rotation = m_rotation * delta;
	m_rotation = glm::normalize(m_rotation);
}

void Transform::Rotate(const Quat& quaternion)
{
	m_rotation = m_rotation * quaternion;
	m_rotation = glm::normalize(m_rotation);
}

void Transform::Scale(const Vec3& scale)
{
	m_scale *= scale;
}

void Transform::Scale(float scale)
{
	m_scale *= scale;
}

void Transform::SetParent(Transform* parent)
{
	if (m_parent == parent)
		return;

	if (m_parent)
		m_parent->DetachChild(this);

	m_parent = parent;
	if (m_parent)
		m_parent->AttachChild(this);
}

void Transform::SetPosition(const Vec3& position)
{
	m_position = position;
}

void Transform::SetRotation(const Vec3& eulerAngle)
{
	m_rotation = Quat(eulerAngle);
}

void Transform::SetRotation(const Quat& quaternion)
{
	m_rotation = quaternion;
}

void Transform::SetScale(const Vec3& scale)
{
	m_scale = scale;
}

Vec3 Transform::TransformPoint(const Vec3& localPosition) const
{
	Vec4 result = GetWorldTransformMatrix() * Vec4(localPosition, 1.0f);
	return Vec3(result);
}

Vec3 Transform::TransformInvertedPoint(const Vec3& localPosition) const
{
	Vec4 result = GetWorldInvertMatrix() * Vec4(localPosition, 1.0f);
	return Vec3(result);
}

Mat4 Transform::GetTranslationMatrix() const
{
	return glm::translate(Mat4(1.0f), m_position);
}

Mat4 Transform::GetRotationMatrix() const
{
	return glm::toMat4(m_rotation);
}

Mat4 Transform::GetScaleMatrix() const
{
	return glm::scale(Mat4(1.0f), m_scale);
}

Mat4 Transform::GetTransformMatrix() const
{
	// TRS methode
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}

Mat4 Transform::GetInvertMatrix() const
{
	return glm::inverse(GetTransformMatrix());
}

Mat4 Transform::GetWorldTransformMatrix() const
{
	if (m_parent)
		return m_parent->GetWorldTransformMatrix() * GetTransformMatrix();

	return GetTransformMatrix();
}

Mat4 Transform::GetWorldInvertMatrix() const
{
	return glm::inverse(GetWorldTransformMatrix());
}

void Transform::AttachChild(Transform* transform)
{
	m_children.push_back(transform);
}

void Transform::DetachChild(Transform* transform)
{
	std::vector<Transform*>::iterator it = std::find(m_children.begin(), m_children.end(), transform);

	if (it != m_children.end())
		m_children.erase(it);
}
