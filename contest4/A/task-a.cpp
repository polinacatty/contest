#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class Hashmap {
private:
    size_t capacity_ = 10000;
    std::vector<std::list<double>> data_;

public:
    Hashmap() : data_(capacity_, std::list<double>()) {}
    bool Exists(const double& key) {
        int new_hash = std::hash<double>{}(key) % capacity_;
        for (std::list<double>::iterator it = data_[new_hash].begin();
             it != data_[new_hash].end(); ++it) {
            if (*it == key) {
                return true;
            }
        }
        return false;
    }
    void Insert(const double& key) {
        if (Exists(key)) {
            return;
        }
        int new_hash = std::hash<double>{}(key) % capacity_;
        data_[new_hash].push_back(key);
    }
    void Erase(const double& key) {
        if (!Exists(key)) {
            return;
        }
        int new_hash = std::hash<double>{}(key) % capacity_;
        for (std::list<double>::iterator it = data_[new_hash].begin();
             it != data_[new_hash].end(); ++it) {
            if (*it == key) {
                data_[new_hash].erase(it);
                return;
            }
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> b(n);
    std::string a;
    double val;
    Hashmap hash;
    for (int i = 0; i < n; ++i) {
        std::cin >> a >> val;
        if (a == "+") {
            hash.Insert(val);
        } else if (a == "-") {
            hash.Erase(val);
        } else {
            if (hash.Exists(val)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }
}
