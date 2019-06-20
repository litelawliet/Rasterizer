#include "Rasterizer/Resources/Entity.h"

Rasterizer::Resources::Entity::Entity(std::string&& p_modelPath)
	: m_model{ std::move(p_modelPath) }, m_transform{}
{
}

const Rasterizer::Resources::Model& Rasterizer::Resources::Entity::GetModel() const noexcept
{
	return m_model;
}

const glm::mat4x4& Rasterizer::Resources::Entity::GetTransform() const noexcept
{
	return m_transform;
}
