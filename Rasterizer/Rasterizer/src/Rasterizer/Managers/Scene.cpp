#include "Rasterizer/Managers/Scene.h"

std::unique_ptr<Rasterizer::Managers::Scene> Rasterizer::Managers::Scene::m_instance;

const std::list<Rasterizer::Resources::Entity>& Rasterizer::Managers::Scene::GetEntities() const noexcept
{
	return m_entities;
}

void Rasterizer::Managers::Scene::AddEntity(std::string&& p_modelEntity)
{
	m_entities.emplace_back(std::move(p_modelEntity));
}

std::unique_ptr<Rasterizer::Managers::Scene>& Rasterizer::Managers::Scene::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::make_unique<Scene>();
	}

	return m_instance;
}
