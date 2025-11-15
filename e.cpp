#include <iostream>
#include <iomanip>

int* w;
double* v;

void solve_backpack(double** dp, int n, int W, int ignore) {
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    for (int j = 0; j <= W; ++j) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        int item = i - 1;
        for (int j = 1; j <= W; ++j) {
            if (item == ignore) {
                dp[i][j] = dp[i - 1][j];
                continue;
            }

            if (j - w[item] >= 0) {
                dp[i][j] = std::max(dp[i - 1][j - w[item]] + v[item], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

int main(int, char**) {
    int n, W;
    std::cin >> n >> W;

    w = new int[n];
    v = new double[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> w[i] >> v[i];
    }

    double** dp = new double*[n + 1];
    for (int i = 0; i <= n; ++i) {
        dp[i] = new double[W + 1];
    }

    double* answer = new double[n];
    for (int i = 0; i < n; ++i) {
        solve_backpack(dp, n, W, i);
        answer[i] = dp[n][W];
    }

    for (int i = 0; i < n; ++i) {
        std::cout << std::showpoint << std::fixed << std::setprecision(9) << answer[i] << std::endl;
    }

    for (int i = 0; i <= n; ++i) {
        delete dp[i];
    }
    delete[] dp;

    delete[] answer;
    delete[] w;
    delete[] v;

    return 0;
}