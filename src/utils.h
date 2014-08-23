#ifndef UTILS_H
#define UTILS_H



//// Misc util functions


#include <string>
#include <vector>


//// Make it easier to find files depening on the build
void AddPath(const std::string &path);
std::vector<std::string> & GetPathList();
std::string FindFile(const std::string &filename);


// Some quick random number helpers.  Could be improved (eg, seeding and not using % )

void seed_random();


float random_float(float min, float max);
float random_int(int min, int max);

float random_rotation();

float random_velocity();
float random_rot_velocity();



#endif // UTILS_H
