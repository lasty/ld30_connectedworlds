
#include "utils.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

#include <glm/gtx/random.hpp>

namespace {

std::vector<std::string> the_path_list;

};

std::vector<std::string> & GetPathList()
{
	return the_path_list;
}

void AddPath(const std::string &path)
{
	GetPathList().push_back(path);
}


//// try to locate a file by prepending all values in search path
std::string FindFile(const std::string &filename)
{
	for(auto &path : GetPathList())
	{
		std::string fullfilename = path + "/" + filename;
		try
		{
			std::ifstream in(fullfilename);

			if(in) return fullfilename;
		}
		catch (std::exception &e)
		{

		}
	}
	throw std::runtime_error("Could not find file '"+filename+"'");
}


////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
void seed_random() { srand(time(nullptr)); }

float random_float(float min, float max){ return glm::linearRand(min, max); }
float random_int(int min, int max) { return (glm::linearRand<float>(min, max+1)); }

float random_rotation() { return random_float(0.0f, 360.0f); }

float random_velocity() { return random_float(0.0f, 10.0f); }
float random_rot_velocity() { return random_float(-20.0f, 20.0f); }

