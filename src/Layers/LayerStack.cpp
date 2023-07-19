//
// Created by ianpo on 18/07/2023.
//

#include "Voxymore/Layers/LayerStack.hpp"

namespace Voxymore::Core {
    LayerStack::LayerStack() {
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer *overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer *layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.begin()+m_LayerInsertIndex+1, layer);
        if(it != m_Layers.begin()+m_LayerInsertIndex+1){
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer *overlay) {
        auto it = std::find(m_Layers.begin()+m_LayerInsertIndex+1, m_Layers.end(), overlay);
        if(it != m_Layers.end()){
            m_Layers.erase(it);
        }
    }
} // Layers