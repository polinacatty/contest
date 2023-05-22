#include <iostream>
#include <stdlib.h>

int* Partition(int* arr, int l, int r, int x) {
    int beg = l;
    int end = r - 1;
    while (beg < end) {
        while (arr[beg] < x) {
            beg++;
            if (beg >= r) {
                break;
            }
        }
        while (arr[end] >= x) {
            end--;
            if (end < l) {
                break;
            }
        }
        if (beg < end) {
            int z = arr[beg];
            arr[beg] = arr[end];
            arr[end] = z;
        }
    }
    if (beg == r) {
        return arr;
    }
    end = r - 1;
    while (beg < end) {
        while (arr[beg] == x) {
            beg++;
            if (beg >= r) {
                break;
            }
        }
        while (arr[end] > x) {
            end--;
            if (end < l) {
                break;
            }
        }
        if (beg < end) {
            int z = arr[beg];
            arr[beg] = arr[end];
            arr[end] = z;
        }
    }
    return arr;
}

int Kb(int* arr, int l, int r, int k) {
    int m;
    m = arr[l + rand() % (r - l)];
    Partition(arr, l, r, m);
    int i = l;
    while (arr[i] < m) {
        i ++;
        if (i >= r) {
            break;
        }
    }
    int n_1 = i - l;
    while (arr[i] == m) {
        i ++;
        if (i >= r) {
            break;
        }
    }
    int n_2 = i - l - n_1;
    if (k <= n_1) {
        return Kb(arr, l, l + n_1, k);
    }
    if ((k > n_1) && (k <= n_1 + n_2)) {
        return m;
    }
    return Kb(arr, l + n_1 + n_2, r, k - n_1 - n_2);
}

int K(int* arr, int l, int r, int k) {
    if (r - l < 5) {
        return Kb(arr, l, r, k);
    }
    int* B = new int[(r - l) / 5];
    for (int i = 0; i < (r - l) / 5; i++) {
        if (l + 5*i + 5 > r) {
            B[i] = Kb(arr, l + 5*i, r, 1);
        } else {
            B[i] = Kb(arr, l + 5*i, l + 5*i + 5, 3);
        }
    }
    int m = K(B, 0, (r - l) / 5, ((r - l) / 10) + 1);
    Partition(arr, l, r, m);
    int i = l;
    while (arr[i] < m) {
        i ++;
        if (i >= r) {
            break;
        }
    }
    int n_1 = i - l;
    while (arr[i] == m) {
        i ++;
        if (i >= r) {
            break;
        }
    }
    int n_2 = i - l - n_1;
    if (k <= n_1) {
        return K(arr, l, l + n_1, k);
    }
    if ((k > n_1) && (k <= n_1 + n_2)) {
        return m;
    }
    return K(arr, l + n_1 + n_2, r, k - n_1 - n_2);
}

void Qsort(int* arr, int l, int r) {
    if (r == l) {
        return;
    }
    int m = K(arr, l, r, ((r - l) / 2) + 1);
    Partition(arr, l, r, m);
    int i = l;
    while (arr[i] < m) {
        i ++;
        if (i >= r) {
            break;
        }
    }
    int n_1 = i - l;
    while (arr[i] == m) {
        i ++;
        if (i >= r) {
            break;
        }
    }
    int n_2 = i - l - n_1;
    Qsort(arr, l, l + n_1);
    Qsort(arr, l + n_1 + n_2, r);
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    Qsort(arr, 0, n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
}
