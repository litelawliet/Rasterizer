#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System/Vector2.hpp>

namespace Rasterizer::LowRenderer
{
	class Camera final
	{
	public:
		explicit Camera(const glm::vec3& p_position = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3& p_up = glm::vec3(0.0f, 1.0f, 0.0f)) noexcept;
		glm::mat4 GetViewMatrix() noexcept;
		glm::mat4 GetProjectionMatrix() const noexcept;

		void MoveLeft(const float p_dt);
		void MoveRight(const float p_dt);
		void MoveForward(const float p_dt);
		void MoveBackward(const float p_dt);
		void MoveUp(const float p_dt);
		void MoveDown(const float p_dt);

		void LookAround(const float p_dt, const sf::Vector2i& p_mousePosition);

		void SetMovementSpeed(const float p_movementSpeed);
		void SetSensitivitySpeed(const float p_sensitivitySpeed);
		void SetWidthAspectRatio(const unsigned int p_width);
		void SetHeightAspectRatio(const unsigned int p_height);

		static std::unique_ptr<Camera>& GetInstance();
		float GetMovementSpeed() const;
		glm::vec3& GetPos() { return m_position; }
		glm::vec3& GetRight() { return m_rightAxis; }
		glm::vec3& GetUp() { return m_upAxis; }
		glm::vec3& GetForward() { return m_forward; }
		glm::vec3& GetTarget() { return m_target; }
		glm::vec3& GetBack() { return m_back; }
		float GetYaw() const { return m_yaw; }
		float GetPitch() const { return m_pitch; }

		void SetPos(const glm::vec3& p_vec) { m_position = p_vec; }

	private:
		glm::vec3 m_position;
		glm::vec3 m_rightAxis{};
		glm::vec3 m_upAxis{};
		glm::vec3 m_forward;
		glm::vec3 m_target;
		glm::vec3 m_back{};
		float m_movementSpeed;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
		float m_lastXPos = 0.0f;
		float m_lastYPos = 0.0f;
		float m_lookSensitivity;

		unsigned int m_width;
		unsigned int m_height;

		void UpdateCameraVector() noexcept;
		static std::unique_ptr<Camera> m_instance;
	};
}
