#include <iostream>
#include <Core/Core.h>
#include <Render/Renderer.h>
#include <Input/InputSystem.h>
#include <Render/ModelManager.h>
#include <Audio/AudioSystem.h>
#include <Framework/Actor.h>
#include <Framework/Scene.h>
#include <GamerModeActivated/Weapon.h>
#include <GamerModeActivated/Player.h>
#include <GamerModeActivated/Enemy.h>
#include <Render/Font.h>
#include <Render/Text.h>
#include "SpaceWars.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include <vector>
#include <thread>
#include <memory>
using namespace std;

class Star {
public:
	Star(const V::vec2& pos,const V::vec2& vel):
		m_pos{pos},
		m_vel {vel}
	{}
	void update(int width, int height) {
		m_pos += m_vel * kiko::g_time.getDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}
	void Draw(Sc::Render& render) {
		render.drawPoint(m_pos.x, m_pos.y);
	}

public:
	V::vec2 m_pos;
	V::vec2 m_vel;
};

int main(int argc, char* argv[]) {
	kiko::MemoryTracker::Initialize();
	std::unique_ptr<int> up = std::make_unique<int>(10);

	/*int* p = new int;
	delete p;*/
	
	//constexpr float a = MaUt::DegreesToRadians(180.0f);

	//vector<V::vec2> points{{-10, 5 }, { 10, 5 }, { 0, -5 }, { -10,5 }};

	/*V::vec2 v{5, 5};
	v.Normalize();*/
	/*M::g_memoryTracker.DisplayInfo();
	int* p = new int;
	M::g_memoryTracker.DisplayInfo();
	delete p;
	M::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++){}
	cout << timer.GetElapsedSeconds() << endl;*/

	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {}
		auto end = std::chrono::high_resolution_clock::now();

		cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
	*/
	/*cout << F::getFilePath() << endl;
	F::setFilePath("Assets");
	cout << F::getFilePath() << endl;
	size_t size;
	F::getFileSize("game.txt", size);
	cout << size << endl;

	std::string s;
	F::readFile("game.txt", s);
	cout << s << endl;

	R::seedRandom((unsigned int)time(nullptr));
	for(int i = 0; i < 30; i++)
	cout << R::random(20, 30) << endl;*/

	//int m = MaUt::Max(4.0f, 3.0f);

	R::seedRandom((unsigned int)time(nullptr));
	F::setFilePath("assets");

	Sc::g_render.initialize();
	Sc::g_render.createWindow("CSC196", 800, 600);
	I::g_inputSystem.Initialize();
	Audi::g_audioSystem.Initialize();
	unique_ptr<SpaceWars> game = make_unique<SpaceWars>();
	game->Init();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {

		V::Vector2 pos(V::Vector2(R::random(Sc::g_render.GetWidth()), R::random(Sc::g_render.GetHeight())));
		V::Vector2 vel(R::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}
	/*T::Transform transform{ {400, 300}, 0, 3 };
	V::vec2 position(400, 300);
	float speed = 200;
	constexpr float turnRate = MaUt::DegreesToRadians(180);*/

		bool quit = false;
		while (!quit)
		{

			//update engine
			kiko::g_time.Tick();
			I::g_inputSystem.Update();
			Audi::g_audioSystem.Update();

			if (I::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			//update game
			game->Update(kiko::g_time.getDeltaTime());
			Sc::g_particleSystem.Update(kiko::g_time.getDeltaTime());
			

			/*V::vec2 direction;
			if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
			if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
			if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
			if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

			position += direction * speed * kiko::g_time.getDeltaTime();*/

			//draw game
			Sc::g_render.setColor(0, 0, 0, 0);
			Sc::g_render.beginFrame();
			game->Draw(Sc::g_render);
			//draw
			V::Vector2 vel(1.0f, 0.3f);
			for (auto& star : stars) {
				star.update(Sc::g_render.GetWidth(), Sc::g_render.GetHeight());
				if (star.m_pos.x >= Sc::g_render.GetWidth()) star.m_pos.x = 0;
				if (star.m_pos.y >= Sc::g_render.GetHeight()) star.m_pos.y = 0;
				Sc::g_render.setColor(R::random(256), R::random(256), R::random(256), R::random(256));
				star.Draw(Sc::g_render);
			}
			//	for (int i = 0; i < 10000; i++){
			//		V::Vector2 pos(R::random(render.GetWidth()), R::random(render.GetHeight()));
			//		render.setColor(R::random(256), R::random(256), R::random(256), 255);
			//		render.drawPoint(pos.x, pos.y);
			//		//render.drawLine(R::random(render.GetWidth()), R::random(render.GetHeight()), R::random(render.GetWidth()), R::random(render.GetHeight()));
			//}
			game->Draw(Sc::g_render);
			Sc::g_particleSystem.Draw(Sc::g_render);
			Sc::g_render.endFrame();
			
			//this_thread::sleep_for(chrono::milliseconds(100));
		}
		stars.clear();
		kiko::MemoryTracker::DisplayInfo();
		
	return 0;
}
