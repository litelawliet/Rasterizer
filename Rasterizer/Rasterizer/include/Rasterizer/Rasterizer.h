#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Rasterizer/Managers/Scene.h"

namespace Rasterizer
{
	enum class PixelFormat
	{
		RGB = 3,
		RGBA = 4
	};

	class Rasterizer final : public sf::Drawable
	{
	public:
		Rasterizer(const unsigned int p_width, const unsigned int p_height);
		~Rasterizer();
		Rasterizer& operator=(const Rasterizer& p_other);

		void draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const override;

		void Update(const float p_dt);

		const sf::Sprite& GetSprite() const noexcept;

	private:
		void SetPixelColor(const unsigned int p_x, const unsigned int p_y, const sf::Color& p_color) const;
		void SetPixelColor(const unsigned int p_x, const unsigned int p_y, const sf::Uint8& p_red, const sf::Uint8& p_green, const sf::Uint8& p_blue, const sf::Uint8& p_alpha = 255) const;

		sf::Uint8* m_pixelArray;
		Managers::Scene& m_scene;
		sf::Sprite m_spriteToRender;
		sf::Texture m_textureFromImage;
		sf::Image m_imageFromPixelArray; // Each pixel behave as RGBA internally

		unsigned int m_width;
		unsigned int m_height;
	};
}
