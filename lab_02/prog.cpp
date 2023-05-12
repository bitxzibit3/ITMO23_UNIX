#include <iostream>
#include <time.h>

int foo(int x = 1) {
	return x * x - x * x + x * 4 - x * 5 + x + x;
}

int natural_digit_length(int x) {
	int counter = 0;
	if (x < 0)
		return -1;
	while (x) {
		x /= 10;
		counter += 1;
	}
	return counter;
}

int main() {
	std::string n_str, x_str;
	bool flag = true;
	while(flag) {
		std::cout << "Enter n: ";
		std::cin >> n_str;
		int n = 0;
		try {
			n = std::stoi(n_str);
		}
		catch (std::invalid_argument e) {
			std::cout << "n should be a natural digit\n";
			return 1;
		}
		if (natural_digit_length(n) != n_str.size()) {
			std::cout << "n should be a natural digit\n";
			return 1;
		}
		time_t begin = clock();
		for (int i = 0; i < n; i++)
			foo();
		time_t end = clock();
    		double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Done: " << n << " iterations, time: " << seconds;
		std::cout << "\nDo you want to retry? Type 'q' to quit. ";
		std::string ans;
		std::cin >> ans;
		flag = (ans != "q");
	}
	return 0;
}
