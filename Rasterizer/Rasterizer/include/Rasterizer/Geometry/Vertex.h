#pragma once

#include <glm/glm.hpp>

namespace Rasterizer::Geometry
{
	struct Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_normals;
		glm::vec2 m_textCoords;
		glm::vec3 m_tangents;
		glm::vec3 m_biTangents;
	};
}