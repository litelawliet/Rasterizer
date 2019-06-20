#pragma once
#include "Rasterizer/Resources/Mesh.h"
#include <string>
#include <assimp/mesh.h>

namespace Rasterizer::Resources::Loaders
{
	class MeshLoader
	{
	public:
		MeshLoader() = delete;
		~MeshLoader() = delete;

		static Mesh* Load(const std::string& p_modelPath);
		static bool Destroy(Mesh*& p_meshInstanceReference) noexcept;

	private:
		static void ProcessMesh(aiMesh* p_mesh);

		static unsigned int m_offset;
		static std::vector<Rasterizer::Geometry::Vertex> m_vertices;
		static std::vector<unsigned int> m_indices;
	};
}
