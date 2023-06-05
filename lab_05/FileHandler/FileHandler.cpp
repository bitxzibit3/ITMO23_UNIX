//
// Created by timur on 02.06.23.
//

#include "FileHandler.h"

FileHandler::FileHandler() {
    std::cout << "Error occured! Please, enter a filename!";
}

FileHandler::FileHandler(const std::string& p) {
    this->path = p;
}

int FileHandler::write(std::string s) {
    std::ofstream fout;
    fout.open(this->path, std::ofstream::app);
    if (!fout.is_open()) {
        std::cout << "File can not be opened\n";
        return -1;
    }
    fout << s << std::endl;
    fout.close();
    return 0;
}

int FileHandler::write(std::vector<std::string> v) {
    std::ofstream fout;
    fout.open(this->path, std::ofstream::app);
    if (!fout.is_open()) {
        std::cout << "File can not be opened\n";
        return -1;
    }
    for (auto s: v)
        fout << s << std::endl;
    fout.close();
    return 0;
}

int FileHandler::write(float num) {
    std::ofstream fout;
    fout.open(this->path, std::ofstream::app);
    if (!fout.is_open()) {
        std::cout << "File can not be opened\n";
        return -1;
    }
    fout << num << std::endl;
    fout.close();
    return 0;
}
