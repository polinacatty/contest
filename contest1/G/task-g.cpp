#include <iostream>
#include <algorithm>

bool func(long l, int k,  int n, long* coordinates) {
    long coordinate = coordinates[0];
    int k_1 = 0;
    for (int i = 1; i < n; i++) {
        if (coordinates[i] > (coordinate + l)) {
            ++k_1;
            coordinate = coordinates[i];
        }
    }
    ++k_1;
    if (k_1 <= k) {
        return true;
    }
    return false;
}


long* Merge(int size_1, int size_2, long* mas1, long* mas2) {
    long* mas = new long[size_1 + size_2];
    int it = 0;
    int it_1 = 0;
    int it_2 = 0;
    while ((it_1 != size_1) && (it_2 != size_2)) {
        if (mas1[it_1] < mas2[it_2]) {
            mas[it] = mas1[it_1];
            ++it;
            ++it_1;
        }
        else {
            mas[it] = mas2[it_2];
            ++it;
            ++it_2;
        }
    }
    if (it_1 == size_1) {
        while (it_2 != size_2) {
            mas[it] = mas2[it_2];
            ++it;
            ++it_2;
        }
    }
    else {
        while (it_1 != size_1) {
            mas[it] = mas1[it_1];
            ++it;
            ++it_1;
        }
    }
    return mas;
}

long* mergeSort(long* mas, int l, int r) {
    long* sorted = new long[r-l];
    if (r-l == 1) {
        sorted[0] = mas[l];
    }
    else {
        int mid = (l + r)/2;
        long* mas1 = mergeSort(mas, l, mid);
        long* mas2 = mergeSort(mas, mid, r);
        sorted = Merge(mid-l, r-mid, mas1, mas2);
    }

    return sorted;

}


int main() {
    int n, k;
    std::cin >> n >> k;
    long*  coordinates = new long[n];
    for (int i = 0; i < n; ++i) {
        long x;
        std::cin >> x;
        coordinates[i] = x;
    }
    coordinates = mergeSort(coordinates, 0, n);
    long l;
    if (func(0, k, n, coordinates)) {
        l = 0;
    }
    else {
        long l_1 = 0;
        long l_2 = ((coordinates[n-1] - coordinates[0]) / k) + 1;
        while ((l_2 - l_1) > 1) {
            l = (l_2 + l_1)/2;
            if (func(l, k, n, coordinates)) {
                l_2 = l;
            }
            else {
                l_1 = l;
            }
        }
        l = l_2;
    }
    std::cout << l;
}

