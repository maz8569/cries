#include "Scene/GComponent.h"

namespace GameEngine {
    /*
    std::string GComponent::getType()
    {
        return m_type;
    }
    void GComponent::setType(std::string newType)
    {
        m_type = newType;
    }
    */
    GComponent::GComponent(GObject* parent)
        : m_parent(parent)
    {

    }
}

