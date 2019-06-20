#pragma once
#include <vector>
#include "Rasterizer/Geometry/Vertex.h"

namespace Rasterizer::Resources
{
	class Mesh
	{
	public:
		Mesh(std::vector<Geometry::Vertex>&& p_vertices, std::vector<unsigned int>&& p_indices);
		~Mesh();

	private:
		std::vector<Geometry::Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};
}
