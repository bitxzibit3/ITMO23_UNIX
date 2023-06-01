#include <iostream>
#include <ctime>
#include <iomanip>

int f1(int x) {
    return x * x - x * x  + 4 * x  - 5 * x + x + x;
}

int f2(int x) {
    return x - x;
}

int f3(int x, int y) {
    return x + y - x;
}

double count_n (int iterations, int x = 1) {
    double begin = clock();
    for (int i = 0; i < iterations; i++) {
        int a = f1(x);
        int b = f2(x);
        f3(a, b);
    }
    double end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

double count_average(int iterations, int x = 1, int COUNT = 1000) {
    double time = 0;
    for (int i = 0; i < COUNT; i++) {
        time += count_n(iterations, x);
    }
    double t = time / COUNT;
    std::cout << std::fixed << std::setprecision(6) << "Time for " << iterations << " : " << t << " s.\n";
    return t;
}

int main() {
    count_average(10000);
    count_average(100000);
    count_average(1000000);
}