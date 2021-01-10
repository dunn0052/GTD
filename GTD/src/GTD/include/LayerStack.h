#pragma once
#include "Core.h"
#include "Layer.h"

#include <vector>

namespace GTD
{
	class LayerStack
	{
	public:
		GTD_API LayerStack();
		GTD_API ~LayerStack();

		GTD_API void PushLayer(Layer* layer);
		GTD_API void PushOverlay(Layer* overlay);
		GTD_API void PopLayer(Layer* layer);
		GTD_API void PopOverlay(Layer* layer);

		GTD_API std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		GTD_API std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:

		// IF we have a static number of layers we can make this an array with the actual layers instead of pointers 
		// (maybe too much memory on the stack though..)
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
		unsigned int m_LayerInsertIndex = 0;
	};
}


