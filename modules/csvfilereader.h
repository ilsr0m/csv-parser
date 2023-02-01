//
// Created by 1 on 28.01.2023.
//
#pragma once

#include <vector>
#include <string>

// a class represents data from cvs file
class CSVFileReader {
public:
    CSVFileReader();

    ~CSVFileReader();

    // function records data from given file path
    static void read(const std::string& path, std::vector<std::vector<std::string>> &data);
};