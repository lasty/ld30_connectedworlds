#ifndef UTILS_H
#define UTILS_H



//// Misc util functions


#include <string>
#include <vector>

class HUD;

//// Make it easier to find files depening on the build
void AddPath(const std::string &path);
std::vector<std::string> & GetPathList();
std::string FindFile(const std::string &filename);


// Some quick random number helpers.  Could be improved (eg, seeding and not using % )

void seed_random(unsigned int seed);
void seed_random_time();


float random_float(float min, float max);
float random_int(int min, int max);

float random_rotation();

float random_velocity();
float random_rot_velocity();


void SetHUD(HUD *debughud);

void Debug_Rectangle(int x1, int y1, int w, int h);
void Debug_Circle(int x, int y, int radius);


#include <glm/vec4.hpp>
#include "gamedefs.h"

namespace sdl{ class Texture;  class Renderer; }


const glm::ivec4 & GetColour(colour col);
void SetTintColour(sdl::Texture &texture, colour col);
void SetDrawColour(sdl::Renderer &renderer, colour col);


std::string FormatMoney(int coins);


#endif // UTILS_H
