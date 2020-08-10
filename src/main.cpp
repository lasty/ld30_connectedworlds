
//// Just wrapper around main game class

#include "game.h"

#include "utils.h"

#include <string>

#include "sdl/headers.h"

//#define TESTS

#ifdef TESTS

#include <iostream>
#include "utils.h"
#include <map>

namespace tests
{

using std::cout;
using std::cerr;
using std::endl;

void TestRand()
{
	for(int i=0; i<30; i++)
	{
		int r = random_int(0, 10);
		cout << r << " ";
	}
	cout << endl;
}

void TestRand2()
{
	std::map<int, int> hist;

	for(int i=0; i<10000; i++)
	{
		int r = random_int(0, 10);
		hist[r]++;
	}

	for(auto &item : hist)
	{
		cout << "["<<item.first<<"] : " //<< item.second
		<< std::string((item.second/10), '*' )
		<< "\n";
	}
	cout << endl;
}


void DoTests()
{
	seed_random();
	TestRand();
	TestRand2();
}

} //namespace tests

int main()
{
	tests::DoTests();
}

#else

#include <stdexcept>

int main()
{
	seed_random_time();

	AddPath(".");

	AddPath("data");


	//For MACOSX, gets  Resource directory inside app bundle
	char* base_cstr = SDL_GetBasePath();
	std::string base{base_cstr};
	SDL_free(base_cstr);

	AddPath(base+"data");


	//For build tree (saves having to install every single time)
	AddPath(base+"../../../data");
	AddPath("../data");
	AddPath("../../data");


	GameApp thegame;

	thegame.Run();
}

#endif //TESTS
