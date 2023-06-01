#include <iostream>
#include <ctime>
#include <iomanip>
#include <thread>


double count_n(int iterations, int x = 1) {
    int res1[iterations],
            res2[iterations];
    clock_t begin = clock();
    std::thread th1(
            [&res1, x](int iterations) {
                for (int i = 0; i < iterations; i++)
                    res1[i] = x * x - x * x + 4 * x - 5 * x + x + x;
            }, iterations);
    std::thread th2(
            [&res2, x](int iterations) {
                for (int i = 0; i < iterations; i++)
                    res2[i] = x - x;
            }, iterations);
    std::thread th3(
            [&res1, &res2](int iterations) {
                for (int i = 0; i < iterations; i++)
                    res1[i] + res2[i] - res1[i];
            }, iterations);

    th1.join();
    th2.join();
    th3.join();
    clock_t end = clock();
    double seconds = (double) (end - begin) / CLOCKS_PER_SEC;
    return seconds;
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