#include "Noise.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"
namespace noise {

// [[0.003765   0.015019   0.02379159 0.015019   0.003765  ]
//  [0.015019   0.05991246 0.0949073  0.05991246 0.015019  ]
//  [0.02379159 0.0949073  0.15034262 0.0949073  0.02379159]
//  [0.015019   0.05991246 0.0949073  0.05991246 0.015019  ]
//  [0.003765   0.015019   0.02379159 0.015019   0.003765  ]]

float lerp(float x0, float x1, float alpha) {
    return glm::mix(x0, x1, alpha);
}

imap2d getFile(std::string const filename) {
    imap2d res;
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        imap1d vec;
        switch (nrChannels) {
            case 1: {format = GL_RED; break;}
            case 3: {format = GL_RGB; break;}
            case 4: {format = GL_RGBA; break;}
            default: throw "Noise: unknow color space";
        }
        
        if (format == GL_RED) {
            for (auto i = 0; i < width; i++) {
                vec.clear();
                for (auto j = 0; j < height; j++) {
                    vec.push_back((float)data[i * height + j] / 255.0);
                }
                res.push_back(vec);
            }
        } else if (format == GL_RGB) {
            for (auto i = 0; i < width; i++) {
                vec.clear();
                for (auto j = 0; j < height; j++) {
                    vec.push_back((float)data[i * height * 3 + j * 3] / 255.0);
                }
                res.push_back(vec);
            }
        } else if (format == GL_RGBA) {
            for (auto i = 0; i < width; i++) {
                vec.clear();
                for (auto j = 0; j < height; j++) {
                    vec.push_back((float)data[i * height * 4 + j * 4] / 255.0);
                }
                res.push_back(vec);
            }
        }
        seaLevelize(res);
        stbi_image_free(data);
    }
    else {
        stbi_image_free(data);
        throw "Noise: file "+ filename + " not exists";
    }
    return res;
}

void seaLevelize(imap2d &imap) {
    float minH = 1.0f;
    for (auto i = 0; i < imap.size(); ++i) {
        for (auto j = 0; j < imap[0].size(); ++j) {
            minH = imap[i][j] < minH ? imap[i][j] : minH; 
        }        
    } 
    for (auto i = 0; i < imap.size(); ++i) {
        for (auto j = 0; j < imap[0].size(); ++j) {
            imap[i][j] -= minH; 
        }
    }
}

imap2d whiteNoise(int width, int height) {
    return randomx::rand2(width, height);
}

imap1d smoothNoise1d(
    imap1d const& white_noise, int octave, int length) {
    imap1d _res(length);
    int sample_period = (int)powf(2, octave);
    float sample_frequency = 1.0f / sample_period;
    for (auto i = 0; i < length; ++i) {
        int sample_l = (i / sample_period) * sample_period;
        int sample_r = (sample_l + sample_period) % length;
        float horizontal_blend = (i - sample_l) * sample_frequency;
        _res[i] = lerp(white_noise[sample_l], white_noise[sample_r], horizontal_blend);
    } 
    return _res; 
}

imap1d perlNoise1d(imap1d const& white_noise, int octave_count, int length) {
    vector<imap1d> smooth_noises {};
    imap1d perl_noise(length);
    float _persistance = 0.8f;
    for (auto i = 0; i < octave_count; ++i) {
        smooth_noises.push_back(smoothNoise1d(white_noise, i, length));
    }
    float amplitude = 1.0f;
    float total_amp = 0.0f;
    float total_mag = 0.0f;
    
    for (auto octave = octave_count - 1; octave >= 0; --octave) {
        amplitude *= _persistance;
        total_amp += amplitude;
        for (auto i = 0; i < length; ++i) {
            if (octave == octave_count - 1) perl_noise.push_back(0.0f);
            perl_noise[i] += smooth_noises[octave][i] * amplitude;
        }
    }
    
    for (auto i = 0; i < length; ++i) {
        perl_noise[i] /= total_amp;
    }

    return perl_noise;
}

imap2d smoothNoise(
    imap2d const& white_noise, int octave, int width, int height) {
    imap2d _res(width);
    int sample_period = (int)powf(2, octave);
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
            _res[i].push_back(lerp(top, bottom, vertical_blend));
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
                if (octave == octave_count - 1) perl_noise[i].push_back(0.0f);
                perl_noise[i][j] += smooth_noises[octave][i][j] * amplitude;
            }
        }
    }
    
    for (auto i = 0; i < width; ++i) {
        for(auto j = 0; j < height; ++j) {
            perl_noise[i][j] /= total_amp;
        }
    }
    seaLevelize(perl_noise);

    return perl_noise;
}
}