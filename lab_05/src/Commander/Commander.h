//
// Created by timur on 02.06.23.
//

#ifndef LAB_05_COMMANDER_H
#define LAB_05_COMMANDER_H

#include <thread>
#include <string>
#include "../FileHandler/FileHandler.h"

class Commander {
public:
    std::vector<std::thread> threads;
    std::vector<std::string> commands;
    FileHandler logfile;
    Commander();
    Commander(std::string);
    void make_commands(std::vector<std::string>);

private:
    // Helpers
    int command_type(std::string);
    std::string get_out_argument(std::string);
    bool is_numeric(std::string);
    std::vector<std::string> split(std::string, std::string);
    std::pair<int, int> find_brackets(std::string);
    std::string trim(std::string);
    std::string delete_spaces(std::string);
    std::vector<std::string> split_operation(std::string);
    std::string expression_handling(std::string);
    std::vector<int> extract_loop_info(std::string);

    // Main part
    float execute_calculation(std::string);
    void make_loop(int, int, std::string, int);
    void console_print(std::string);
    void file_print(std::string, std::string);
    void make_command(std::string);
};


void log_operation(FileHandler, std::string, std::thread::id);

#endif //LAB_05_COMMANDER_H
