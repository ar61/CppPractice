
#include <vector>
#include <string>

namespace testqns {

struct Node
{
    int val;
    Node* left;
    Node* right;

    Node(int v): val(v), left(nullptr), right(nullptr) {}

    Node* find(int v);
};

class Solution {
public:

static void callBSTFind();

static bool balanceBrackets(std::string input);

static int danceSteps(int n);

static int findLargestNum(std::vector<int> n);

};

void callBalanceBrackets();

void callDanceSteps();

void callFindLargestSum();

// do sparseVector problem

}
