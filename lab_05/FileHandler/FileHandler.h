//
// Created by timur on 02.06.23.
//

#ifndef LAB_05_FILEHANDLER_H
#define LAB_05_FILEHANDLER_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

class FileHandler {
public:
    std::string path;
    FileHandler();
    FileHandler(const std::string&);
    int write(std::string);
    int write(float);
    int write(std::vector<std::string>);
};

#endif //LAB_05_FILEHANDLER_H
