#include <iostream>
#include <iomanip>

int* w;
double* v;

void solve_forwards(double** dp, int n, int W) {
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    for (int j = 0; j <= W; ++j) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        int item = i - 1;
        for (int j = 1; j <= W; ++j) {
            if (j - w[item] >= 0) {
                dp[i][j] = std::max(dp[i - 1][j - w[item]] + v[item], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

void solve_backwards(double** dp, int n, int W) {
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    for (int j = 0; j <= W; ++j) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        int item = n - i;
        for (int j = 1; j <= W; ++j) {
            if (j - w[item] >= 0) {
                dp[i][j] = std::max(dp[i - 1][j - w[item]] + v[item], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

void output(double** dp, int n, int W) {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            std::cout << std::showpoint << std::fixed << std::setprecision(1) << dp[i][j] << (j == W ? "\n" : " ");
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

    double** dpF = new double*[n + 1];
    double** dpB = new double*[n + 1];
    for (int i = 0; i <= n; ++i) {
        dpF[i] = new double[W + 1];
        dpB[i] = new double[W + 1];
    }

    solve_forwards(dpF, n, W);
    solve_backwards(dpB, n, W);

    double* answer = new double[n];
    for (int ignored = 0; ignored < n; ++ignored) {
        double maxD = 0;
        for (int j = 0; j <= W; ++j) {
            double d = dpF[ignored][W - j] + dpB[n - 1 - ignored][j];
            maxD = std::max(maxD, d);
        }
        answer[ignored] = maxD;
    }

    /*
    output(dpF, n, W);
    std::cout << std::endl;
    output(dpB, n, W);
    */

    for (int i = 0; i < n; ++i) {
        std::cout << std::showpoint << std::fixed << std::setprecision(9) << answer[i] << std::endl;
    }

    for (int i = 0; i <= n; ++i) {
        delete dpF[i];
        delete dpB[i];
    }
    delete[] dpF;
    delete[] dpB;

    delete[] answer;
    delete[] w;
    delete[] v;

    return 0;
}