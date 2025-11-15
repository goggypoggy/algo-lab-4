#include <iostream>
#include <cstdlib>

#define RAND_MAX INT_MAX

int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }

    return result;
}

void from_num_to_mask(int x, char* mask, int n) {
    for (int i = 0; i < n; ++i) {
        int r = x % 3;
        x /= 3;
        mask[i] = r + '0';
    }
    mask[n] = 0;
}

bool can_go_from_L_to_R(int L, int R, int n) {
    char* Lmask = new char[n + 1];
    char* Rmask = new char[n + 1];

    from_num_to_mask(L, Lmask, n);
    from_num_to_mask(R, Rmask, n);

    int len = 0;
    for (int i = 0; i < n; ++i) {
        if (Lmask[i] == Rmask[i] && Lmask[i] == '0') {
            len++;
        } else {
            if (len % 3 != 0) {
                return false;
            }
            len = 0;
            if (Lmask[i] == '0' && Rmask[i] == '2') {
                continue;
            }
            if (Rmask[i] != Lmask[i] - 1) {
                return false;
            }
        }
    }

    if (len % 3 != 0) {
        return false;
    }

    //std::cout << Lmask << " " << Rmask << "\n";

    delete[] Lmask;
    delete[] Rmask;

    return true;
}


struct pair {
    int left = 0;
    int right = 0;
};

bool operator<(const pair& lhs, const pair& rhs) {
    if (lhs.left < rhs.left) {
        return true;
    } else if (lhs.left == rhs.left) {
        return lhs.right < rhs.right;
    } else {
        return false;
    }
}

bool operator==(const pair& lhs, const pair& rhs) {
    return lhs.left == rhs.left && lhs.right == rhs.right;
}

std::ostream& operator<<(std::ostream& stream, const pair& x) {
    stream << "{" << x.left << ":" << x.right << "}";
    return stream;
}

template<typename T>
struct vector {
    int size = 0;
    int capacity = 0;
    T* mem;

    vector()
     : size(0), capacity(10),
       mem(new T[10])
    {}

    ~vector() {
        delete[] mem;
    }

    
    void add(const T& x) {
        if (size == capacity) {
            increaseCapacity();
        }
        
        mem[size] = x;
        size++;
        sorted = false;
    }
    
    void sort() {
        if (!sorted) {
            Partition(0, size);
            sorted = true;
        }
    }
    
    void output() {
        for (int i = 0; i < size; ++i) {
            std::cout << mem[i] << (i == size - 1 ? "\n" : " ");
        }
    }

    bool is_in(const T& x) {
        if (!sorted) {
            sort();
        }

        int l = 0;
        int r = size - 1;

        while (l <= r) {
            int m = (l + r) / 2;
            if (mem[m] < x) {
                l = m + 1;
            } else {
                r = m - 1;
            }   
        }

        return mem[l] == x;
    }

    private:
    bool sorted = false;

    void increaseCapacity() {
        capacity *= 2;
        T* new_mem = new T[capacity];
        for (int i = 0; i < size; ++i) {
            new_mem[i] = mem[i];
        }
        delete[] mem;
        mem = new_mem;
    }

    void Swap(T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    int Rand(int min, int max) {
        return min + (std::rand() % (max - min));
    }

    void Partition(int l, int r) {
        T pivot = mem[Rand(l, r - 1)];
        int i = l;
        int j = r - 1;
        
        while (i <= j) {
            while (mem[i] < pivot && i < r) {
                i++;
            }

            while (pivot < mem[j] && j >= l) {
                j--;
            }

            if (i <= j) {
                Swap(mem[i], mem[j]);
                i++;
                j--;
            }
        }

        if (l < j) {
            Partition(l, j + 1);
        }
        if (i < r - 1) {
            Partition(i, r);
        }
    }
};

int main(int, char**) {
    vector<pair> V;
    V.add({1, 2});
    V.add({3, 2});
    V.add({1, 5});
    V.add({4, 2});
    V.add({4, 1});
    V.add({2, 6});
    V.add({2, 1});
    V.add({3, -4});

    V.output();
    std::cout << V.is_in({3, 2});
    std::cout << V.is_in({3, 5});
    std::cout << V.is_in({1, 5});
    /*
    int n;
    int m;

    std::cin >> n >> m;

    int maxMask = pow(3, n);

    int** d = new int*[maxMask];
    for (int i = 0; i < maxMask; ++i) {
        d[i] = new int[maxMask];
    }

    for (int i = 0; i < maxMask; ++i) {
        for (int j = 0; j < maxMask; ++j) {
            d[i][j] = can_go_from_L_to_R(i, j, n);
        }
    }

    int** A = new int*[m + 1];
    for (int i = 0; i <= m; ++i) {
        A[i] = new int[maxMask];
    }

    for (int p = 0; p < maxMask; ++p) {
        A[1][p] = d[0][p];
    }

    for (int i = 2; i <= m; ++i) {
        for (int p = 0; p < maxMask; ++p) {
            A[i][p] = 0;
            for (int j = 0; j < maxMask; ++j) {
                A[i][p] += A[i - 1][j] * d[j][p];
            }
        }
    }

    std::cout << A[m][0];

    for (int i = 0; i <= m; ++i) {
        delete[] A[i];
    }
    delete[] A;

    for (int i = 0; i < maxMask; ++i) {
        delete[] d[i];
    }
    delete[] d;
    */
    return 0;
}