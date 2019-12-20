#ifndef COMMON_HPP
#define COMMON_HPP
// OpenGL staff
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// Standard libraries
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cassert>
// Streams 
#include <sstream>
#include <fstream>
#include <iostream>
// System 
#include <sys/stat.h>
// Standard containers
#include <memory>
#include <vector>
#include <tuple>
#include <map>
#include <unordered_map>
#include <list>
#include <string>

using std::string;
using std::map;
using std::unordered_map;
using std::list;
using std::vector;
using std::shared_ptr;
using std::tuple;
using std::pair;
using std::ifstream;
using strstream = std::stringstream;
using std::chrono::system_clock;
using std::to_string;

using indice_vector = vector<unsigned int>;


#endif