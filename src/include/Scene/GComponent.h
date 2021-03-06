#pragma once

#include <typedefs.h>

namespace GameEngine {

	class GObject;

	struct GComponent
	{

		GObject* parent;
		unsigned int ID;

		GComponent(GObject* obj = nullptr);

		virtual void setParent(GObject* newParent);
		
		virtual void Update(float dt);

		virtual void OnCollisionEnter(GObject* other);
		virtual void OnCollisionStay(GObject* other);
		virtual void OnCollisionExit(GObject* other);

	};

}