#include <iostream>

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

int main(int, char**) {
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

    return 0;
}