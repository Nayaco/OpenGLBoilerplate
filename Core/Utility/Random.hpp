#ifndef RANDOM_HPP
#define RANDOM_HPP
#include "Core/Common.hpp"
#include <random>

namespace randomx {

float random(float lower_bound, float upper_bound);
imap1d rand(int __length);
imap2d rand2(int __width, int __height);

} 
#endif