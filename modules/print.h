#pragma once
#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::vector<std::string>> &);

// function prints file data
void print(const std::vector<std::vector<std::string>> &data) {
    for (const auto &row: data) {
        int counter = 0;
        for (const auto &cell: row) {
            counter++;
            std::cout << cell;
            if (counter != row.size()) std::cout << ",";
        }
        std::cout << std::endl;
    }
}
