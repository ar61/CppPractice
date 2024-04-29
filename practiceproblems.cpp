
#include "practiceproblems.h"

namespace practiceproblems {

using namespace std;
int lengthOfLIS(vector<int>& nums) {
    int len = nums.size() - 1;
    vector<int> LIS(len, 1);

    for(int i = len; i >= 0; --i) {
        for(int j = i + 1; j <= len; ++j) {
            if(nums[i] < nums[j]) {
                LIS[i] = max(LIS[i], 1 + LIS[j]);
            }
        }
    }
    return *max_element(LIS.begin(), LIS.end());
}


bool searchIsland(int r, int c, unordered_set<string>& visited, 
                    vector<vector<char>>& grid) {

    bool rowInBound = (r >=0 && r < grid.size());
    bool colInBound = (c >=0 && c < grid[0].size());

    if(!rowInBound || !colInBound || grid[r][c] == '0') {
        return false;
    }
    string key = to_string(r) + "," + to_string(c);
    if(visited.count(key) > 0) {
        return false;
    }
    visited.insert(key);
    searchIsland(r-1, c, visited, grid);
    searchIsland(r, c-1, visited, grid);
    searchIsland(r+1, c, visited, grid);
    searchIsland(r, c+1, visited, grid);
    return true;
}

// vector<vector<char>> grid = {
//                             {'1','1','0','0','0'},
//                             {'1','1','0','0','0'},
//                             {'0','0','1','0','0'},
//                             {'0','0','0','1','1'}
//                             };
//cout << numIslands(grid) << '\n';
int numIslands(vector<vector<char>>& grid) {
    unordered_set<string> visited;
    int res = 0;
    for(int r = 0; r < grid.size(); ++r) {
        for(int c = 0; c < grid[0].size(); ++c) {
            if(searchIsland(r, c, visited, grid)) {
                ++res;
            }
        }
    }
    return res;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    vector<vector<int>> res;
    for(int i = 0; i < nums.size(); ++i) {
        
        if(i > 0 && nums[i - 1] == nums[i]) {
            continue;
        }

        int start = i + 1;
        int end = nums.size() - 1;
        
        while(start < end) {
            int sum = nums[i] + nums[start] + nums[end];
            if(sum > 0) {
                --end;
            } else if(sum < 0) {
                ++start;
            } else {
                res.push_back({nums[i], nums[start], nums[end]});
                ++start;
                while(nums[start] == nums[start-1] && start < end) {
                    ++start;
                }
            }
        }
    }
    return res;
}
}
