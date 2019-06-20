#include "Rasterizer/Resources/Model.h"
#include "Rasterizer/Resources/Loaders/MeshLoader.h"

Rasterizer::Resources::Model::Model(std::string&& p_modelPath)
	: m_meshFile{ std::move(p_modelPath) }
{
	m_mesh = std::make_shared<Mesh>(*Loaders::MeshLoader::Load(m_meshFile));
}

const std::shared_ptr<Rasterizer::Resources::Mesh>& Rasterizer::Resources::Model::GetMesh() const noexcept
{
	return m_mesh;
}

const std::string& Rasterizer::Resources::Model::GetMeshFile() const noexcept
{
	return m_meshFile;
}
