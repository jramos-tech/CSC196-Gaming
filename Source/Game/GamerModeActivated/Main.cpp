#include "Core/Random.h"
#include "Core/FileI0.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include <iostream>
#include <Render/Renderer.h>
using namespace std;


int main() {
	M::g_memoryTracker.DisplayInfo();
	int* p = new int;
	M::g_memoryTracker.DisplayInfo();
	delete p;
	M::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++){}
	cout << timer.GetElapsedSeconds() << endl;

	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {}
		auto end = std::chrono::high_resolution_clock::now();

		cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;*/
	

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
}
