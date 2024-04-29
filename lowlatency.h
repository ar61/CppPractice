#include <cstddef>

namespace lowlatency {

template <int a, int b>
struct gcd {
    inline static constexpr int value = gcd<b, a%b>::value;
};

template <int a>
struct gcd<a, 0> {
    inline static constexpr int value = a;
};

void runGCD();

template <typename T>
struct Rank {
    inline static constexpr size_t value = 0;
};

template <typename T>
struct Rank<T[]> {
    inline static constexpr size_t value = 1u + Rank<T>::value;
};

template <typename T, size_t N>
struct Rank<T[N]> {
    inline static constexpr size_t value = 1u + Rank<T>::value;
};

void runRank();
}
