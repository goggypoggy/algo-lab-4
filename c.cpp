#include <iostream>

struct node;
struct node {
    int val;
    node* next;
    node* prev;

    node(int x,
        node* prv = nullptr, node* nxt = nullptr
    ) : 
        val(x),
        next(nxt), prev(prv)
    {}
};

struct dequeue {
    node* start = nullptr;
    node* end = nullptr;

    ~dequeue() {
        node* prev = start;

        while (prev != nullptr) {
            node* next = prev->next;
            delete prev;
            prev = next;
        }
    }

    void push_end(int x) {
        if (end == nullptr) {
            push_first(x);
            return;
        }

        node* new_node = new node(x, end, nullptr);
        end->next = new_node;
        end = new_node;
    }

    void push_start(int x) {
        if (start == nullptr) {
            push_first(x);
            return;
        }

        node* new_node = new node(x, nullptr, start);
        start->prev = new_node;
        start = new_node;
    }

    int check_start() {
        if (start == nullptr) {
            return 0;
        }

        return start->val;
    }

    int pop_start() {
        if (start == nullptr) {
            return 0;
        }

        int x = start->val;
        node* to_del = start;

        if (start->next != nullptr) {
            start->next->prev = nullptr;
        }
        start = start->next;

        delete to_del;

        if (start == nullptr) {
            end = nullptr;
        }

        return x;
    }

    bool empty() {
        return start == nullptr;
    }

    void output() {
        node* beg = start;
        while (beg != nullptr) {
            std::cout << beg->val << (beg->next == nullptr ? "\n" : ", ");
            beg = beg->next;
        }
    }

    private:
    void push_first(int x) {
        node* new_node = new node(x);
        start = end = new_node;
    }
};

int depth = 0;

int check(dequeue* A, dequeue* B, int prev) {
    std::cout << "--- " << depth << " ---------------------\n";
    std::cout << "A: ";
    A->output();
    std::cout << "B: ";
    B->output();
    std::cout << "prev: " << prev << std::endl;
    std::cout << "------------------------\n";

    
    if (A->empty() || B->empty()) {
        return prev;
    }

    bool has_similar = A->check_start() == B->check_start();
    
    if (has_similar) {
        int extra = 0;
        extra = A->pop_start();
        B->pop_start();
        prev++;
        int M = check(A, B, prev);
        std::cout << "depth " << depth << " M->" << M << std::endl;
        A->push_start(extra);
        B->push_start(extra);
        prev--;

        return M;
    }

    int L = 0;
    if (!A->empty()) {
        int x = A->pop_start();
        depth++;
        L = check(A, B, prev);
        std::cout << "depth " << depth << " L->" << L << std::endl;
        depth--;
        A->push_start(x);
    } 

    int R = 0;
    if (!B->empty()) {
        int x = B->pop_start();
        depth++;
        R = check(A, B, prev);
        std::cout << "depth " << depth << " R->" << R << std::endl;
        depth--;
        B->push_start(x);   
    }

    return std::max(L, R);
}

int main(int, char**) {
    int n;
    int m;
    
    std::cin >> n;
    // int *a = new int[n];
    dequeue A;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        A.push_end(x);
        // std::cin >> a[i];
    }
    
    std::cin >> m;
    // int *b = new int[m];
    dequeue B;
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        B.push_end(x);
        // std::cin >> b[i];
    }

    std::cout << check(&A, &B, 0);

    return 0;
}