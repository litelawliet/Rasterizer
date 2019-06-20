#include "Rasterizer/Rasterizer.h"
#include <SFML/Graphics/RenderTarget.hpp>

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
	auto & entities = m_scene.GetEntities();
	for (const auto & entity : entities)
	{
		const auto & model = entity.GetModel();
		const auto & transform = entity.GetTransform();

		// Now iterate over each triangle of the model
		// use the transform for each vertex of the model and color it make the rasterization process out of it
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
