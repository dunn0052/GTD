#include "../PCH/PCH.h"
#include "../Util/Utils.h"
#include "OrthoGraphicCameraController.h"

namespace GTD
{

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) :
		m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotating(rotation)
    {

    }

    OrthographicCameraController::OrthographicCameraController() :
        m_AspectRatio(0.0), m_Rotating(false), m_Camera(0.0f,0.0f,0.0f,0.0f)// default constructor
    {

    } 

    void OrthographicCameraController::OnUpdate(Timestep& dt, Controllers& controllers)
    {
		for (auto& controller : controllers.GetXboxControllers())
		{
			if (controller.connected)
			{

				if (m_Rotating)
				{
					// rotation
					if (controller.m_buttons[GTD::ContextCode::LB])
					{
						m_CameraRotation += -m_CameraRotationSpeed * dt;
						m_Camera.SetRotation(m_CameraRotation);
					}
					if (controller.m_buttons[GTD::ContextCode::RB])
					{
						m_CameraRotation += m_CameraRotationSpeed * dt;
						m_Camera.SetRotation(m_CameraRotation);
					}
					m_Camera.SetRotation(m_CameraRotation);
				}

			
				if (controller.m_buttons[GTD::ContextCode::UP])
				{
					m_CameraPosition.y += 10 * dt;
				}

				if (controller.m_buttons[GTD::ContextCode::RIGHT])
				{
					m_CameraPosition.x += 10 * dt;
				}
				m_CameraPosition.x += controller.m_axis[GTD::ContextAxis::RX];
				m_CameraPosition.y -= controller.m_axis[GTD::ContextAxis::RY];

				m_ZoomLevel -= controller.m_axis[GTD::ContextAxis::LX] * 0.01;
				m_ZoomLevel += controller.m_axis[GTD::ContextAxis::LY] * 0.01;
			}
		}


		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		m_Camera.SetPosition(m_CameraPosition);
    }

	void OrthographicCameraController::OnUpdate(Timestep& dt)
	{
		// Get keys here
	}

    void OrthographicCameraController::OnEvent(Event& e)
    {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FTN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FTN(OrthographicCameraController::OnWindowResize));
    }

	void OrthographicCameraController::CalculateView()
	{
		// TODO calculate view
		//m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		//m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottome, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
		m_ZoomLevel = Clamp<float>(m_ZoomLevel - e.GetYOffset(), m_LowerZoomBound, m_UpperZoomBound);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		//CalculateView();
        return false;
    }

    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
    {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		//CalculateView();
        return false;
    }
}
