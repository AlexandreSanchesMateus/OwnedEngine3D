#include "OwnedEngine3D/Mesh.h"

Mesh::Mesh() : m_vertices(), m_indexes()
{
}

Mesh::Mesh(const std::vector<MeshVertex>& vertices, const std::vector<int>& indexes) : m_vertices(vertices), m_indexes(indexes)
{
}

Mesh::Mesh(std::vector<MeshVertex>&& vertices, std::vector<int>&& indexes) : m_vertices(vertices), m_indexes(indexes)
{
}

Mesh::~Mesh()
{
}

const std::vector<MeshVertex>& Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<int>& Mesh::GetIndexes() const
{
	return m_indexes;
}
