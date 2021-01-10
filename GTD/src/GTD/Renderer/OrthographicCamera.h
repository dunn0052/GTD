#pragma once

#include "../include/Core.h"
#include "../../Vendor/glm/glm.hpp"

namespace GTD
{
	class OrthographicCamera
	{
	public:
		GTD_API OrthographicCamera(float left, float right, float bottom, float top);

		GTD_API void SetProjection(float left, float right, float bottom, float top);

		GTD_API const glm::vec3& GetPosition() const { return m_Position; }
		GTD_API void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		GTD_API void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		GTD_API const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		GTD_API const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		GTD_API const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:

		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix; //inverse of transformation matrix
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}