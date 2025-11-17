#include <iostream>
#include <cstdlib>

#define RAND_MAX 2147483647

int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }

    return result;
}

struct string {
    int length = 0;
    char* c;
    
    string(int len)
    : length(len), c(new char[len])
    {}

    string(const string& s)
    : length(s.length), c(new char[s.length])
    {
        memcpy(c, s.c, length);
    }

    string& operator=(const string& s) {
        if (this == &s) {
            return *this;
        }

        delete[] c;

        length = s.length;
        c = new char[length];

        memcpy(c, s.c, length);

        return *this;
    }

    ~string() {
        delete[] c;
    }

    char& operator[](int i) {
        return c[i];
    }

    const char& operator[](int i) const {
        return c[i];
    }

    void clear() {
        memset(c, 0, length);
    }
};

std::ostream& operator<<(std::ostream& stream, const string& s) {
    for (int i = 0; i < s.length; ++i) {
        stream << s[i];
    }
    return stream;
}

string& from_num_to_mask(int x, string& mask) {
    for (int i = 0; i < mask.length; ++i) {
        int r = x % 3;
        x /= 3;
        mask[i] = r + '0';
    }

    return mask;
}

bool can_go_from_L_to_R(int L, int R, int n) {
    static string Lmask(n + 1);
    static string Rmask(n + 1);

    from_num_to_mask(L, Lmask);
    from_num_to_mask(R, Rmask);

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

    Lmask.clear();
    Rmask.clear();

    return true;
}

template<typename T1, typename T2>
struct pair {
    T1 left;
    T2 right;
};

bool operator<(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    if (lhs.left < rhs.left) {
        return true;
    } else if (lhs.left == rhs.left) {
        return lhs.right < rhs.right;
    } else {
        return false;
    }
}

bool operator==(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.left == rhs.left && lhs.right == rhs.right;
}

std::ostream& operator<<(std::ostream& stream, const pair<int, int>& x) {
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

    vector(const vector<T>& V)
     : size(V.size), capacity(V.capacity),
       mem(new T[V.capacity])
    {
        for (int i = 0; i < size; ++i) {
            mem[i] = V.mem[i];
        }        
    }

    vector<T>& operator=(const vector<T>& V) {
        if (this == &V) {
            return *this;
        }

        delete[] mem;
        size = V.size;
        capacity = V.capacity;

        mem = new T[capacity];
        for (int i = 0; i < size; ++i) {
            mem[i] = V.mem[i];
        }

        return *this;
    }

    ~vector() {
        delete[] mem;
    }

    T& operator[](int i) {
        return mem[i];
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
        if (size == 0) {
            std::cout << "none\n";
            return;
        }

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

    void clear() {
        delete[] mem;

        size = 0;
        capacity = 10;
        mem = new T[10];
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

int from_mask_to_num(string& mask) {
    int result = 0;
    int three = 1;

    for (int i = 0; i < mask.length; ++i) {
        result += three * (mask[i] - '0');
        three *= 3;    
    }

    return result;
}

void resolveV(string& mask, vector<int>& connections) {
    string resolvedMask = mask;
    
    int len = 0;
    for (int i = 0; i < mask.length; ++i) {
        if (mask[i] == 'V') {
            len++;
            resolvedMask[i] = '2';
            if (len >= 3) {
                string zeroVariant = resolvedMask;
                zeroVariant[i] = zeroVariant[i - 1] = zeroVariant[i - 2] = '0';

                resolveV(zeroVariant, connections);
            }
        } else {
            len = 0;
        }
    }

    connections.add(from_mask_to_num(resolvedMask));
}

void addPossibleConnections(int start, vector<int>& connections, int n) {
    string Lmask(n);
    from_num_to_mask(start, Lmask);

    string Rmask(n);

    for (int i = 0; i < n; ++i) {
        if (Lmask[i] == '0') {
            Rmask[i] = 'V';
        } else {
            Rmask[i] = Lmask[i] - 1;
        }
    }

    resolveV(Rmask, connections);
}

int main(int, char**) {
    int n;
    int m;

    std::cin >> n >> m;

    if (m < 3) {
        std::cout << (n % 3 == 0 ? 1 : 0);
        return 0;
    }

    int maxMask = pow(3, n);

    vector<vector<int>> d;

    for (int i = 0; i < maxMask; ++i) {
        vector<int> connections;
        addPossibleConnections(i, connections, n);
        d.add(connections);
    }

    /*
    for (int i = 0; i < d.size; ++i) {
        string s(n);
        std::cout << from_num_to_mask(i, s) << ": ";
        for (int k = 0; k < d[i].size; ++k) {
            int j = d[i][k];
            std::cout << from_num_to_mask(j, s) << (k == d[i].size - 1 ? "" : ", ");
        }
        std::cout << std::endl;
    }
    */
    
    int64_t** A = new int64_t*[m + 1];
    for (int i = 0; i <= m; ++i) {
        A[i] = new int64_t[maxMask];
        memset(A[i], 0, sizeof(int64_t) * maxMask);
    }
    
    vector<int> prevMasks;
    vector<int> newMasks;

    bool* added = new bool[maxMask];

    for (int k = 0; k < d[0].size; ++k) {
        A[1][d[0][k]] = 1;
        prevMasks.add(d[0][k]);
    }
    
    for (int i = 1; i < m; ++i) {
        memset(added, 0, sizeof(bool) * maxMask);

        for (int prev = 0; prev < prevMasks.size; ++prev) {
            int j = prevMasks[prev];

            for (int new_ = 0; new_ < d[j].size; ++new_) {
                int p = d[j][new_];
                A[i + 1][p] += A[i][j];
                if (!added[p]) {
                    newMasks.add(p);
                    added[p] = true;
                }
            }
        }
        
        prevMasks = newMasks;
        newMasks.clear();
    }

    std::cout << A[m][0];
    
    delete[] added;
    for (int i = 0; i <= m; ++i) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}