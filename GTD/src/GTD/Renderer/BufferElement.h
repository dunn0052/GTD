#pragma once
#include <cstdint> // needed for uint32_t
#include "../include/Logger.h"

namespace GTD
{
	enum class ShaderDataType // could make this type smaller like uint8_t
	{
		None = 0,
		FLOAT, FLOAT2, FLOAT3, FLOAT4, 
		MAT3, MAT4,
		INT, INT2, INT3, INT4,
		BOOL
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT:  return 4;
		case ShaderDataType::FLOAT2: return 4 * 2;
		case ShaderDataType::FLOAT3: return 4 * 3;
		case ShaderDataType::FLOAT4: return 4 * 4;
		case ShaderDataType::MAT3:   return 4 * 3 * 3;
		case ShaderDataType::MAT4:   return 4 * 4 * 4;
		case ShaderDataType::INT:    return 4;
		case ShaderDataType::INT2:   return 4 * 2;
		case ShaderDataType::INT3:   return 4 * 3;
		case ShaderDataType::INT4:   return 4 * 4;
		case ShaderDataType::BOOL:   return 1; // 1 for bool? or 4?
		}
		GTD_ASSERT(false, "Unknown datatype");
		return 0;
	};

	struct BufferElement
	{
		std::string Name; // In theory the name is not needed, but only used to help reference variables in shaders
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		GTD_API BufferElement() : Name(""), Type(ShaderDataType::None), Offset(0), Size(0), Normalized(false) {}

		GTD_API BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{

		}

		GTD_API uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::FLOAT:  return 1;
			case ShaderDataType::FLOAT2: return 2;
			case ShaderDataType::FLOAT3: return 3;
			case ShaderDataType::FLOAT4: return 4;
			case ShaderDataType::MAT3:   return 3 * 3;
			case ShaderDataType::MAT4:   return 4 * 4;
			case ShaderDataType::INT:    return 4;
			case ShaderDataType::INT2:   return 2;
			case ShaderDataType::INT3:   return 3;
			case ShaderDataType::INT4:   return 4;
			case ShaderDataType::BOOL:   return 1;
			}

			GTD_ASSERT(false, "Unknown datatype");
			return 0;
		}
	};
}