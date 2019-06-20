#pragma once
#include <string>
#include "Model.h"

namespace Rasterizer::Resources
{
	class Entity final
	{
	public:
		explicit Entity(std::string&& p_modelPath);

		const Model& GetModel() const noexcept;
		const glm::mat4x4& GetTransform() const noexcept;

	private:
		Model m_model;
		glm::mat4x4 m_transform;
	};
}
