#include <iostream>

void GetBest(char* field, int* best, int pos) {
    best[pos] = -1;

    if (field[pos] == 'w') {
        return;
    }

    int max_points = 0;
    int jumps[3] = {1, 3, 5};
    bool accessible = pos == 0;

    for (int i = 0; i < 3; ++i) {
        int prev_pos = pos - jumps[i];

        if (prev_pos < 0) {
            break;
        }

        if (best[prev_pos] == -1) {
            continue;
        }

        if (best[prev_pos] > max_points) {
            max_points = best[prev_pos];
        }

        accessible = true;
    }

    if (!accessible) {
        return;
    }

    if (field[pos] == '"') {
        max_points += 1;
    }

    best[pos] = max_points;
}

int main(int, char**) {
    int n;
    std::cin >> n;

    char* field = new char[n];
    /*
    . - no point
    " - 1 point
    w - inaccessible
    */
    int* best = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> field[i];
        best[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        GetBest(field, best, i);
    }

    std::cout << best[n - 1];

    delete[] field;
    return 0;
}