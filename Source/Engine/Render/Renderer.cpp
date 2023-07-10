#include "Renderer.h"
namespace R{
	bool Render::initialize(){
		SDL_Init(SDL_INIT_VIDEO);
		return true;
	}
	void Render::shutdown(){

	}
	void Render::createWindow(const std::string& title, int width, int height){
		m_width = width;
		m_height = height;
		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
	void Render::beginFrame(){
		SDL_RenderClear(m_renderer);
	}
	void Render::endFrame(){
		SDL_RenderPresent(m_renderer);
	}
	void Render::setColor(int r, int g, int b, int a){
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}
	void Render::drawLine(int x1, int y1, int x2, int y2){
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}
	void Render::drawLine(float x1, float y1, float x2, float y2){
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}
	void Render::drawPoint(int x, int y){
		SDL_RenderDrawPoint(m_renderer, x, y);
	}
	void Render::drawPoint(float x, float y){
		SDL_RenderDrawPointF(m_renderer, x, y);
	}
}