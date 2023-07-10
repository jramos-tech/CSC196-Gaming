#include <iostream>
#include <Core/Core.h>
#include <Render/Renderer.h>
#include <Input/InputSystem.h>
#include <vector>
using namespace std;

class Star {
public:
	Star(const V::Vector2& pos,const V::Vector2& vel):
		m_pos{pos},
		m_vel {vel}
	{}
	void update(int width, int height) {
		m_pos += m_vel;
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}
	void Draw(R::Render& render) {
		render.drawPoint(m_pos.x, m_pos.y);
	}

public:
	V::Vector2 m_pos;
	V::Vector2 m_vel;
};


int main(int argc, char* argv[]) {
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

	R::seedRandom((unsigned int)time(nullptr));
	
	R::Render render;
	render.initialize();
	render.createWindow("CSC196", 800, 600);

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {

		V::Vector2 pos(V::Vector2(R::random(render.GetWidth()), R::random(render.GetHeight())));
		V::Vector2 vel(R::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	while (1) {
		render.setColor(0, 0, 0, 0);
		render.beginFrame();
		//draw
		V::Vector2 vel(1.0f, 0.3f);
		for (auto& star : stars){
			star.update(render.GetWidth(), render.GetHeight());
			if (star.m_pos.x >= render.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= render.GetHeight()) star.m_pos.y = 0;
			render.setColor(R::random(256), R::random(256), R::random(256), 255);
			star.Draw(render);
		}
	//	for (int i = 0; i < 10000; i++){
	//		V::Vector2 pos(R::random(render.GetWidth()), R::random(render.GetHeight()));
	//		render.setColor(R::random(256), R::random(256), R::random(256), 255);
	//		render.drawPoint(pos.x, pos.y);
	//		//render.drawLine(R::random(render.GetWidth()), R::random(render.GetHeight()), R::random(render.GetWidth()), R::random(render.GetHeight()));
	//}
		render.endFrame();
	}
	I::InputSystem inputSystem;
	inputSystem.Initialize();
	bool quit = false;
	while (!quit)
	{
		inputSystem.Update();
		if (inputSystem.GetKeyDown())
		{
			quit = true;
		}
	return 0;
}
