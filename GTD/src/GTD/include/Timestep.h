#pragma once
#include "Core.h"

namespace GTD
{
	class GTD_API Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSecond() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; };
		void Set(float time) { m_Time = time; }

	private:
		float m_Time;
	};
}