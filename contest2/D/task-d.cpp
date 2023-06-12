#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int* cnt = new int[301];
    for (int i = 0; i < 301; i++) {
        cnt[i] = 0;
    }
    std::string* res = new std::string[n];
    std::pair<int, std::string>* ege = new std::pair<int, std::string>[n];
    for (int i = 0; i < n; i++) {
        std::string surname;
        std::string name;
        int x;
        int y;
        int z;
        std::cin >> surname >> name >> x >> y >> z;
        std::string str = surname + " " + name;
        int sum_mark = x + y + z;
        ege[i] = {300 - sum_mark, str};
        cnt[300 - (x + y + z)]++;
    }
    int vsp = cnt[0];
    cnt[0] = 0;
    for (int i = 1; i < 301; i++) {
        int vsp_1 = cnt[i];
        cnt[i] = cnt[i-1] + vsp;
        vsp = vsp_1;
    }
    for (int i = 0; i < n; i ++) {
        res[cnt[ege[i].first]] = ege[i].second;
        ++cnt[ege[i].first];
    }
    for (int i = 0; i < n; i++) {
        std::cout << res[i] << "\n";
    }
}
