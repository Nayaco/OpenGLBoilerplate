#include "Random.hpp"

namespace randomx {
    
static std::random_device _rand_dev;
imap1d rand(int __length) {
    std::mt19937 _mt(_rand_dev());
    std::uniform_real_distribution<float> _gen(0.0f, 1.0f);
    imap1d _res(__length);
    for (auto i = 0; i < __length; ++i) {
        _res[i] = _gen(_mt);
    }
    return _res;
}
imap2d rand2(int __width, int __height) {
    std::mt19937 _mt(_rand_dev());
    std::uniform_real_distribution<float> _gen(0.0f, 1.0f);
    imap2d _res(__width);
    for (auto i = 0; i < __width; ++i) {
        _res[i].reserve(__height);
        for(auto j = 0; j < __height; ++j) {
            _res[i][j] = _gen(_mt);
        }
    }
    return _res;
}

}