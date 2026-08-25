#ifndef GAME_TIME_LIB_HPP
#define GAME_TIME_LIB_HPP

#include <cstdint>
#include <chrono>

namespace GameTime {
    inline uint64_t getNanoS()
    {
        auto tse = std::chrono::steady_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();
    }
}

#endif