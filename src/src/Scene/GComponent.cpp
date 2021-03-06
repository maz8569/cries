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
    GComponent::GComponent(GObject* obj)
        : parent(obj)
    {

    }
    void GComponent::setParent(GObject* newParent)
    {
        parent = newParent;
    }
    void GComponent::Update(float dt)
    {
    }
    void GComponent::OnCollisionEnter(GObject* other)
    {
    }
    void GComponent::OnCollisionStay(GObject* other)
    {
    }
    void GComponent::OnCollisionExit(GObject* other)
    {
    }
}

