
// run with g++ *.cpp -std=c++2a; ./a.out
// for debug build: g++ main.cpp -std=c++2a -g -O0
#include <iostream>
//#include <vector>
//#include <string> // <====  std::getline exists here!
#include "stdimpl.h"

int main(int argc, const char * argv[]) {
    stdimpl::uniqueptrTests();
    stdimpl::sharedptrTests();

    return 0;
}

/*

*/
