#include "Rasterizer/Window.h"
#include "Rasterizer/LowRenderer/Camera.h"
#include <iostream>

Rasterizer::Window::Window(const unsigned int p_width, const unsigned int p_height, std::string&& p_title, const sf::Uint32& p_style, const bool p_vSyncEnable)
	: m_rasterizer{ p_width, p_height }, m_event{}, m_thread{ &Window::Render, this }, m_title{ std::move(p_title) }, m_camera{ *LowRenderer::Camera::GetInstance() }, m_style{ p_style }, m_width{ p_width }, m_height{ p_height }, m_vSyncEnable{ p_vSyncEnable }, m_shouldClose{ false }
{
	m_windowSettings.majorVersion = 4;
	m_windowSettings.minorVersion = 5;
	m_windowSettings.antialiasingLevel = 16;
	m_windowSettings.depthBits = 24;
	m_windowSettings.stencilBits = 8;

	CreateWindow();
}

Rasterizer::Window::Window(const Window& p_other)
	: m_rasterizer{ p_other.m_width, p_other.m_height }, m_event{ p_other.m_event }, m_thread{ &Window::Render, this }, m_title{ p_other.m_title }, m_windowSettings{ p_other.m_windowSettings }, m_camera{ p_other.m_camera }, m_style{ p_other.m_style }, m_width{ p_other.m_width }, m_height{ p_other.m_height }, m_vSyncEnable{ p_other.m_vSyncEnable }, m_shouldClose{ p_other.m_shouldClose }
{
	CreateWindow();
}

Rasterizer::Window& Rasterizer::Window::operator=(const Window& p_other)
{
	if (&p_other == this)
		return *this;

	m_rasterizer = p_other.m_rasterizer;
	m_title = p_other.m_title;
	m_windowSettings = p_other.m_windowSettings;
	m_camera = p_other.m_camera;
	m_style = p_other.m_style;
	m_width = p_other.m_width;
	m_height = p_other.m_height;
	m_vSyncEnable = p_other.m_vSyncEnable;
	m_shouldClose = p_other.m_shouldClose;

	CreateWindow();

	return *this;
}

Rasterizer::Window& Rasterizer::Window::operator=(Window&& p_other) noexcept
{
	if (&p_other == this)
		return *this;

	*this = p_other;

	p_other.m_window.close();

	CreateWindow();

	return *this;
}

Rasterizer::Window::Window(Window&& p_other) noexcept
	: m_rasterizer{ p_other.m_rasterizer }, m_event{ p_other.m_event }, m_thread{ &Window::Render, this }, m_title{ std::move(p_other.m_title) }, m_windowSettings{ p_other.m_windowSettings }, m_camera{ p_other.m_camera }, m_style{ p_other.m_style }, m_width{ p_other.m_width }, m_height{ p_other.m_height }, m_vSyncEnable{ p_other.m_vSyncEnable }, m_shouldClose{ p_other.m_shouldClose }
{
	CreateWindow();
}

void Rasterizer::Window::Run()
{
	m_window.setActive(false);
	m_thread.launch();

	while (m_window.isOpen())
	{
		HandleEvents();
	}
}

const std::string& Rasterizer::Window::GetTitle() const
{
	return m_title;
}

void Rasterizer::Window::Render()
{
	m_window.setActive(true);

	// TODO: Use mutex to increment the delta time
	while (!m_shouldClose)
	{
		m_window.clear();
		m_window.draw(m_rasterizer);
		m_window.display();
	}
}

void Rasterizer::Window::HandleEvents()
{
	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_shouldClose = true;
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			switch (m_event.key.code)
			{
			case sf::Keyboard::Escape:
				m_shouldClose = true;
				m_window.close();
				break;
			default:;
			}
			break;
		default:;
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition();
		m_camera.LookAround(1.0f, mousePosition);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// Left
			m_camera.MoveLeft(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// Right
			m_camera.MoveRight(1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			// Forward
			m_camera.MoveForward(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// Backward
			m_camera.MoveBackward(1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// Up
			m_camera.MoveUp(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// Down
			m_camera.MoveDown(1.0f);
		}
	}

	m_rasterizer.Update(1.0f);
	// TODO: Use mutex to increment the delta time
}

void Rasterizer::Window::CreateWindow()
{
	m_camera.SetWidthAspectRatio(m_width);
	m_camera.SetHeightAspectRatio(m_height);
	m_window.create(sf::VideoMode(m_width, m_height), m_title, m_style, m_windowSettings);
	m_window.setVerticalSyncEnabled(m_vSyncEnable);
}

unsigned int Rasterizer::Window::GetWidth() const
{
	return m_width;
}

unsigned Rasterizer::Window::GetHeight() const
{
	return m_height;
}

bool Rasterizer::Window::IsVSynEnabled() const
{
	return m_vSyncEnable;
}

sf::Uint32 Rasterizer::Window::GetStyle() const
{
	return m_style;
}
