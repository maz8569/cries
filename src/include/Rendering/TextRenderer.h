#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <ft2build.h>
#include "typedefs.h"
#include <map>
#include <Shaders/Shader.h>
#include <Scene/Camera.h>
#include <GUI/GuiComponent.h>
#include FT_FREETYPE_H

namespace GameEngine {
	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	class TextRenderer
	{
	public:
		std::map<char, Character> Characters;
		Ref<Shader> GUIShader = nullptr;
		Ref<Camera> m_camera;
		unsigned int GUI_VBO, GUI_VAO;
		FT_Library ft;
		FT_Face face;
		int m_size = 48;
		bool success = false;

		TextRenderer(Ref<Camera> camera, std::string fontPath,const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		~TextRenderer();
		void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
		void setSize(int size);
		void clean();
	};
}
