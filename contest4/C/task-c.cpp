#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::string str_s;
    std::string str_p;
    std::cin >> str_s;
    std::cin >> str_p;
    std::vector<char> p(str_p.size());
    std::vector<char> s(str_s.size() + str_p.size() + 1);
    for (uint i = 0; i < str_p.size(); ++i) {
        s[i] = str_p[i];
        p[i] = str_p[i];
    }
    s[str_p.size()] = '#';
    for (uint i = 0; i < str_s.size(); ++i) {
        s[i + str_p.size() + 1] = str_s[i];
    }
    std::vector<int> prefix(s.size(), 0);
    for (uint i = 1; i < s.size(); ++i) {
        int k = prefix[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = prefix[k - 1];
        }
        if (s[i] == s[k]) {
            prefix[i] = k + 1;
        } else {
            prefix[i] = k;
        }
    }
    for (uint i = p.size(); i < prefix.size(); ++i) {
        if (prefix[i] == p.size()) {
            std::cout << i - p.size() * 2 << "\n";
        }
    }
}
