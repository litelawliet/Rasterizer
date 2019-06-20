#include "Rasterizer/LowRenderer/Camera.h"

std::unique_ptr<Rasterizer::LowRenderer::Camera> Rasterizer::LowRenderer::Camera::m_instance;

Rasterizer::LowRenderer::Camera::Camera(const glm::vec3& p_position, const glm::vec3& p_up) noexcept
	: m_position{ glm::vec3(0.0f, 0.0f, 3.0f) },
	m_rightAxis{ glm::vec3{1.0f, 0.0f, 0.0f } },
	m_upAxis{ glm::vec3{0.0f, 1.0f, 0.0f} },
	m_forward{ glm::vec3(0.0f, 0.0f, -1.0f) },
	m_target{ glm::vec3(0.0f, 0.0f, 0.0f) },
	m_movementSpeed{ 1.0f },
	m_lookSensitivity{ 1.0f },
	m_width{ 0 },
	m_height{ 0 }
{
	UpdateCameraVector();
}

void Rasterizer::LowRenderer::Camera::UpdateCameraVector() noexcept
{
	//m_back      = normalize(m_position - m_target);
	m_forward = -m_back;
	m_rightAxis = normalize(cross(m_upAxis, m_back));
	//m_upAxis    = normalize(cross(m_back, m_rightAxis));
}

glm::mat4 Rasterizer::LowRenderer::Camera::GetViewMatrix() noexcept
{
	UpdateCameraVector();
	return lookAt(m_position, m_position - m_back, m_upAxis);
}

glm::mat4 Rasterizer::LowRenderer::Camera::GetProjectionMatrix() const noexcept
{
	return glm::perspective(glm::radians(60.0f), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, 100.0f);;
}

void Rasterizer::LowRenderer::Camera::MoveLeft(const float p_dt)
{
	m_position -= glm::normalize(cross(m_forward, m_upAxis)) * m_movementSpeed * p_dt;
}

void Rasterizer::LowRenderer::Camera::MoveRight(const float p_dt)
{
	m_position += normalize(cross(m_forward, m_upAxis)) * m_movementSpeed * p_dt;
}

void Rasterizer::LowRenderer::Camera::MoveForward(const float p_dt)
{
	m_position += m_movementSpeed * m_forward * p_dt;
}

void Rasterizer::LowRenderer::Camera::MoveBackward(const float p_dt)
{
	m_position -= m_movementSpeed * m_forward * p_dt;
}

void Rasterizer::LowRenderer::Camera::MoveUp(const float p_dt)
{
	m_position += m_movementSpeed * m_upAxis * p_dt;
}

void Rasterizer::LowRenderer::Camera::MoveDown(const float p_dt)
{
	m_position -= m_movementSpeed * m_upAxis * p_dt;
}

void Rasterizer::LowRenderer::Camera::LookAround(const float p_dt, const sf::Vector2i& p_mousePosition)
{
	glm::vec3 front;
	float xOffset = p_mousePosition.x - m_lastXPos;
	float yOffset = p_mousePosition.y - m_lastYPos; // reversed since y-coordinates range from bottom to top
	m_lastXPos = static_cast<float>(p_mousePosition.x);
	m_lastYPos = static_cast<float>(p_mousePosition.y);

	xOffset *= m_lookSensitivity * p_dt;
	yOffset *= m_lookSensitivity * p_dt;

	m_yaw += xOffset;
	m_pitch += yOffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	front.y = sin(glm::radians(m_pitch));
	front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	m_back = normalize(front);
}

void Rasterizer::LowRenderer::Camera::SetMovementSpeed(const float p_movementSpeed)
{
	m_movementSpeed = p_movementSpeed;
}

void Rasterizer::LowRenderer::Camera::SetSensitivitySpeed(const float p_sensitivitySpeed)
{
	m_lookSensitivity = p_sensitivitySpeed;
}

void Rasterizer::LowRenderer::Camera::SetWidthAspectRatio(const unsigned int p_width)
{
	m_width = p_width;
}

void Rasterizer::LowRenderer::Camera::SetHeightAspectRatio(const unsigned int p_height)
{
	m_height = p_height;
}


std::unique_ptr<Rasterizer::LowRenderer::Camera>& Rasterizer::LowRenderer::Camera::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::make_unique<Camera>();
	}

	return m_instance;
}

float Rasterizer::LowRenderer::Camera::GetMovementSpeed() const { return m_movementSpeed; }