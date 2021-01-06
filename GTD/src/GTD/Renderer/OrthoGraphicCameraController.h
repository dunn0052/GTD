#pragma once

#include "OrthographicCamera.h"
#include "../include/Timestep.h"
#include "../Events/AppEvent.h"
#include "../Events/MouseEvent.h"
#include "../include/Controllers.h"

namespace GTD
{
	struct GTD_API OrthographicCameraControllerProps
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

	class GTD_API OrthographicCameraController
	{
public:
	OrthographicCameraController(float aspectRation, const Ref<Timestep>& dt, bool rotation = false); // zoom level 1.0, aspectratio * 2 units
	OrthographicCameraController(const OrthographicCameraControllerProps& props);
	OrthographicCameraController();

	void OnUpdate(Controllers& controllers);
	void OnUpdate();
	void OnEvent(Event& e);
	OrthographicCamera& GetCamera() { return m_Camera; }
	const OrthographicCamera& GetCamera() const { return m_Camera; }

private:
	void CalculateView();

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
	float m_CameraTranslationSpeed = 1.0f;
	float m_CameraRotationSpeed = 180.0f;


	};
}