#pragma once
#include <memory>
#include "Rasterizer/Resources/Mesh.h"
#include <string>

namespace Rasterizer::Resources
{
	class Model final
	{
	public:
		explicit Model(std::string&& p_modelPath);
		~Model() = default;

		const std::shared_ptr<Mesh>& GetMesh() const noexcept;
		const std::string& GetMeshFile() const noexcept;

	private:
		std::shared_ptr<Mesh> m_mesh;
		std::string m_meshFile;
	};
}
