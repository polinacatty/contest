#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <map>
#include <queue>

class Graph {

public:
    std::vector<std::vector<std::pair<size_t, size_t>>> conn;
    size_t v_count;
    size_t e_count;

    std::vector<size_t> dfs_color;

    std::vector<std::pair<int, size_t>> bfs_way;

    std::vector<size_t> parent;


public:

    explicit Graph(size_t ver_count = 0) {
        e_count = 0;
        v_count = ver_count;
        for (size_t i = 0; i < ver_count + 1; ++i) {
            conn.emplace_back(0);
            dfs_color.emplace_back(0);
            bfs_way.emplace_back(-1, 0);
            parent.emplace_back(0);

        }
    }

    void add_edge(size_t first, size_t second, bool oriented = false, size_t ord = 0) {
        ++e_count;
        if (oriented) {
            conn[first].emplace_back(second, ord);
        } else {
            conn[first].emplace_back(second, ord);
            conn[second].emplace_back(first, ord);
        }
    }

    void add_edges(size_t ed_count, bool oriented = false) {
        for (size_t i = 1; i < ed_count + 1; ++i) {
            size_t first;
            size_t second;
            std::cin >> first >> second;
            add_edge(first, second, oriented, i);
        }
    }

    void bfs(size_t point) {
        bfs_way[point] = {0, 0};
        std::queue<size_t> Q;
        Q.push(point);
        while (!Q.empty()) {
            size_t ver = Q.front();
            Q.pop();
            for (auto to : conn[ver])
                if (bfs_way[to.first].first == -1) {
                    bfs_way[to.first].first = bfs_way[ver].first + 1;
                    bfs_way[to.first].second = ver;
                    Q.push(to.first);
                }
        }
    }


    std::vector<size_t> process_graph(size_t from, size_t to) {
        std::vector<size_t> ans;
        bfs(to);
        for (size_t i = from; i != 0; i = bfs_way[i].second) {
            ans.push_back(i);
        }
        return ans;
    }

};


int main() {
    size_t v_count, e_count;
    std::cin >> v_count >> e_count;
    size_t start;
    size_t end;
    std::cin >> start >> end;

    Graph g(v_count);
    g.add_edges(e_count);

    auto ans = g.process_graph(start, end);
    std::cout << g.bfs_way[start].first << "\n";
    if (g.bfs_way[start].first >= 0) {
        for (auto v : ans) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
