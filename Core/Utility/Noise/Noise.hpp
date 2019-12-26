#ifndef NOISE_HPP
#define NOISE_HPP
#include "Core/Common.hpp"
#include "Core/Utility/Random.hpp"
#include "Core/ResourceManager/ResourceManager.hpp"

namespace noise {

float lerp(float x0, float x1, float alpha);

imap2d getFile(std::string const filename);

void seaLevelize(imap2d &map);
imap2d whiteNoise(int width, int height);
imap2d smoothNoise(imap2d const& white_noise, int octave, int width, int height);
imap2d perlNoise(imap2d const& white_noise, int octave_count, int width, int height);
imap1d smoothNoise1d(imap1d const& white_noise, int octave, int length);
imap1d perlNoise1d(imap1d const& white_noise, int octave_count, int length);

}

#endif