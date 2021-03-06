#include "Physics/Collisions/Collision2D.h"

namespace GameEngine {


	void Collision2D::addCollision(Ref<GuiComponent> c)
	{
		c->onCollisionEnter(m_mouseCursor);
		m_collisions.push_back(c);
	}

	void Collision2D::removeCollision(Ref<GuiComponent> c)
	{
		c->onCollisionExit(m_mouseCursor);
		
		for (i = 0; i < m_collisions.size(); i++)
		{
			if (m_collisions[i] == c)
			{
				m_collisions.erase(m_collisions.begin() + i);
				m_collisions.shrink_to_fit();
			}
		}

		/*
		if (m_collisions.size() > 1)
		{
			m_collisions.erase(std::remove(m_collisions.begin(), m_collisions.end(), c), m_collisions.end());
		}
		else
		{
		*/
		//	m_collisions.clear();
		//}
	}

	Collision2D::Collision2D(Ref<MouseCursor> mouseCursor)
		: m_mouseCursor(mouseCursor)
	{
	}

	bool Collision2D::testPointAABB(Ref<GuiComponent> c, glm::vec2 pos)
	{
		glm::vec2 scale = c->getScale();

		scale.x = abs(scale.x);
		scale.y = abs(scale.y);

		glm::vec2 min = c->getPosition() - scale;
		glm::vec2 max = c->getPosition() + scale;

		if (pos.x < max.x && pos.y < max.y && pos.x > min.x && pos.y > min.y)
		{
			return true;
		}

		return false;
	}

	void Collision2D::CollisionCheck()
	{
		if (m_collisions.size() > 0)
		{
			for (i = 0; i < m_collisions.size(); i++) {
				auto c = m_collisions[i];
				if (testPointAABB(c, m_mouseCursor->mousePos))
				{
					c->onCollisionStay(m_mouseCursor);
				}
				else
				{
					removeCollision(c);
				}

			}
		}

		if (m_2DAABB.size() > 0) {
			for (auto c : m_2DAABB) {
				if (std::count(m_collisions.begin(), m_collisions.end(), c))
				{}
				else
				{
					if (testPointAABB(c, m_mouseCursor->mousePos))
					{
						addCollision(c);
					}
				}
			}
		}

	}

	void Collision2D::addGuiComponent(Ref<GuiComponent> c)
	{
		m_2DAABB.push_back(c);
	}

}