#include<iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <unordered_map>

#include "heapify.h"

namespace heapify {

using namespace std;
void printVecInt(const vector<int>& heap) {
    for(auto i : heap) {
        cout << i << " ";
    }
}

void printVecTuple(const vector<tuple<int, int>>& heap) {
    for(auto [k, v] : heap) {
        cout << k << ":" << v << ", ";
    }
}

void popPrintInt(vector<int>& heap) {

    cout << "pop: " << heap.back();
    cout << '\n';

    heap.pop_back();

    printVecInt(heap);
    cout << '\n';
}

void popPrintTuple(vector<tuple<int,int>>& heap) {
    
    auto [k, v] = heap.back();
    cout << "pop: " << k << ":" << v;
    cout << '\n';

    heap.pop_back();

    printVecTuple(heap);
    cout << '\n';
}

void heapVectorInts() {
    vector<int> heap{3,2,5,6,9,8,10};

    make_heap(heap.begin(), heap.end(), std::greater<>());

    printVecInt(heap);
    cout << '\n';

    popPrintInt(heap);
    popPrintInt(heap);
    popPrintInt(heap);
}

void heapVectorTuple() {
    vector<int> values{4,4,4,2,2,7,7,7,7,5,5,5,5,5,5,5};

    unordered_map<int, int> map;
    for(auto v : values) {
        map[v] += 1;
    }

    vector<tuple<int,int>> heap;
    for(auto [k, v] : map) {
        heap.emplace_back(k, v);
    }

    make_heap(heap.begin(), heap.end(), [](auto a, auto b){
        return get<0>(a) > get<0>(b);
    });

    printVecTuple(heap);
    cout << '\n';

    popPrintTuple(heap);
    popPrintTuple(heap);
}

}
