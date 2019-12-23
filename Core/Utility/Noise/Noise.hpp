#ifndef NOISE_HPP
#define NOISE_HPP
#include "Core/Common.hpp"
#include "Core/Utility/Random.hpp"
namespace noise {

float lerp(float x0, float x1, float alpha);
// float blur(imap2d const& white_noise, imap2d const& white_noise);


imap2d whiteNoise(int width, int height);
imap2d smoothNoise(imap2d const& white_noise, int octave, int width, int height);
imap2d perlNoise(imap2d const& white_noise, int octave_count, int width, int height);

}

#endif