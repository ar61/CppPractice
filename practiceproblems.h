
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

namespace practiceproblems {

int lengthOfLIS(std::vector<int>& nums);

bool searchIsland(int r, int c, std::unordered_set<string>& visited, 
                    std::vector<std::vector<char>>& grid);

int numIslands(std::vector<std::vector<char>>& grid);

std::vector<std::vector<int>> threeSum(std::vector<int>& nums);

}