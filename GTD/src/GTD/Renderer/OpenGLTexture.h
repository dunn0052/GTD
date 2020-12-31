#pragma once
#include "ITexture.h"

namespace GTD
{
	class OpenGLTexture2D : public ITexture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();
		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;


		virtual bool operator == (const ITexture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Path; // eventually map<path, texture>
		GLenum m_InternalFormat, m_DataFormat;
		uint32_t m_RendererID;

	};
}