#include <iostream>
#include <algorithm>

const int kSize = 100000;
struct Mydeque{
    int capacity = kSize;
    int array[kSize];
    int top_front;
    int top_back;

    Mydeque() {
        top_back = 0;
        top_front = 0;
    }

    void Push_front(int element) {
        array[top_front] = element;
        top_front = (top_front + 1) % kSize;
    }

    void Push_back(int element) {
        if (top_back == 0) {
            top_back = kSize - 1;
        }
        else {
            --top_back;
        }
        array[top_back] = element;
    }

    int Pop_front() {
        if (top_front == 0) {
            top_front = kSize - 1;
        }
        else {
            --top_front;
        }
        return array[top_front];
    }

    int Pop_back() {
        int rez = array[top_back];
        top_back = (top_back + 1) % kSize;
        return rez;
    }

    int Front() {
        if (top_front == 0) {
            return array[kSize-1];
        }
        else {
            return array[top_front - 1];
        }
    }

    int Back(){
        return array[top_back];
    }

    int Size() {
        if (top_back <= top_front) {
            return (top_front - top_back);
        }
        else {
            return (top_front + (kSize - top_back));
        }
    }

    void Clear() {
        top_back = 0;
        top_front = 0;
    }
};


int main() {
    int k;
    std::string str;
    Mydeque dek = Mydeque();
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> str;
        if (str == "push_front") {
            int n;
            std::cin >> n;
            dek.Push_front(n);
            std::cout << "ok" << "\n";
        }

        if (str == "push_back") {
            int n;
            std::cin >> n;
            dek.Push_back(n);
            std::cout << "ok" << "\n";
        }

        if (str == "pop_front") {
            if (dek.Size() == 0) {
                std::cout << ("error") << "\n";
            }
            else {
                std::cout << (dek.Pop_front()) << "\n";
            }
        }

        if (str == "pop_back") {
            if (dek.Size() == 0) {
                std::cout << ("error") << "\n";
            }
            else {
                std::cout << (dek.Pop_back()) << "\n";
            }
        }

        if (str == "front") {
            if (dek.Size() == 0) {
                std::cout << ("error") << "\n";
            }
            else {
                std::cout << (dek.Front()) << "\n";
            }
        }

        if (str == "back") {
            if (dek.Size() == 0) {
                std::cout << ("error") << "\n";
            }
            else {
                std::cout << (dek.Back()) << "\n";
            }
        }

        if (str == "size") {
            std::cout << (dek.Size()) << "\n";
        }

        if (str == "clear") {
            dek.Clear();
            std::cout << "ok" << "\n";
        }

        if (str == "exit") {
            std::cout << "bye" << "\n";
            break;
        }
    }
}
