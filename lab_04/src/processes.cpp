#include <iostream>
#include <iomanip>
#include <sys/wait.h>
#include <unistd.h>

int f1(int x) {
    return x * x - x * x  + 4 * x  - 5 * x + x + x;
}

int f2(int x) {
    return x - x;
}

int f3(int x, int y) {
    return x + y - x;
}

int main(int argc, char *argv[]) {
    int COUNT = 1000;
    int x = 1;
    double time = 0;
    int iterations = std::stoi(argv[1]);
    for (int k = 0; k < COUNT; k++) {
        int res1[iterations],
            res2[iterations];
        clock_t begin = clock();
        pid_t id1 = fork();
        if (id1 == 0) {
            //
            for (int i = 0; i < iterations; i++)
                res1[i] = f1(x);
            return 0;
        }
        pid_t id2 = fork();
        if (id2 == 0) {
            for (int i = 0; i < iterations; i++)
                res2[i] = f2(x);
            return 0;
        }
        for (int i = 0; i < iterations; i++) {
            res1[i] + res2[i] - res1[i];
        }
        int stat_loc;
        waitpid(id1, &stat_loc, 0);
        waitpid(id2, &stat_loc, 0);
        clock_t end = clock();
        double seconds = (double) (end - begin) / CLOCKS_PER_SEC;
        time += seconds;
    }
    double t = time / COUNT;
    std::cout << std::fixed << std::setprecision(6) << "Time for " << iterations << " : " << t << " s.\n";
    return 0;
}