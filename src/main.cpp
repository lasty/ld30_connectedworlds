
//// Just wrapper around main game class

#include "game.h"

#include "utils.h"

#include <string>


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


int main()
{

	AddPath(".");
	AddPath("data");
	AddPath("../data");

	GameApp thegame;

	thegame.Run();
}

#endif //TESTS
