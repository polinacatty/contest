#include <algorithm>
#include <iostream>

const int kSize = 1000000;

struct Mystack {
    int capacity = kSize;
    int mytop;
    int array[kSize];

    Mystack() {
        mytop = -1;
    }

    void Push(int element) {
        array[++mytop] = element;
    }

    int Pop() {
        --mytop;
        return array[mytop + 1];
    }

    int Top() {
        return array[mytop];
    }

    bool Empty() {
        if (mytop == -1){
            return true;
        }
        return false;
    }

    int Size() {
        return (mytop + 1);
    }

    void Clear() {
        mytop = -1;
    }
};


struct Myqueue {
    Mystack stack1;
    Mystack stack2;
    Mystack min1;
    Mystack min2;

    Myqueue() {
        stack1 = Mystack();
        stack2 = Mystack();
        min1 = Mystack();
        min2 = Mystack();
    }

    void Push(int element) {
        if (stack1.Empty()) {
            stack1.Push(element);
            min1.Push(element);
        }
        else {
            min1.Push(std::min(element, min1.Top()));
            stack1.Push(element);
        }
    }

    int Pop() {
        if (stack2.Empty()) {
            int c = stack1.Size();
            for (int i = 0; i < c; ++i) {
                if (stack2.Empty()) {
                    min2.Push(stack1.Top());
                }
                else{
                    min2.Push(std::min(stack1.Top(), min2.Top()));
                }
                stack2.Push(stack1.Pop());
            }
            min1.Clear();
        }
        min2.Pop();
        int z = stack2.Pop();
        return z;
    }

    int Top() {
        if (stack2.Empty()) {
            int c = stack1.Size();
            for (int i = 0; i < c; ++i) {
                if (stack2.Empty()) {
                    min2.Push(stack1.Top());
                }
                else{
                    min2.Push(std::min(stack1.Top(), min2.Top()));
                }
                stack2.Push(stack1.Pop());
            }
            min1.Clear();
        }
        return stack2.Top();
    }

    int Size() {
        return (stack1.Size() + stack2.Size());
    }

    void Clear() {
        stack1.Clear();
        stack2.Clear();
        min1.Clear();
        min2.Clear();
    }

    int Min() {
        if (min1.Empty()) {
            return min2.Top();
        }
        else{
            if (min2.Empty()) {
                return min1.Top();
            }
            else {
                return std::min(min1.Top(), min2.Top());
            }
        }
    }
};



int main() {
    int M;
    std::cin >> M;
    Myqueue hat = Myqueue();
    for (int i = 0; i < M; ++i) {
        std::string str;
        int k;
        std::cin >> str;
        if (str == "enqueue") {
            std::cin >> k;
            hat.Push(k);
            std::cout << "ok" << "\n";
        }
        if (str == "dequeue") {
            if (hat.Size() == 0) {
                std::cout << "error" << "\n";
            }
            else {
                std::cout << hat.Pop() << "\n";
            }
        }
        if (str == "front") {
            if (hat.Size() == 0) {
                std::cout << "error" << "\n";
            }
            else {
                std::cout << hat.Top() << "\n";
            }
        }
        if (str == "size") {
            std::cout << hat.Size() << "\n";
        }
        if (str == "clear") {
            hat.Clear();
            std::cout << "ok" << "\n";
        }
        if (str == "min") {
            if (hat.Size() == 0) {
                std::cout << "error" << "\n";
            }
            else {
                std::cout << hat.Min() << "\n";
            }
        }
    }
    return 0;
}

