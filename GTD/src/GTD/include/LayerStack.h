#pragma once
#include "Core.h"
#include "Layer.h"

#include <vector>

namespace GTD
{
	class GTD_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:

		// IF we have a static number of layers we can make this an array with the actual layers
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_layerInster;
	};
}


