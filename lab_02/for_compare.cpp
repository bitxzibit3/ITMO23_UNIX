#include <iostream>
#include <fstream>
#include <time.h>

int foo(int x = 1) {
    return x * x - x * x + x * 4 - x * 5 + x + x;
}

double time_counter(int n) {
    time_t begin = clock();
    for (int i = 0; i < n; i++)
        foo();
    time_t end = clock();
    double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
    return seconds;
}

int main() {
    int N[] = {1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    std::ofstream out;
    out.open("cpp_results.txt");
    for (auto n: N) {
        double ans = time_counter(n);
        out << n << " - " << ans << "\n";
    }
    return 0;
}
