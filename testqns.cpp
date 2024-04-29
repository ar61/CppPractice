#include "testqns.h"
#include <iostream>
#include <stack>
#include <unordered_map>

namespace testqns {

Node* DFS(int v, Node* cur) {
    if(cur == nullptr) {
        return new Node(0);
    }
    if(cur->val == v) {
        return cur;
    }

    Node* next;
    if(v < cur->val) {
        next = DFS(v, cur->left);
    } else {
        next = DFS(v, cur->right);
    }
    return next;
}

Node* Node::find(int v) {
    return DFS(v, this);
}

void Solution::callBSTFind() {
    Node* head = new Node(9);
    Node* seven = new Node(7);
    Node* eight = new Node(8);
    Node* eleven = new Node(11);
    Node* six = new Node(6);
    Node* five = new Node(5);
    Node* four = new Node(4);
    Node* twelve = new Node(12);

    head->left = seven;
    head->right = eleven;

    seven->left = six;
    seven->right = eight;

    six->left = four;
    six->right = five;
    
    eleven->right = twelve;

    Node* n = head->find(8);
    std::cout << "Find 8 on 9: " << n->val << "\n";
    
    n = head->find(9);
    std::cout << "Find 9 on 9: "  << n->val << "\n";
    
    n = six->find(9);
    std::cout << "Find 9 on 6: " << n->val << "\n";

    n = head->find(12);
    std::cout << "Find 12 on 9: " << n->val << "\n";
    
    n = head->find(4);
    std::cout << "Find 4 on 9: " << n->val << "\n";
}

bool Solution::balanceBrackets(std::string s) {
    
    int i = 0;
    std::stack<char> st;

    while(i < s.size()) {
        if(s[i] == '(' || s[i] == '[') {
            st.push(s[i]);
        } else {
            if(st.empty()) {
                return false;
            }
            if(st.top() == '[' && s[i] == ']') {
                st.pop();
            } else if(st.top() == '(' && s[i] == ')') {
                st.pop();
            } else {
                return false;
            }
        }
        ++i;
    }

    return st.empty() ? true : false;
}

void callBalanceBrackets() {
    std::cout << "[]() => " << Solution::balanceBrackets("[]()") << '\n';
    std::cout << "[]([()]) => " << Solution::balanceBrackets("[]([()])") << '\n';
    std::cout << "[]()( => " << Solution::balanceBrackets("[]()(") << '\n';
    std::cout << "[]()] => " << Solution::balanceBrackets("[]()]") << '\n';
    std::cout << "[]([[[[[](((())))]]]])) => " << Solution::balanceBrackets("[]([[[[[](((())))]]]])") << '\n';
}

int Solution::danceSteps(int n) {

    std::unordered_map<int, int> stepsTaken;

    if(n <= 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    if(n == 2) {
        return -2;
    }
    
    stepsTaken[0] = 0;
    stepsTaken[1] = 1;
    stepsTaken[2] = -2;

    int curPos = stepsTaken[0] + stepsTaken[1] + stepsTaken[2];
    for(int i = 3; i <= n; ++i) {
        stepsTaken[i] = stepsTaken[i - 1] - stepsTaken[i - 2];
        curPos += stepsTaken[i];
    }
    return curPos;
}

void callDanceSteps() {
    int i = 0;
    for(i = 0; i <= 20; ++i) {
        std::cout << i << " => " << Solution::danceSteps(i) << '\n';
    }
    
    std::cout << 1000 << " => " << Solution::danceSteps(1000) << '\n';
}

int Solution::findLargestNum(std::vector<int> nums) {
    int largest = nums[0];

    for(int i = 1; i < nums.size(); ++i) {
        if(nums[i] > largest) {
            largest = nums[i];
        }
    }
    return largest;
}

void callFindLargestSum() {
    std::vector<int> nums{0, -232, 100000, 232, 440, -100000};
    std::cout << Solution::findLargestNum(nums) << '\n';
}

}
