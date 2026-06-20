#pragma once

#include "OwnedEngine3D/Export.h"
#include "OwnedEngine3D/Vertex.h"
#include <vector>

class OWNED_ENGINE_API Mesh
{
public:
	Mesh();
	Mesh(const std::vector<MeshVertex>& vertices, const std::vector<int>& indexes);
	Mesh(std::vector<MeshVertex>&& vertices, std::vector<int>&& indexes);
	~Mesh();

	const std::vector<MeshVertex>& GetVertices() const;
	const std::vector<int>& GetIndexes() const;

private:
	
	std::vector<MeshVertex> m_vertices;
	std::vector<int> m_indexes;

	// List Vertex
	//     Should have position, UV
	//     May have normal, tangent, bitangent
	
	// List d'Index

	// Struct Skeleton
	//    List of bones
	//        name + Mat4 inverseBindMatrix;
};