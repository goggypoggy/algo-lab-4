#include <iostream>
#include <cstdint>

/*
inf = false => ordinary value
inf = true => infinite value, sign in val
*/
struct value {
    int64_t val = 1;
    bool inf = true;

    bool is_pos_inf() {
        return inf && val > 0;
    }
    bool is_neg_inf() {
        return inf && val < 0;
    }
};

int binary_search(value* a, int n, value x) {
    int l = 0;
    int r = n - 1;
    
    while (l <= r) {
        int m = (l + r) / 2;
        if ((a[m].val < x.val || x.is_pos_inf()) && !a[m].is_pos_inf() ||
            a[m].is_neg_inf()) {
            l = m + 1;
        } else {
            r = m - 1;
        }   
    }

    return l;
}

int main(int, char**) {
    int n;
    std::cin >> n;

    int64_t* a = new int64_t[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    value* d = new value[n + 1];
    d[0] = {-1, true};

    for (int i = 0; i < n; ++i) {
        int j = binary_search(d, n + 1, {a[i], false});
        if (a[i] < d[j].val || d[j].is_pos_inf()) {
            d[j] = {a[i], false};
        }
        
        /*
        for (int k = 0; k <= n; ++k) {
            if (d[k].inf) {
                std::cout << (d[k].val > 0 ? "+" : "-") << "inf";
            } else {
                std::cout << d[k].val;
            }
            std::cout << (k == n ? "\n" : " ");
        }
        */
    }
    
    std::cout << binary_search(d, n + 1, {1, true}) - 1;

    delete[] d;
    delete[] a;
    return 0;
}