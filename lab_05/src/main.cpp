#include "Commander/Commander.h"

std::vector<std::string> exec_from_file(std::string filename) {
    std::ifstream in;
    in.open(filename);
    std::string s;
    std::vector<std::string> commands;
    while (!in.eof()) {
        in >> s;
        commands.emplace_back(s);
    }
    return commands;
}

int main() {
    auto commands = exec_from_file("../src/source.txt");
    Commander commander("../logs/log.txt");
    commander.make_commands(commands);
    return 0;
}
