#include "csvvalidator.h"
#include "error.h"
#include <regex>

// Validator
bool Validator::isdigit_str(const std::string str) {
    return std::regex_match(str, std::regex("^[0-9]+$"));
}

bool Validator::isalpha_str(const std::string str) {
    return std::regex_match(str, std::regex("^[A-Za-z]+$"));
}

// CSV validtor class

bool CSVVAlidator::check_cell() {
    for (int i = 1; i < data.size(); i++) {
        for (int j = 1; j < data[i].size(); j++) {
            char first = data[i][j][0];
            if(first != '=' && !isdigit(first) && first !='-') {
                return false;
            }
        }
    }
    return true;
}

bool CSVVAlidator::check_row_headers() {
    for (int i = 1; i < data.size(); i++)
        if (!isdigit_str(data[i][0]))
            return false;
    return true;
}

void CSVVAlidator::validate() {
    if (!check_id()) throw Syntax_error{"csv file ID must be empty"};
    if (!check_col_headers())
        throw Syntax_error{"invalid column header/headers\nMake sure it contains latin characters only"};
    if (!check_row_headers())
        throw Syntax_error{"invalid row header/headers\nMake sure it contains digits only"};
    if (!check_cell()) throw Syntax_error{"invalid cell values"};
}

void CSVVAlidator::setData(std::vector<std::vector<std::string>> data) { this->data = std::move(data); }

CSVVAlidator::CSVVAlidator(std::vector<std::vector<std::string>> data) : data{std::move(data)} {}

bool CSVVAlidator::check_col_headers() {
    for (int i = 1; i < data[0].size(); i++) {
        // if row contains non alpha
        if (!isalpha_str(data[0][i]))
            return false;
    }
    return true;
}

bool CSVVAlidator::check_id() { return data[0][0].empty(); }
