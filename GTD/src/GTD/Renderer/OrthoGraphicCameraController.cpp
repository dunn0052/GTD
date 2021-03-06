#include "../PCH/PCH.h"
#include "../Util/Utils.h"
#include "OrthoGraphicCameraController.h"

namespace GTD
{

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, const Ref<Timestep>& dt, bool rotation) :
		m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_DT(dt), m_Rotating(rotation)
    {

    }

	OrthographicCameraController::OrthographicCameraController(const OrthographicCameraControllerProps& props) :
		m_AspectRatio(props.aspectRatio), m_Camera(-props.aspectRatio * props.zoomLevel, props.aspectRatio * props.zoomLevel, -props.zoomLevel, props.zoomLevel), 
		m_DT(props.dt), m_Rotating(props.rotation), m_CameraRotationSpeed(props.rotationSpeed), m_CameraRotation(props.startingRotation), 
		m_CameraPosition(props.position), m_CameraTranslationSpeed(props.translationSpeed), m_ZoomLevel(props.zoomLevel)
	{
	}

    OrthographicCameraController::OrthographicCameraController() :
        m_AspectRatio(0.0), m_Rotating(false), m_DT(), m_Camera(0.0f,0.0f,0.0f,0.0f)// default constructor
    {

    } 

    void OrthographicCameraController::OnUpdate(Controllers& controllers)
    {
		for (auto& controller : controllers.GetXboxControllers())
		{
			if (controller.connected)
			{

				if (m_Rotating)
				{
					// rotation
					if (controller.m_CurrentButtons[GTD::ContextCode::LB])
					{
						m_CameraRotation += -m_CameraRotationSpeed * m_DT->GetSecond();
						m_Camera.SetRotation(m_CameraRotation);
					}
					if (controller.m_CurrentButtons[GTD::ContextCode::RB])
					{
						m_CameraRotation += m_CameraRotationSpeed * m_DT->GetSecond();
						m_Camera.SetRotation(m_CameraRotation);
					}
					m_Camera.SetRotation(m_CameraRotation);
				}

			
				if (controller.m_CurrentButtons[GTD::ContextCode::UP])
				{
					m_CameraPosition.y += m_CameraTranslationSpeed * m_DT->GetSecond();
				}

				if (controller.m_CurrentButtons[GTD::ContextCode::RIGHT])
				{
					m_CameraPosition.x += m_CameraTranslationSpeed * m_DT->GetSecond();
				}

				if (controller.m_CurrentButtons[GTD::ContextCode::DOWN])
				{
					m_CameraPosition.y -= m_CameraTranslationSpeed * m_DT->GetSecond();
				}

				if (controller.m_CurrentButtons[GTD::ContextCode::LEFT])
				{
					m_CameraPosition.x -= m_CameraTranslationSpeed * m_DT->GetSecond();
				}

				m_CameraPosition.x += controller.m_axis[GTD::ContextAxis::RX] * m_DT->GetSecond();
				m_CameraPosition.y -= controller.m_axis[GTD::ContextAxis::RY] * m_DT->GetSecond();

				m_ZoomLevel -= controller.m_axis[GTD::ContextAxis::LX] * m_CameraTranslationSpeed * m_DT->GetSecond();
				m_ZoomLevel += controller.m_axis[GTD::ContextAxis::LY] * m_CameraTranslationSpeed * m_DT->GetSecond();
			}
		}


		//m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		//m_Camera.SetPosition(m_CameraPosition);
    }

	void OrthographicCameraController::OnUpdate()
	{
		// Get keys here
		m_Camera.SetPosition(m_Following->GetQuad()->m_Rect.Center());

	}

    void OrthographicCameraController::OnEvent(Event& e)
    {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FTN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FTN(OrthographicCameraController::OnWindowResize));
    }

	void OrthographicCameraController::Follow(const Ref<PC>& ent)
	{
		m_Following = ent;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = m_ZoomLevel > 0.25f ? m_ZoomLevel : 0.25f;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		LOG_DEBUG("ZOOM LEVEL %f", m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
    {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}
