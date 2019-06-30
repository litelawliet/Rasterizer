#include "Rasterizer/Rasterizer.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Rasterizer/Utils/UtilsTemplatedFunctions.h"
#include <iostream>

Rasterizer::Rasterizer::Rasterizer(const unsigned p_width, const unsigned p_height)
	: m_pixelArray{ nullptr }, m_scene{ *Managers::Scene::GetInstance() }, m_width{ p_width }, m_height{ p_height }
{
	m_pixelArray = new sf::Uint8[m_width * m_height * static_cast<unsigned int>(PixelFormat::RGBA)];
	m_imageFromPixelArray.create(m_width, m_height, m_pixelArray);
}

Rasterizer::Rasterizer::~Rasterizer()
{
	if (m_pixelArray != nullptr)
	{
		delete[] m_pixelArray;
	}
}

Rasterizer::Rasterizer& Rasterizer::Rasterizer::operator=(const Rasterizer& p_other)
{
	if (&p_other == this)
		return *this;

	m_pixelArray = p_other.m_pixelArray;
	m_scene = p_other.m_scene;
	m_imageFromPixelArray = p_other.m_imageFromPixelArray;
	m_textureFromImage = p_other.m_textureFromImage;
	m_spriteToRender = p_other.m_spriteToRender;
	m_width = p_other.m_width;
	m_height = p_other.m_height;

	return *this;
}

void Rasterizer::Rasterizer::draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const
{
	p_target.draw(m_spriteToRender, p_states);
}

void Rasterizer::Rasterizer::Update(const float p_dt)
{
	// TODO: Rasterization process
	// Modify the image after looping over all triangles
	// get all meshes :
	auto& entities = m_scene.GetEntities();
	for (const auto& entity : entities)
	{
		const auto& model = entity.GetModel();
		const auto& transform = entity.GetTransform();

		// Now iterate over each triangle of the model
		// use the transform for each vertex of the model and color it make the rasterization process out of it

		// Transformation 3D point to 2D
		//(transformedVertex[k].m_x / 5.0f + 1.0f) * 0.5f * m_width, m_height - (transformedVertex[k].m_y / 5.0f + 1.0f) * 0.5f * m_height , transformedVertex[k].m_z

		const auto& vertices = model.GetMesh()->GetVertices();
		const auto& indices = model.GetMesh()->GetIndices();

		// Outer loop
		for (uint32_t i = 0; i < std::floor((indices.size() - 1) / 3); i += 3)
		{
			Geometry::Vertex v0;
			Geometry::Vertex v1;
			Geometry::Vertex v2;
			try
			{
				v0 = vertices.at(indices.at(i));
				v1 = vertices.at(indices.at(i + 1));
				v2 = vertices.at(indices.at(i + 2));
			}
			catch (const std::out_of_range& e)
			{
				std::cerr << "Out of Range error: " << e.what() << "\n";
			}

			v0.m_position = glm::vec3{ transform * glm::vec4{ v0.m_position, 1.0f } };
			v1.m_position = glm::vec3{ transform * glm::vec4{ v1.m_position, 1.0f } };
			v2.m_position = glm::vec3{ transform * glm::vec4{ v2.m_position, 1.0f } };

			// Convert the vertices of the triangle to raster space
			Geometry::Vertex v0Raster = v0;
			Geometry::Vertex v1Raster = v1;
			Geometry::Vertex v2Raster = v2;

			v0Raster.m_position = glm::vec3{ (v0Raster.m_position.x / 5.0f + 1.0f) * 0.5f * static_cast<float>(m_width), static_cast<float>(m_height) - (v0Raster.m_position.y / 5.0f + 1.0f) * 0.5f * static_cast<float>(m_height) , v0Raster.m_position.z };
			v1Raster.m_position = glm::vec3{ (v1Raster.m_position.x / 5.0f + 1.0f) * 0.5f * static_cast<float>(m_width), static_cast<float>(m_height) - (v1Raster.m_position.y / 5.0f + 1.0f) * 0.5f * static_cast<float>(m_height) , v0Raster.m_position.z };
			v2Raster.m_position = glm::vec3{ (v2Raster.m_position.x / 5.0f + 1.0f) * 0.5f * static_cast<float>(m_width), static_cast<float>(m_height) - (v2Raster.m_position.y / 5.0f + 1.0f) * 0.5f * static_cast<float>(m_height) , v0Raster.m_position.z };

			// Precompute reciprocal of vertex z-coordinate
			v0Raster.m_position.z = 1 / v0Raster.m_position.z;
			v1Raster.m_position.z = 1 / v1Raster.m_position.z;
			v2Raster.m_position.z = 1 / v2Raster.m_position.z;

			// Prepare vertex attributes. Divde them by their vertex z-coordinate (though we use a multiplication here because v.z = 1 / v.z)
			glm::vec2 st0;
			glm::vec2 st1;
			glm::vec2 st2;
			try
			{
				st0 = vertices.at(indices.at(i)).m_textCoords;
				st1 = vertices.at(indices.at(i + 1)).m_textCoords;
				st2 = vertices.at(indices.at(i + 2)).m_textCoords;
			}
			catch (const std::out_of_range& e)
			{
				std::cerr << "Out of Range error: " << e.what() << "\n";
			}

			st0 *= v0Raster.m_position.z, st1 *= v1Raster.m_position.z, st2 *= v2Raster.m_position.z;

			float xMin = Min3(v0Raster.m_position.x, v1Raster.m_position.x, v2Raster.m_position.x);
			float yMin = Min3(v0Raster.m_position.y, v1Raster.m_position.y, v2Raster.m_position.y);
			float xMax = Max3(v0Raster.m_position.x, v1Raster.m_position.x, v2Raster.m_position.x);
			float yMax = Max3(v0Raster.m_position.y, v1Raster.m_position.y, v2Raster.m_position.y);

			// the triangle is out of screen
			if (xMin > static_cast<float>(m_width) - 1 || xMax < 0 || yMin > static_cast<float>(m_height) - 1 || yMax < 0) continue;

			// be careful xmin/xmax/ymin/ymax can be negative. Don't cast to uint32_t
			uint32_t x0 = std::max(int32_t(0), static_cast<int32_t>(std::floor(xMin)));
			uint32_t x1 = std::min(int32_t(m_width) - 1, static_cast<int32_t>(std::floor(xMax)));
			uint32_t y0 = std::max(int32_t(0), static_cast<int32_t>(std::floor(yMin)));
			uint32_t y1 = std::min(int32_t(m_height) - 1, static_cast<int32_t>(std::floor(yMax)));

			float area = EdgeFunction(v0Raster, v1Raster, v2Raster);
		}

		// White quad for debug purpose
		for (unsigned int i = 0; i < m_width / 4; ++i)
		{
			for (unsigned int j = 0; j < m_height / 4; ++j)
			{
				SetPixelColor(i, j, sf::Color::White);
			}
		}

		// Update the image and texture and set the new sprite to render
		m_imageFromPixelArray.create(m_width, m_height, m_pixelArray);
		m_textureFromImage.loadFromImage(m_imageFromPixelArray);
		m_spriteToRender.setTexture(m_textureFromImage);
	}
}

const sf::Sprite& Rasterizer::Rasterizer::GetSprite() const noexcept
{
	return m_spriteToRender;
}

void Rasterizer::Rasterizer::SetPixelColor(const unsigned p_x, const unsigned p_y, const sf::Color& p_color) const
{
	const unsigned int index = static_cast<unsigned int>(PixelFormat::RGBA) * (p_y * m_width + p_x);
	m_pixelArray[index] = p_color.r;
	m_pixelArray[index + 1] = p_color.g;
	m_pixelArray[index + 2] = p_color.b;
	m_pixelArray[index + 3] = p_color.a;
}

void Rasterizer::Rasterizer::SetPixelColor(const unsigned p_x, const unsigned p_y, const sf::Uint8& p_red,
	const sf::Uint8& p_green, const sf::Uint8& p_blue, const sf::Uint8& p_alpha) const
{
	const unsigned int index = static_cast<unsigned int>(PixelFormat::RGBA) * (p_y * m_width + p_x);
	m_pixelArray[index] = p_red;
	m_pixelArray[index + 1] = p_green;
	m_pixelArray[index + 2] = p_blue;
	m_pixelArray[index + 3] = p_alpha;
}

float Rasterizer::Rasterizer::EdgeFunction(const Geometry::Vertex& p_first,
	const Geometry::Vertex& p_second, const Geometry::Vertex& p_third)
{
	return (p_third.m_position[0] - p_first.m_position[0]) * (p_second.m_position[1] - p_first.m_position[1]) - (p_third.m_position[1] - p_first.m_position[1]) * (p_second.m_position[0] - p_first.m_position[0]);
}
