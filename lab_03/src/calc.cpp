#include <iostream>

float str_to_float(std::string str) {
    int minus_count = 0, dot_count = 0, comma_count = 0;
    // Проверяем, есть ли буквы.
    // Проверяем, сколько минусов, точек и запятых
    size_t size = str.size();
    for (size_t idx = 0; idx < size; idx++) {
        if ((minus_count > 1) || (dot_count > 1) || (comma_count > 1))
            throw "Incorrect input\n";
        char c = str[idx];
        if (c == '.')
            dot_count++;
        else if (c == ',')
            comma_count++;
        else if ((c == '-') && (idx == 0))
            minus_count++;
        else if (std::isdigit(c))
            continue;
        else
            throw "Incorrect input\n";
        }
    return std::stof(str);
}

float power(float x, int a) {
    if (a == 0)
        return 1;
    float tmp = 1;
    for (int i = 0; i < a; i++)
        tmp *= x;
    return tmp;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Incorrect input!\n";
        return 1;
    }
    try {
        float digit1 = str_to_float(argv[1]);
        char *oper = argv[2];
        float digit2 = str_to_float(argv[3]);
        switch (*oper) {
            case '+': {
                std::cout << digit1 + digit2 << std::endl;
                break;
            }
            case '-': {
                std::cout << digit1 - digit2 << std::endl;
                break;
            }
            case '^': {
                std::cout << power(digit1, digit2) << std::endl;
                break;
            }
            default: {
                std::cout << "Incorrect input(possible operands are '+', '-' and '^'\n";
                break;
            }
        }
    }
    catch (const char *s) {
        std::cout << s << std::endl;
    }
    return 0;
}
