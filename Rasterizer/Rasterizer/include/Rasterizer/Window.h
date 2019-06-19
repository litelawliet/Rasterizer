#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Thread.hpp>
#include "Rasterizer.h"

namespace Rasterizer
{
	class Window final
	{
	public:
		explicit Window(const unsigned int p_width = 800u, const unsigned int p_height = 600u, std::string && p_title = "DefaultTitle", const sf::Uint32 & p_style = 7u, const bool p_vSyncEnable = true);
		Window(const Window& p_other);
		Window(Window&& p_other) noexcept;
		Window& operator=(const Window& p_other);
		Window& operator=(Window&& p_other) noexcept;
		~Window() = default;

		void Run();

		const std::string& GetTitle() const;
		sf::Uint32 GetStyle() const;
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		bool IsVSynEnabled() const;

	private:
		void Render();
		void HandleEvents();

		void CreateWindow();

		sf::RenderWindow m_window;
		Rasterizer m_rasterizer;
		sf::Event m_event;
		sf::Thread m_thread;
		std::string m_title;
		sf::ContextSettings m_windowSettings;

		sf::Uint32 m_style;
		unsigned int m_width;
		unsigned int m_height;
		bool m_vSyncEnable;

		bool m_shouldClose;
	};
}
