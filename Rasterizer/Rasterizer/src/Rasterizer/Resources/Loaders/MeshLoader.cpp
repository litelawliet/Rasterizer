#include "Rasterizer/Resources/Loaders/MeshLoader.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

unsigned int Rasterizer::Resources::Loaders::MeshLoader::m_offset = 0;
std::vector<Rasterizer::Geometry::Vertex> Rasterizer::Resources::Loaders::MeshLoader::m_vertices = {};
std::vector<unsigned int>Rasterizer::Resources::Loaders::MeshLoader::m_indices = {};

void Rasterizer::Resources::Loaders::MeshLoader::ProcessMesh(aiMesh* p_mesh)
{
	for (unsigned int j = 0; j < p_mesh->mNumVertices; ++j)
	{
		//Create a vertex to store the mesh's vertices temporarily
		Geometry::Vertex tempVertex{};

		//Set the positions
		tempVertex.m_position[0] = p_mesh->mVertices[j].x;
		tempVertex.m_position[1] = p_mesh->mVertices[j].y;
		tempVertex.m_position[2] = p_mesh->mVertices[j].z;

		//Set the textures coordinates

		if (p_mesh->mTextureCoords[0] != nullptr) {
			aiVector3D* textureVec = &p_mesh->mTextureCoords[0][j];
			//printf("tex (%f,%f,%f)", textureVec->x, textureVec->y, textureVec->z );
			tempVertex.m_textCoords[0] = textureVec->x;
			tempVertex.m_textCoords[1] = textureVec->y;
		}

		if (p_mesh->HasTangentsAndBitangents())
		{
			tempVertex.m_tangents[0] = p_mesh->mTangents[j].x;
			tempVertex.m_tangents[1] = p_mesh->mTangents[j].y;
			tempVertex.m_tangents[2] = p_mesh->mTangents[j].z;

			tempVertex.m_biTangents[0] = p_mesh->mBitangents[j].x;
			tempVertex.m_biTangents[1] = p_mesh->mBitangents[j].y;
			tempVertex.m_biTangents[2] = p_mesh->mBitangents[j].z;
		}

		//Set the normals
		tempVertex.m_normals[0] = p_mesh->mNormals[j].x;
		tempVertex.m_normals[1] = p_mesh->mNormals[j].y;
		tempVertex.m_normals[2] = p_mesh->mNormals[j].z;

		//Add the vertex to the vertices vector
		m_vertices.push_back(tempVertex);
	}

	//Iterate over the faces of the mesh
	for (unsigned int j = 0; j < p_mesh->mNumFaces; ++j)
	{
		//Get the face
		const auto face = p_mesh->mFaces[j];
		//Add the indices of the face to the vector
		for (unsigned int k = 0; k < face.mNumIndices; ++k)
		{
			m_indices.push_back(face.mIndices[k] + m_offset);
		}
	}

	m_offset += static_cast<unsigned int>(m_vertices.size());
}

Rasterizer::Resources::Mesh* Rasterizer::Resources::Loaders::MeshLoader::Load(const std::string& p_modelPath)
{
	m_offset = 0;
	m_indices.clear();
	m_vertices.clear();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(p_modelPath.c_str(),
		aiProcess_CalcTangentSpace |
		aiProcess_GenNormals |
		//aiProcess_JoinIdenticalVertices |
		//aiProcess_ImproveCacheLocality |
		//aiProcess_LimitBoneWeights |
		aiProcess_RemoveRedundantMaterials |
		//aiProcess_SplitLargeMeshes |
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		//aiProcess_SortByPType |
		//aiProcess_FindDegenerates |
		//aiProcess_FindInvalidData |
		aiProcess_OptimizeMeshes |
		//aiProcess_OptimizeGraph |
		aiProcess_PreTransformVertices |
		0);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::Importer::ReadFile(): " << importer.GetErrorString() << std::endl;
		return new Mesh{ std::move(m_vertices), std::move(m_indices) };
	}

	//Iterate over the meshes
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];
		ProcessMesh(mesh);
	}
	return new Mesh{ std::move(m_vertices), std::move(m_indices) };
}

bool Rasterizer::Resources::Loaders::MeshLoader::Destroy(Mesh*& p_meshInstanceReference) noexcept
{
	if (p_meshInstanceReference != nullptr)
	{
		delete p_meshInstanceReference;
		p_meshInstanceReference = nullptr;

		return true;
	}
	return false;
}
