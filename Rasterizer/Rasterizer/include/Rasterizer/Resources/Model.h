#pragma once
#include <memory>
#include "Rasterizer/Resources/Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Rasterizer::Resources
{
	class Model
	{
	public:
		explicit Model(const std::string& p_modelPath);
		~Model() = default;

	private:
		std::shared_ptr<Mesh> m_mesh;
		glm::mat4x4 m_transform;
	};
}
