#pragma once
#include "ContextCodes.h"
#include <unordered_map>

namespace GTD
{
	enum class PRESS_TYPE
	{
		SINGLE,
		HOLD
	};

	struct Button
	{
		Button(ContextCode code, PRESS_TYPE type)
			: m_Code(code), m_Type(type)
		{
		}
	public:
		ContextCode Code() const { return m_Code; }
		PRESS_TYPE Type() const { return m_Type; }
		void SetType(PRESS_TYPE type) { m_Type = type; }
	private:
		ContextCode m_Code;
		PRESS_TYPE m_Type;
	};

	static std::unordered_map<ContextCode, Button> buttonMap =
	{
		{ContextCode::X, Button(ContextCode::X, PRESS_TYPE::SINGLE)},
		{ContextCode::B, Button(ContextCode::B, PRESS_TYPE::SINGLE)},
		{ContextCode::A, Button(ContextCode::A, PRESS_TYPE::SINGLE)},
		{ContextCode::Y, Button(ContextCode::Y, PRESS_TYPE::SINGLE)},
		{ContextCode::LB, Button(ContextCode::LB, PRESS_TYPE::SINGLE)},
		{ContextCode::RB, Button(ContextCode::RB, PRESS_TYPE::SINGLE)},
		{ContextCode::LT, Button(ContextCode::LT, PRESS_TYPE::SINGLE)},
		{ContextCode::RT, Button(ContextCode::RT, PRESS_TYPE::SINGLE)},
		{ContextCode::BACK, Button(ContextCode::BACK, PRESS_TYPE::SINGLE)},
		{ContextCode::START, Button(ContextCode::START, PRESS_TYPE::SINGLE)},
		{ContextCode::LSB, Button(ContextCode::LSB, PRESS_TYPE::SINGLE)},
		{ContextCode::RSB, Button(ContextCode::RSB, PRESS_TYPE::SINGLE)},
		{ContextCode::UP, Button(ContextCode::UP, PRESS_TYPE::SINGLE)},
		{ContextCode::RIGHT, Button(ContextCode::RIGHT, PRESS_TYPE::SINGLE)},
		{ContextCode::DOWN, Button(ContextCode::DOWN, PRESS_TYPE::SINGLE)},
		{ContextCode::LEFT, Button(ContextCode::LEFT, PRESS_TYPE::SINGLE)},
	};
}