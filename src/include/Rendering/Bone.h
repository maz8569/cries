#pragma once

#include <vector>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <list>
#include <string>
#include <Utils/AssimpGLMHelpers.h>

namespace GameEngine {

    struct KeyPosition
    {
        glm::vec3 position;
        float timeStamp;
    };

    struct KeyRotation
    {
        glm::quat orientation;
        float timeStamp;
    };

    struct KeyScale
    {
        glm::vec3 scale;
        float timeStamp;
    };

    class Bone
    {
    private:
        std::vector<KeyPosition> m_Positions;
        std::vector<KeyRotation> m_Rotations;
        std::vector<KeyScale> m_Scales;
        int m_NumPositions;
        int m_NumRotations;
        int m_NumScalings;

        glm::mat4 m_LocalTransform;
        std::string m_Name;
        int m_ID;

    public:

        /*reads keyframes from aiNodeAnim*/
        Bone(const std::string& name, int ID, const aiNodeAnim* channel);

        /*interpolates  b/w positions,rotations & scaling keys based on the curren time of
        the animation and prepares the local transformation matrix by combining all keys
        tranformations*/
        void Update(float animationTime);

        glm::mat4 GetLocalTransform();
        std::string GetBoneName() const { return m_Name; }
        int GetBoneID() { return m_ID; }


        /* Gets the current index on mKeyPositions to interpolate to based on
        the current animation time*/
        int GetPositionIndex(float animationTime)
        {
            for (int index = 0; index < m_NumPositions - 1; ++index)
            {
                if (animationTime < m_Positions[index + 1].timeStamp)
                    return index;
            }
            assert(0);
        }

        /* Gets the current index on mKeyRotations to interpolate to based on the
        current animation time*/
        int GetRotationIndex(float animationTime)
        {
            for (int index = 0; index < m_NumRotations - 1; ++index)
            {
                if (animationTime < m_Rotations[index + 1].timeStamp)
                    return index;
            }
            assert(0);
        }

        /* Gets the current index on mKeyScalings to interpolate to based on the
        current animation time */
        int GetScaleIndex(float animationTime)
        {
            for (int index = 0; index < m_NumScalings - 1; ++index)
            {
                if (animationTime < m_Scales[index + 1].timeStamp)
                    return index;
            }
            assert(0);
        }

    private:

        /* Gets normalized value for Lerp & Slerp*/
        float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
        {
            float scaleFactor = 0.0f;
            float midWayLength = animationTime - lastTimeStamp;
            float framesDiff = nextTimeStamp - lastTimeStamp;
            scaleFactor = midWayLength / framesDiff;
            return scaleFactor;
        }

        /*figures out which position keys to interpolate b/w and performs the interpolation
        and returns the translation matrix*/
        glm::mat4 InterpolatePosition(float animationTime)
        {
            if (1 == m_NumPositions)
                return glm::translate(glm::mat4(1.0f), m_Positions[0].position);

            int p0Index = GetPositionIndex(animationTime);
            int p1Index = p0Index + 1;
            float scaleFactor = GetScaleFactor(m_Positions[p0Index].timeStamp,
                m_Positions[p1Index].timeStamp, animationTime);
            glm::vec3 finalPosition = glm::mix(m_Positions[p0Index].position,
                m_Positions[p1Index].position, scaleFactor);
            return glm::translate(glm::mat4(1.0f), finalPosition);
        }

        /*figures out which rotations keys to interpolate b/w and performs the interpolation
        and returns the rotation matrix*/
        glm::mat4 InterpolateRotation(float animationTime)
        {
            if (1 == m_NumRotations)
            {
                auto rotation = glm::normalize(m_Rotations[0].orientation);
                return glm::toMat4(rotation);
            }

            int p0Index = GetRotationIndex(animationTime);
            int p1Index = p0Index + 1;
            float scaleFactor = GetScaleFactor(m_Rotations[p0Index].timeStamp,
                m_Rotations[p1Index].timeStamp, animationTime);
            glm::quat finalRotation = glm::slerp(m_Rotations[p0Index].orientation,
                m_Rotations[p1Index].orientation, scaleFactor);
            finalRotation = glm::normalize(finalRotation);
            return glm::toMat4(finalRotation);
        }

        /*figures out which scaling keys to interpolate b/w and performs the interpolation
        and returns the scale matrix*/
        glm::mat4 Bone::InterpolateScaling(float animationTime)
        {
            if (1 == m_NumScalings)
                return glm::scale(glm::mat4(1.0f), m_Scales[0].scale);

            int p0Index = GetScaleIndex(animationTime);
            int p1Index = p0Index + 1;
            float scaleFactor = GetScaleFactor(m_Scales[p0Index].timeStamp,
                m_Scales[p1Index].timeStamp, animationTime);
            glm::vec3 finalScale = glm::mix(m_Scales[p0Index].scale, m_Scales[p1Index].scale
                , scaleFactor);
            return glm::scale(glm::mat4(1.0f), finalScale);
        }

    };

}