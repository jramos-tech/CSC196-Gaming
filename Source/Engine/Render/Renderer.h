#pragma once
#include <SDL2-2.28.0/include/SDL.h>
#include <string>
namespace R{

	class Render {
	public:
		Render() = default;
		~Render() = default;

		bool initialize();
		void shutdown();
		void createWindow(const std::string& title, int width, int height);
		void beginFrame();
		void endFrame();
		void setColor(int r, int g, int b, int a);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(int x, int y);
		void drawPoint(float x, float y);

		int GetWidth() const {return m_width;}
		int GetHeight() const {return m_height;}

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
	};
}