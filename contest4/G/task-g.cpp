#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>

class Graph {

public:
    std::vector<std::vector<size_t>> conn;
    std::vector<size_t> color;
    std::deque<size_t> topology;

public:

    explicit Graph(size_t v_count = 0) {
        for (size_t i = 0; i < v_count + 1; ++i) {
            conn.emplace_back(0);
            color.emplace_back(0);
        }
    }

    void add_or_edge(size_t first, size_t second) {
        conn[first].push_back(second);
    }

    void add_or_edges(size_t e_count) {
        for (size_t i = 0; i < e_count; ++i) {
            size_t first;
            size_t second;
            std::cin >> first >> second;
            add_or_edge(first, second);
        }
    }


    std::vector<size_t>& operator[](size_t v) {
        return conn[v];
    }

    bool dfs(size_t now, size_t k = 1) {
        color[now] = k;
        for (size_t neig : conn[now]) {
            if (color[neig] == 0) {
                if (!dfs(neig, k)) {
                    return false;
                }
            } else if (color[neig] == k) {
                return false;
            }
        }
        color[now] = k + 1;
        topology.push_front(now);
        return true;
    }

    bool colorize_graph(size_t k = 1) {
        for (size_t v = 1; v < conn.size(); ++v) {
            if (color[v] != 0) {
                continue;
            }
            if (!dfs(v, k)) {
                return false;
            }
        }
        return true;
    }

    void clear_color() {
        for (size_t i = 1; i < conn.size() + 1; ++i) {
            color[i] = 0;
        }
    }

};

bool comp(size_t f, size_t s) {
    return f < s;
}

void print(const std::vector<size_t>& vec) {
    for (auto v : vec) {
        std::cout << v << " ";
    }
}

void print(const std::deque<size_t>& vec) {
    for (auto v : vec) {
        std::cout << v << " ";
    }
}

void print(const int& x) {
    std::cout << x << " ";
}

int main() {
    size_t v_count;
    size_t e_count;
    std::cin >> v_count >> e_count;
    Graph g(v_count);
    g.add_or_edges(e_count);
    if (g.colorize_graph()) {
        print(g.topology);
    } else {
        print(-1);
    }
}
