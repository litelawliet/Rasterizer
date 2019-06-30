#pragma once
#include <vector>
#include "Rasterizer/Geometry/Vertex.h"

namespace Rasterizer::Resources
{
	class Mesh final
	{
	public:
		Mesh(std::vector<Geometry::Vertex>&& p_vertices, std::vector<unsigned int>&& p_indices);
		~Mesh();

		const std::vector<Geometry::Vertex>& GetVertices() const;
		const std::vector<unsigned int>& GetIndices() const;

	private:
		std::vector<Geometry::Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};
}
