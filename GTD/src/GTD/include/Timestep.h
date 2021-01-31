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

		float GetTime() { return 0.0f; } // glfwGetTime() instead of 0.0f, but should be platform independent

		// Operators
		friend bool operator<(const Timestep& l, const Timestep& r)
		{
			return l.m_Time < r.m_Time;
		}	
	
		friend bool operator>(const Timestep& l, const Timestep& r)
		{
			return l.m_Time > r.m_Time;
		}
	
		friend bool operator<=(const Timestep& l, const Timestep& r)
		{
			return l.m_Time <= r.m_Time;
		}
	
		friend bool operator>=(const Timestep& l, const Timestep& r)
		{
			return l.m_Time >= r.m_Time;
		}

		friend bool operator==(const Timestep& l, const Timestep& r)
		{
			return l.m_Time == r.m_Time;
		}

		friend void operator+=(Timestep& l, Timestep& r)
		{
			l.m_Time += r.m_Time;
		}

	private:
		float m_Time;
	};
}