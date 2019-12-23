#include "Noise.hpp"

namespace noise {

// [[0.003765   0.015019   0.02379159 0.015019   0.003765  ]
//  [0.015019   0.05991246 0.0949073  0.05991246 0.015019  ]
//  [0.02379159 0.0949073  0.15034262 0.0949073  0.02379159]
//  [0.015019   0.05991246 0.0949073  0.05991246 0.015019  ]
//  [0.003765   0.015019   0.02379159 0.015019   0.003765  ]]

// imap2d blur(imap2d const& origin, imap2d const& kernel) {
//     imap2d _res = origin;
//     for (auto i = 0; i < origin.size(); i++) {
//         for(auto j = 0; j < origin[0].size(); j++) {
//             _res = 
//             for(auto ii = 0; ii < kernel.size(); ii++) {
//                 for(auto jj = 0; jj < kernel[0].size(); jj++) {
                    
//                 }
//             }
//         }
//     }
// }
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
    float total_mag = 0.0f;
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
    // for (auto i = 0; i < width; ++i) {
    //     for (auto j = 0; j < height; ++j) {
    //         total_mag += perl_noise[i][j];
    //     }
    // }
    // total_mag /= width * height;
    // // imap1d edge_w(width);
    // // imap1d edge_h(height);
    // // for (auto i = 1; i < width - 1; ++i) {
    // //     edge_w[i] = (perl_noise[i][0] + perl_noise[i - 1][0] + perl_noise[i + 1][0]);
    // // }
    // for (auto i = 0; i < width - 1; ++i) {
    //     perl_noise[i][0] = total_mag;//edge_w[i] / 3.0f;
    //     // edge_w[i] = (perl_noise[i][height - 1] + perl_noise[i - 1][height - 1] + perl_noise[i + 1][height - 1]);
    // }
    // for (auto i = 0; i < width - 1; ++i) {
    //     perl_noise[i][height - 1] = total_mag;//edge_w[i] / 3.0f;
    // }

    // // for (auto i = 1; i < height - 1; ++i) {
    // //     edge_h[i] = (perl_noise[0][i] + perl_noise[0][i - 1] + perl_noise[0][i + 1]);
    // // }
    // for (auto i = 0; i < height - 1; ++i) {
    //     perl_noise[0][i] = total_mag;//edge_h[i] / 3.0f;
    //     // edge_h[i] = (perl_noise[width - 1][i] + perl_noise[width - 1][i - 1] + perl_noise[width - 1][i + 1]);
    // }
    // for (auto i = 0; i < height - 1; ++i) {
    //     perl_noise[width - 1][i] = total_mag;//edge_h[i] / 3.0f;
    // }
    
    for (auto i = 0; i < width; ++i) {
        for(auto j = 0; j < height; ++j) {
            perl_noise[i][j] /= total_amp;
        }
    }
    return perl_noise;
}
}