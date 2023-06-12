#include <iostream>
#include <algorithm>
#include <stack>

int main() {
    long n;
    long max = 0;
    std::stack <long> stolbiks;
    std::stack <long> coordinate;
    std::cin >> n;
    stolbiks.push(0);
    coordinate.push(0);
    long f = 0;
    for (int i = 1; i < n+1; ++i) {
        long h;
        std::cin >> h;
        if (h == 0) {
            long x = coordinate.top();
            while (coordinate.top() != f) {
                coordinate.pop();
                long pretend = stolbiks.top() *(x - coordinate.top());
                stolbiks.pop();
                if (pretend > max) {
                    max = pretend;
                }
            }
            coordinate.pop();
            coordinate.push(i);
            f = i;
        }
        else {
            if (h > stolbiks.top()) {
                stolbiks.push(h);
                coordinate.push(i);
            }
            else {
                while (stolbiks.top() >= h) {
                    coordinate.pop();
                    long pretend = (stolbiks.top()*(i - coordinate.top() - 1));
                    stolbiks.pop();
                    if (pretend > max) {
                        max = pretend;
                    }
                    if (stolbiks.empty()) {
                        break;
                    }
                }
                stolbiks.push(h);
                coordinate.push(i);
            }
        }

    }

    long x = coordinate.top();
    while (coordinate.top() != f) {
        coordinate.pop();
        long pretend = stolbiks.top() *(x - coordinate.top());
        stolbiks.pop();
        if (pretend > max) {
            max = pretend;
        }
    }
    std::cout << max;
}