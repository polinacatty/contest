#include <iostream>
#include <queue>

struct Heap {
    std::pair<int, int>* heap;
    int size;

    Heap(std::pair<int, int> a_0, int n) {
        heap = new std::pair<int, int>[n+1];
        heap[0] = a_0;
        size = 0;
    }

    std::pair<int, int> Get_back() {
        return heap[size+1];
    }

    void siffup(int v) {
        while (v != 1) {
            if ((heap[v].first < heap[v/2].first) || ((heap[v].first == heap[v/2].first) && (heap[v].second < heap[v/2].second))) {
                std::pair<int, int> z = heap[v];
                heap[v] = heap[v/2];
                heap[v/2] = z;
                v = v/2;
            } else {
                break;
            }
        }
    }

    void siffdown(int v) {
        while (2*v <= size) {
            int u = 2*v;
            if ((2*v + 1 <= size) && ((heap[2*v+1].first < heap[2*v].first) || ((heap[2*v+1].first == heap[2*v].first) && (heap[2*v+1].second < heap[2*v].second)))) {
                u = 2*v + 1;
            }
            if ((heap[u].first < heap[v].first) || ((heap[u].first == heap[v].first) && (heap[u].second < heap[v].second))) {
                std::pair<int, int> z = heap[u];
                heap[u] = heap[v];
                heap[v] = z;
                v = u;
            } else {
                break;
            }
        }
    }

    void insert(std::pair<int, int> x) {
        ++size;
        heap[size] = x;
        siffup(size);
    }

    void arr_insert(std::pair<int, int> x) {
        ++size;
        heap[size] = x;
    }

    void extractmin() {
        std::pair<int, int> z = heap[1];
        heap[1] = heap[size];
        heap[size] = z;
        --size;
        siffdown(1);
    }

};



int main() {
    int s = 0;
    int k;
    std::cin >> k;
    std::queue<int> mas[k];
    for (int i = 0; i < k; i++) {
        int n;
        std::cin >> n;
        s += n;
        std::queue<int> mas_0;
        for (int j = 0; j < n; j++) {
            int x;
            std::cin >> x;
            mas_0.push(x);
        }
        mas[i] = mas_0;
    }
    Heap heap = Heap({0, 0}, k);
    for (int i = 0; i < k; i++) {
        heap.arr_insert({mas[i].front(), i});
        mas[i].pop();
    }
    for (int i = k; i >=1; --i) {
        heap.siffdown(i);
    }
    for (int i = 0; i < s; i++) {
        heap.extractmin();
        std::cout << heap.Get_back().first << " ";
        int it = heap.Get_back().second;
        if (!mas[it].empty()) {
            heap.insert({mas[it].front(), it});
            mas[it].pop();
        }
    }
}
