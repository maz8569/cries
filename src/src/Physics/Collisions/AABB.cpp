#include "Physics/Collisions/AABB.h"

GameEngine::AABB::AABB(const glm::vec3& min, const glm::vec3& max): GComponent(nullptr),center((max+min)*0.5f), extents(max.x - center.x, max.y - center.y, max.z - center.z) 
{
}

GameEngine::AABB::AABB(const glm::vec3& inCenter, float iI, float iJ, float iK): GComponent(nullptr), center(inCenter), extents(iI, iJ, iK)
{
}

GameEngine::AABB::~AABB()
{
}

void GameEngine::AABB::updateCenter(glm::vec3& newLocation)
{
	center = newLocation;
}

void GameEngine::AABB::updateExtents(glm::vec3& newExtents)
{
	extents = newExtents;
}

glm::vec3 GameEngine::AABB::getVN(const glm::vec3& normal) const
{
	glm::vec3 res = center;

	if (normal.x < 0) {
		res.x += extents.x;
	}
	if (normal.y < 0) {
		res.y += extents.y;
	}
	if (normal.z < 0) {
		res.z += extents.z;
	}

	return res;
}

glm::vec3 GameEngine::AABB::getVP(const glm::vec3& normal) const
{
	glm::vec3 res = center;

	if (normal.x > 0) {
		res.x += extents.x;
	}
	if (normal.y > 0) {
		res.y += extents.y;
	}
	if (normal.z > 0) {
		res.z += extents.z;
	}

	return res;
}

void GameEngine::AABB::setStatic(bool st)
{
	staticAABB = st;
}

std::array<glm::vec3, 8> GameEngine::AABB::getVertice() const
{
	std::array<glm::vec3, 8> vertice;
	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	return vertice;
}

glm::vec3 GameEngine::AABB::getMax()
{
	glm::vec3 result;

	for (int i = 0; i < 3; i++)
	{
		result[i] = center[i] + extents[i];
	}

	return result;
}

glm::vec3 GameEngine::AABB::getMin()
{
	glm::vec3 result;

	for (int i = 0; i < 3; i++)
	{
		result[i] = center[i] - extents[i];
	}

	return result;
}

void GameEngine::AABB::setXExtent(float x)
{
	extents.x = x;
}

void GameEngine::AABB::setYExtent(float y)
{
	extents.y = y;
}

void GameEngine::AABB::setZExtent(float z)
{
	extents.z = z;
}

void GameEngine::AABB::setExtents(glm::vec3 newExtents)
{
	extents = newExtents;
}

void GameEngine::AABB::scaleAABB(glm::vec3 scale)
{
	for (int i = 0; i < 3; i++)
	{
		extents[i] *= scale[i];
	}
}

void GameEngine::AABB::rotateAABBX()
{
	float ext = extents.y;
	extents.y = extents.z;
	extents.z = ext;
}

void GameEngine::AABB::rotateAABBY()
{
	float ext = extents.x;
	extents.x = extents.z;
	extents.z = ext;
}

void GameEngine::AABB::rotateAABBZ()
{
	float ext = extents.x;
	extents.x = extents.y;
	extents.y = ext;
}

glm::vec3 GameEngine::AABB::testDepth(Ref<AABB> other)
{
	glm::vec3 result = glm::vec3();

	for (int i = 0; i < 3; i++)
	{
		if (center[i] < other->center[i])
		{
			result[i] = extents[i] + other->extents[i] + center[i] - other->center[i] - 0.001;
			//result[i] = extents[i] + other->extents[i] + center[i] - other->center[i];

		}
		else
		{
			result[i] = -(extents[i] + other->extents[i] - center[i] + other->center[i] - 0.001);
			//result[i] = -(extents[i] + other->extents[i] - center[i] + other->center[i]);
		}
	}
	return result;
}

float GameEngine::AABB::getSmallestDistance(Ref<AABB> other)
{
	auto vec = testDepth(other);
	float result = vec[0] > vec[1] ? vec[1] : vec[0];
	return result;
}

bool GameEngine::AABB::collides(Ref<AABB> other) const
{
	for (int i = 0; i < 3; i++)
	{
		if (abs(center[i] - other->center[i]) > (extents[i] + other->extents[i]))
			return 0;
	}
	return 1;
}

bool GameEngine::AABB::pointVsAABB(glm::vec3 point)
{
	auto max = getMax();
	auto min = getMin();
	for (int i = 0; i < 3; i++)
	{
		if (!(point[i] >= min[i] && point[i] <= max[i]))
			return 0;
	}
	return 1;
}


GameEngine::AABB GameEngine::generateAABB(std::shared_ptr<Model> model)
{
	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
	for (auto&& mesh : model->meshes)
	{
		for (auto&& vertex : mesh.vertices)
		{
			minAABB.x = std::min(minAABB.x, vertex.Position.x);
			minAABB.y = std::min(minAABB.y, vertex.Position.y);
			minAABB.z = std::min(minAABB.z, vertex.Position.z);

			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
		}
	}
	return AABB(minAABB, maxAABB);
}
