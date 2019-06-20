#include "Rasterizer/Resources/Model.h"
#include "Rasterizer/Resources/Loaders/MeshLoader.h"

Rasterizer::Resources::Model::Model(const std::string& p_modelPath)
	: m_transform{}
{
	m_mesh = std::make_shared<Mesh>(*Loaders::MeshLoader::Load(p_modelPath));
}