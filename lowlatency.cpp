#include <assert.h>
#include <iostream>

#include "lowlatency.h"

// int gcd(int a, int b) {
//     if(b == 0) return a;
//     return gcd(b, a%b);
// }


void runGCD() {
    // std::cout << 15%5 << '\n';
    // std::cout << gcd(5,15);
    // std::cout << gcd(21,31);
    // std::cout << gcd(6,21);

    static_assert(gcd<5, 15>::value == 5);
    static_assert(gcd<21, 31>::value == 1);
    static_assert(gcd<6, 21>::value == 3);

    // Compile error, check in cppinsights.com
    // static_assert(gcd<5, 15>::value == 15);
}

class Emp {};

void runRank() {

    static_assert(Rank<int>::value == 0);

    static_assert(Rank<float[3]>::value == 1);
    static_assert(Rank<char*[3][4]>::value == 2);

    constexpr int x{};
    static_assert(Rank<decltype(x)>::value == 0);

    constexpr int mat[][2] = {
        {1, 2},
        {3, 4}
    };

    static_assert(Rank<decltype(mat)>::value == 2);

    static_assert(Rank<Emp[2][3][4][5]>::value == 4);
}
