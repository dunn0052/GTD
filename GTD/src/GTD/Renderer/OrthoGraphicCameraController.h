#pragma once

#include "OrthographicCamera.h"
#include "../include/Timestep.h"
#include "../Events/AppEvent.h"
#include "../Events/MouseEvent.h"
#include "../include/Controllers.h"
#include "../Game/PC.h"

namespace GTD
{
	struct OrthographicCameraControllerProps
	{
		float aspectRatio;
		Ref<Timestep> dt;
		bool rotation;
		float startingRotation;
		float rotationSpeed;
		glm::vec3 position;
		float translationSpeed;
		float zoomLevel;
	};

	class OrthographicCameraController
	{
public:
	GTD_API OrthographicCameraController(float aspectRation, const Ref<Timestep>& dt, bool rotation = false); // zoom level 1.0, aspectratio * 2 units
	GTD_API OrthographicCameraController(const OrthographicCameraControllerProps& props);
	GTD_API OrthographicCameraController();

	GTD_API void OnUpdate(Controllers& controllers);
	GTD_API void OnUpdate();
	GTD_API void OnEvent(Event& e);
	GTD_API OrthographicCamera& GetCamera() { return m_Camera; }
	GTD_API const OrthographicCamera& GetCamera() const { return m_Camera; }

	GTD_API void SetCameraPosition(const glm::vec3& position) { m_Camera.SetPosition(position); }

	GTD_API const float GetZoomLevel() const { return m_ZoomLevel; }

	GTD_API void Follow(const Ref<PC>& ent);

private:

	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

private:
	Ref<Timestep> m_DT;

	float m_AspectRatio;
	float m_ZoomLevel = 1.0f;
	OrthographicCamera m_Camera;

	float m_LowerZoomBound = 0;
	float m_UpperZoomBound = 100;

	bool m_Rotating;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;
	float m_CameraTranslationSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;

	Ref<PC> m_Following;

	float m_PanSpeed = 10.0f;
	float m_PanAcceleration = 2.0f;

	};
}