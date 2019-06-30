#include "Rasterizer/Resources/Mesh.h"

Rasterizer::Resources::Mesh::Mesh(std::vector<Geometry::Vertex>&& p_vertices, std::vector<unsigned int>&& p_indices)
	: m_vertices{ std::move(p_vertices) }, m_indices{ std::move(p_indices) }
{
}

Rasterizer::Resources::Mesh::~Mesh()
{
}

const std::vector<Rasterizer::Geometry::Vertex>& Rasterizer::Resources::Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<unsigned>& Rasterizer::Resources::Mesh::GetIndices() const
{
	return m_indices;
}
