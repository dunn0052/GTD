#pragma once
#include "BufferElement.h"

namespace GTD
{
	class BufferLayout
	{
	public:
		GTD_API BufferLayout() {}

		GTD_API BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		GTD_API inline uint32_t GetStride() const { return m_Stride; }

		GTD_API inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		GTD_API std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		GTD_API std::vector<BufferElement>::iterator end() { return m_Elements.end(); }		
		GTD_API std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		GTD_API std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0; // the stride aka how many bites the m_Elements vertex contains
	};

}
