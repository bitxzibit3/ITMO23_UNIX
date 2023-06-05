//
// Created by timur on 02.06.23.
//

#include <sstream>
#include "Commander.h"


Commander::Commander() {
    this->threads = std::vector<std::thread> (0);
    this->commands = std::vector<std::string> (0);
    std::string log_file = "log.txt";
    this->logfile = FileHandler(log_file);
}


Commander::Commander(std::string logfilename) {
    this->threads = std::vector<std::thread> (0);
    this->commands = std::vector<std::string> (0);
    this->logfile = FileHandler(logfilename);
}

void Commander::make_commands(std::vector<std::string> commands) {
    /* Мы тут получаем команду, понимаем, что за команда, выполняем соотв. команду
     Доступные команды:
          1) цикл:            LOOP(begin, end, step = 1)
          2) вывод в консоль: PRINT(expression)
          3) вывод в файл:    FPRINT(expression)
          4) + - / *:         operand sign operand
          Пример кода:
          LOOP(1,5)
              PRINT(3+6);
          LOOP(3,6)
              FPRINT(1*2);
    */
    // TODO
    size_t size = commands.size();
    for (size_t i = 0; i < size; i++) {
        std::string command = commands[i];
        int ct = command_type(command);
        switch (ct) {
            case 1: {
                i++;
                std::string command_to_execute = commands[i];
                std::string argument = get_out_argument(command);
                std::vector<int> args = extract_loop_info(argument);
                make_loop(args[0], args[1], command_to_execute, args[2]);
                break;
            }
            default: {
                make_command(command);
                break;
            }
        }
    }
    size_t threads_amount = threads.size();
//    std::cout << "{" << threads_amount << "}";
    for (int i = 0; i < threads_amount; i++)
        threads[i].join();
}

int Commander::command_type(std::string s) {
    // 1 - цикл
    auto npos = std::string::npos;
    if (s.find("LOOP") != npos)
        return 1;
    // 3 - fprint
    if (s.find("FPRINT") != npos)
        return 3;
    // 2 - print
    if (s.find("PRINT") != npos)
        return 2;
    // 4 - операция
    std::string signs = "+-*/";
    for (auto c: signs) {
        if (s.find(c) != npos)
            return 4;
    }
    // 5 - просто число(например, для вывода)
    if (is_numeric(s))
        return 5;
    return 0;
}

 std::string Commander::get_out_argument(std::string s) {
    auto brackets = find_brackets(s);
    int left = brackets.first, right = brackets.second;
    return s.substr(left + 1, right - left - 1);
}

bool Commander::is_numeric(std::string s) {
    for (auto c: s)
        if ((c < '0') || (c > '9'))
            return false;
    return true;
}

std::vector<std::string> Commander::split(std::string s, std::string delim) {
    size_t begin_idx = 0;
    size_t delim_idx = s.find(delim);
    std::vector<std::string> vec;
    while(delim_idx != std::string::npos) {
        std::string part = s.substr(begin_idx, delim_idx - begin_idx);
        vec.emplace_back(part);
        begin_idx = delim_idx + 1;
        delim_idx = s.find(delim, delim_idx + 1);
    }
    vec.emplace_back(s.substr(begin_idx));
    return vec;
}

std::pair<int, int> Commander::find_brackets(std::string s) {
    size_t left_bracket = s.find('(');
    size_t right_bracket = s.find(')');
    return {left_bracket, right_bracket};
}


float Commander::execute_calculation(std::string s) {

    std::string command = delete_spaces(s);
    auto splitted = split_operation(command);

    if (splitted.size() != 3) {
        std::cout << "Invalid expression";
        exit(1);
    }
    if (!is_numeric(splitted[0]) || !is_numeric(splitted[1])) {
        std::cout << "Invalid expression";
        exit(1);
    }
    float x = std::stof(splitted[0]), y = std::stof(splitted[1]);
    std::cout << "x = " << x << ", y = " << y << std::endl;
    switch(splitted[2][0]) {
        case '+': {
            float res;
            threads.emplace_back(std::thread([&res, this, command](float x, float y)
                {
                    std::stringstream ss;
                    ss << std::this_thread::get_id();
                    uint64_t id = std::stoull(ss.str());
                    log_operation(this->logfile, command, id);
                    res = x + y;
                }, x, y));
            return res;
        }

        case '-': {
            float res;
            threads.emplace_back([&res, this, command](float x, float y)
                {
                    std::stringstream ss;
                    ss << std::this_thread::get_id();
                    uint64_t id = std::stoull(ss.str());
                    log_operation(this->logfile, command, id);
                    res = x - y;
                }, x, y);
            return res;
        }

        case '*': {
            float res;
            threads.emplace_back([&res, this, command](float x, float y)
                {
                    std::stringstream ss;
                    ss << std::this_thread::get_id();
                    uint64_t id = std::stoull(ss.str());
                    log_operation(this->logfile, command, id);
                    res = x * y;
                }, x, y);
            return res;
        }

        case '/': {
            if (y == 0) {
                std::cout << "Division by zero!";
                exit(1);
            }
            float res;
            threads.emplace_back([&res, this, command](float x, float y)
                {
                    std::stringstream ss;
                    ss << std::this_thread::get_id();
                    uint64_t id = std::stoull(ss.str());
                    log_operation(this->logfile, command, id);
                    res = x / y;
                }, x, y);
            return res;
        }

        default: {
            std::cout << "Invalid expression";
            exit(1);
        }

    }
}

std::string Commander::trim(std::string s) {
    int left_idx = 0, right_idx = s.size() - 1;
    while (s[left_idx] == ' ')
        left_idx++;
    while (s[right_idx] == ' ')
        right_idx--;
    return s.substr(left_idx, right_idx - left_idx + 1);
}

std::string Commander::delete_spaces(std::string s) {
    auto t = trim(s);
    std::string res;
    for (char c: t) {
        if (c != ' ')
            res += c;
    }
    return res;
}

std::vector<std::string> Commander::split_operation(std::string s) {
    std::string signs = "+-*/";
    std::string finded_sign = " ";
    for (char sign: signs)
        if (s.find(sign) != std::string::npos) {
            finded_sign = sign;
            break;
        }
    auto splitted = split(s, finded_sign);
    splitted.emplace_back(finded_sign);
    return splitted;
}

void Commander::make_loop(int begin, int end, std::string command, int step = 1) {
    for (int i = begin; i <= end;) {
        make_command(command);
        i += step;
    }
}

void Commander::console_print(std::string expression) {
    int ct = command_type(expression);
    switch (ct) {
        case 4: {
            std::cout << execute_calculation(expression) << std::endl;
            return;
        }
        default: {
            std::cout << expression << std::endl;
            return;
        }
    }
}

void Commander::file_print(std::string filename, std::string expression) {
    int ct = command_type(expression);
    if ((ct != 0) && (ct < 4)) {
        std::cout << "Error";
        exit(1);
    }
    FileHandler f(filename);
    std::string to_write = expression_handling(expression);
    f.write(to_write);
}

std::string Commander::expression_handling(std::string expression) {
    int ct = command_type(expression);
    switch (ct) {
        case 4: {
            float x = execute_calculation(expression);
            std::string s = std::to_string(x);
            return s;
        }
        default:
            return expression;
    }
}

void Commander::make_command(std::string command) {
    int ct = command_type(command);
    std::string argument = get_out_argument(command);
//    std::cout << "{" << ct << "}{" << argument << "}";
    switch(ct) {
        case 2: {
            console_print(argument);
            break;
        }
        case 3: {
            auto vec = split(argument, ",");
            std::string filename = vec[0].substr(1, vec[0].size() - 2);
            if (vec.size() != 2) {
                std::cout << "Error";
                exit(1);
            }
            file_print(filename, vec[1]);
            break;
        }
        default: {
            std::cout << "Error";
            exit(1);
        }
    }
}

std::vector<int> Commander::extract_loop_info(std::string arg) {
    auto args = split(arg, ",");
    if (args.size() == 2)
        args.emplace_back("1");
    if (args.size() != 3) {
        std::cout << "Loop error";
        exit(1);
    }
    std::vector<int> int_args;
    for (auto arg: args)
        int_args.emplace_back(std::stoi(arg));
    return int_args;
}

void log_operation(FileHandler logfile, std::string operation, uint64_t thread_id) {
//    std::cout << "{" << thread_id << "}";
    std::string info = operation;
    info += " executed in thread with id ";
    info += std::to_string(thread_id);
    info += "\n";
    logfile.write(info);
}