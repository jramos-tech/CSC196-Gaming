#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>
namespace Sc
{
	class Text
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		void Create(Render& renderer, const std::string& text, const Color& color);
		void Draw(Render& renderer, int x, int y);
	private:
		std::shared_ptr<Font> m_font = nullptr;
		struct SDL_Texture* m_texture = nullptr;
	};
}
