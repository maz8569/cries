#pragma once
#include <typedefs.h>
#include <array>
#include <glm/glm.hpp>

namespace GameEngine {
    
    class AABB;

    enum Planes
    {
        Near,
        Far,
        Left,
        Right,
        Top,
        Bottom,
    };

    struct FrustumAABB
    {
        FrustumAABB(const glm::vec3& dimensions, const glm::vec3& position);

        glm::vec3 GetVN(const glm::vec3& normal) const;
        glm::vec3 GetVP(const glm::vec3& normal) const;

        const glm::vec3 m_Dimensions;
        const glm::vec3 m_Position;
    };

    struct Plane
    {
        float distanceToPoint(const glm::vec3& point) const;

        float distanceToOrigin;
        glm::vec3 normal;
    };

    class ViewFrustum
    {
    public:

        static enum {OUTSIDE, INTERSECT, INSIDE};

        void Update(const glm::mat4& VP_Matrix);
        bool BoxInFrustum(Ref<AABB> box) const;

    private:
        std::array<Plane, 6> m_Planes;
    };

}