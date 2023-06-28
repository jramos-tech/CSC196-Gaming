#include "Core/Random.h"
#include "Core/FileI0.h"
#include <iostream>
using namespace std;


int main() {

	cout << F::getFilePath() << endl;

	R::seedRandom((unsigned int)time(nullptr));
	for(int i = 0; i < 30; i++)
	cout << R::random(20, 30) << endl;
}
