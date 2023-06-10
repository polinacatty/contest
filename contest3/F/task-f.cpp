#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int Compute(std::vector<std::vector<int>>& segtree, int index, int l, int r) {
    if (segtree[index][1] >= l && segtree[index][2] <= r) {
        return segtree[index][0];
    }
    if (segtree[index][2] < l || segtree[index][1] > r) {
        return 0;
    }
    int v = Compute(segtree, index * 2 + 1, l, r);
    int b = Compute(segtree, index * 2 + 2, l, r);
    return v + b;
}

void Change(std::vector<std::vector<int>>& segtree, int index, int delta) {
    segtree[index][0] += delta;
    if (index == 0) {
        return;
    }
    Change(segtree, (index - 1) / 2, delta);
}

int main() {
    int n;
    std::cin >> n;
    int l = log2(n - 1);
    l = pow(2, l + 1);
    std::vector<int> reactions(n);
    int z = 2 * l - 1;
    int c = 3;
    std::vector<int> row(c, 0);
    std::vector<std::vector<int>> segtree(z, row);
    for (int i = 0; i < n; ++i) {
        int y;
        std::cin >> y;
        reactions[i] = y * (2 * ((i + 1) % 2) - 1);
    }
    for (int i = l - 1; i < 2 * l - 1; ++i) {
        if (i < l - 1 + n) {
            segtree[i][0] = reactions[i + 1 - l];
        }
        segtree[i][1] = i + 1 - l;
        segtree[i][2] = i + 1 - l;
    }
    for (int i = l - 2; i >= 0; --i) {
        segtree[i][0] = segtree[2 * i + 1][0] + segtree[2 * i + 2][0];
        segtree[i][1] = segtree[2 * i + 1][1];
        segtree[i][2] = segtree[2 * i + 2][2];
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        if (a == 1) {
            if (b % 2 == 1) {
                std::cout << Compute(segtree, 0, b - 1, c - 1) << "\n";
            } else {
                std::cout << -Compute(segtree, 0, b - 1, c - 1) << "\n";
            }
        } else if (a == 0) {
            if (b % 2 == 0) {
                c = -c - segtree[b + l - 2][0];
            } else {
                c = c - segtree[b + l - 2][0];
            }
            Change(segtree, b + l - 2, c);
        }
    }
}
