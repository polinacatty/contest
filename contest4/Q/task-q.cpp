#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <map>
#include <queue>

class Graph {

public:
    struct triple {
        int64_t first = 0;
        int64_t second = 0;
        int64_t third = 0;

        triple(int64_t f = 0, int64_t s = 0, int64_t t = 0) : first(f), second(s), third(t) {}

    };

    std::vector<std::vector<triple>> conn;
    size_t v_count;
    size_t e_count;
    std::vector<int64_t> dist;
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<>> dist_heap;
    std::vector<bool> used;
    std::vector<triple> span_tree;
    int64_t span_tree_weight = 0;
    std::vector<size_t> parent;
public:
    explicit Graph(size_t ver_count = 0) {
        e_count = 0;
        v_count = ver_count;

        conn = std::vector<std::vector<triple>>(v_count + 1);
        dist = std::vector<int64_t>(v_count + 1, -1);
        used = std::vector<bool>(v_count + 1);
        parent = std::vector<size_t>(v_count + 1);

    }

    void add_edge(size_t first, size_t second, bool oriented = false, size_t weight = 0) {
        ++e_count;
        size_t ord = e_count;
        if (oriented) {
            conn[first].emplace_back(second, weight, ord);
        } else {
            conn[first].emplace_back(second, weight, ord);
            conn[second].emplace_back(first, weight, ord);
        }
    }

    void add_edges(size_t ed_count, bool oriented = false) {
        for (size_t i = 1; i < ed_count + 1; ++i) {
            size_t first, second;
            int64_t w;
            std::cin >> first >> second >> w;
            add_edge(first, second, oriented, w);
        }
    }

    void add_edges_with_matrix(bool oriented = false) {
        for (size_t i = 0; i < v_count + 1; ++i) {
            for (size_t j = 0; j < v_count + 1; ++j) {
                if (i * j == 0) continue;
                int64_t x;
                std::cin >> x;
                if (i < j && !oriented)
                    continue;
                if (x != -1 && i != j) add_edge(i, j, oriented, x);
            }
        }
    }

    size_t min_dist() {
        if (dist_heap.empty()) return 0;
        auto m = dist_heap.top();
        dist_heap.pop();
        if (m.first == -1) return 0;
        return m.second;
    }

    void prim(size_t S) {
        dist[S] = 0;
        dist_heap.emplace(0, S);

        while (!dist_heap.empty()) {
            size_t ver = min_dist();

            if (!used[ver] && ver != S) {
                span_tree.emplace_back(parent[ver], ver, dist[ver]);
                span_tree_weight += dist[ver];
            }
            used[ver] = true;

            for (auto to : conn[ver]) {
                if (used[to.first]) continue;
                if (dist[to.first] == -1) {
                    dist[to.first] = to.second;
                    dist_heap.emplace(dist[to.first], to.first);
                    parent[to.first] = ver;
                } else if (to.second < dist[to.first]) {
                    dist[to.first] = to.second;
                    dist_heap.emplace(dist[to.first], to.first);
                    parent[to.first] = ver;
                }
            }
        }
    }
};

void print(const size_t& x) {
    std::cout << x << "\n";
}

void print(const std::deque<size_t>& vec) {
    for (auto x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    size_t v_count, e_count;
    std::cin >> v_count >> e_count;
    Graph g(v_count);
    g.add_edges(e_count, false);
    int64_t ans = 0;
    if (v_count != 0) {
        g.prim(1);
        ans = g.span_tree_weight;
    }
    std::cout << ans << "\n";
}
