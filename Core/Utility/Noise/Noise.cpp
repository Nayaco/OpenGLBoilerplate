#include "Noise.hpp"

namespace noise {
float lerp(float x0, float x1, float alpha) {
    // return x0 * (1 - alpha) + x1 * alpha;
    return glm::mix(x0, x1, alpha);
}

imap2d whiteNoise(int width, int height) {
    return randomx::rand2(width, height);
}

imap2d smoothNoise(
    imap2d const& white_noise, int octave, int width, int height) {
    imap2d _res(width);
    int sample_period = (int)powf32(2, octave);
    float sample_frequency = 1.0f / sample_period;
    for (auto i = 0; i < width; ++i) {
        int sample_l = (i / sample_period) * sample_period;
        int sample_r = (sample_l + sample_period) % width;
        float horizontal_blend = (i - sample_l) * sample_frequency;
        _res[i].reserve(height);
        for (auto j = 0; j < height; ++j) {
            int sample_u = (j / sample_period) * sample_period;
            int sample_d = (sample_u + sample_period) % height;
            float vertical_blend = (j - sample_u) * sample_frequency;
            float top = lerp(white_noise[sample_l][sample_u], 
                            white_noise[sample_r][sample_u], horizontal_blend);
            float bottom = lerp(white_noise[sample_l][sample_d], 
                            white_noise[sample_r][sample_d], horizontal_blend);
            _res[i][j] = lerp(top, bottom, vertical_blend);
        }
    } 
    return _res; 
}

imap2d perlNoise(imap2d const& white_noise, int octave_count, int width, int height) {
    vector<imap2d> smooth_noises {};
    imap2d perl_noise(width);
    float _persistance = 0.8f;
    for (auto i = 0; i < octave_count; ++i) {
        smooth_noises.push_back(smoothNoise(white_noise, i, width, height));
    }
    float amplitude = 1.0f;
    float total_amp = 0.0f;
    for (auto octave = octave_count - 1; octave >= 0; --octave) {
        amplitude *= _persistance;
        total_amp += amplitude;
        for (auto i = 0; i < width; ++i) {
            perl_noise[i].reserve(height);
            for (auto j = 0; j < height; ++j) {
                perl_noise[i][j] += smooth_noises[octave][i][j] * amplitude;
            }
        }
    }
    for(auto i = 0; i < width; ++i) {
        for(auto j = 0; j < height; ++j) {
            perl_noise[i][j] /= total_amp;
        }
    }
    return perl_noise;
}
}