#include "Rasterizer/Resources/Mesh.h"

Rasterizer::Resources::Mesh::Mesh(std::vector<Geometry::Vertex>&& p_vertices, std::vector<unsigned int>&& p_indices)
	: m_vertices{ std::move(p_vertices) }, m_indices{ std::move(p_indices) }
{
}

Rasterizer::Resources::Mesh::~Mesh()
{
}
