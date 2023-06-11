#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

class SparseTable {
public:
    SparseTable(const std::vector<std::pair<int, int>>& data)
            : logs_(data.size() + 3, 0), size_(data.size()) {
        PrecalcLogs(data.size() + 2);
        log_n_ = logs_[size_];
        sparse_.assign(log_n_ + 1,
                       std::vector<std::pair<int, int>>(size_, {int(), int()}));
        BuildSparse(data);
    }

    int Query(int left, int right) {
        int log = logs_[right - left];
        return std::min(sparse_[log][left].first,
                        sparse_[log][right - (1 << log)].first);
    }

    int Shmery(int left, int right) {
        int log = logs_[right - left];
        int value;
        if (sparse_[log][left].first < sparse_[log][right - (1 << log)].first) {
            value = sparse_[log][left].second;
        } else {
            value = sparse_[log][right - (1 << log)].second;
        }
        if (right - left == 2) {
            return std::max(sparse_[0][left].first, sparse_[0][left + 1].first);
        }
        if (value == left) {
            return Query(left + 1, right);
        }
        if (value == right - 1) {
            return Query(left, right - 1);
        }
        if (value - left == 1 && right - value == 2) {
            return std::min(sparse_[0][left].first, sparse_[0][right - 1].first);
        }
        if (value - left == 1) {
            return std::min(sparse_[0][left].first, Query(value + 1, right));
        }
        if (right - value == 2) {
            return std::min(Query(left, value), sparse_[0][right - 1].first);
        }
        return std::min(Query(left, value), Query(value + 1, right));
    }

private:
    std::vector<int> logs_;
    size_t size_;
    size_t log_n_;
    std::vector<std::vector<std::pair<int, int>>> sparse_;
    void BuildSparse(const std::vector<std::pair<int, int>>& data) {
        sparse_[0] = data;
        for (size_t k = 1; k <= log_n_; ++k) {
            for (size_t i = 0; i + (1 << k) < size_; ++i) {
                sparse_[k][i].first = std::min(
                        sparse_[k - 1][i].first, sparse_[k - 1][i + (1 << (k - 1))].first);
                if (sparse_[k - 1][i].first <
                    sparse_[k - 1][i + (1 << (k - 1))].first) {
                    sparse_[k][i].second = sparse_[k - 1][i].second;
                } else {
                    sparse_[k][i].second = sparse_[k - 1][i + (1 << (k - 1))].second;
                }
            }
        }
    }

    void PrecalcLogs(int size) {
        logs_[0] = 0;
        logs_[1] = 0;
        for (int i = 2; i <= size; ++i) {
            logs_[i] = logs_[i / 2] + 1;
        }
    }
};

int main() {
    size_t size;
    size_t diapazone;
    std::cin >> size >> diapazone;
    std::vector<std::pair<int, int>> data(size + 1);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> data[i].first;
        data[i].second = i;
    }
    data[size].first = std::numeric_limits<int>::max();
    data[size].second = size;
    SparseTable sparse(data);
    size_t left;
    size_t right;
    for (size_t i = 0; i < diapazone; ++i) {
        std::cin >> left >> right;
        std::cout << sparse.Shmery(left - 1, right) << "\n";
    }
}
