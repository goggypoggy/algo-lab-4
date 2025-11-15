#include <iostream>

int main(int, char**) {
    int n;
    int m;
    
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    
    std::cin >> m;
    int *b = new int[m];
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    int** dp = new int*[n + 1];
    for (int i = 0; i <= n; ++i) {
        dp[i] = new int[m + 1];
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int prev = std::max(dp[i - 1][j], dp[i][j - 1]);
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = prev + 1;
            } else {
                dp[i][j] = prev;
            }
        }
    }
    
    /*
    for (int j = 0; j <= m; ++j) {
        if (j != 0) {
            std::cout << b[j - 1] << (j == m ? "\n" : " ");
        } else {
            std::cout << "    ";
        }
    }
    for (int i = 0; i <= n; ++i) {
        if (i != 0) {
            std::cout << a[i - 1] << " ";
        } else {
            std::cout << "  ";
        }
        for (int j = 0; j <= m; ++j) {
            std::cout << dp[i][j] << (j == m ? "\n" : " ");
        }
    }
    */

    std::cout << dp[n][m];

    for (int i = 0; i <= n; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
    return 0;
}