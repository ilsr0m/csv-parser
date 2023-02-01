#pragma once
#include <vector>
#include <string>

// just validator class
class Validator {
public:
    bool isdigit_str(const std::string str);

    bool isalpha_str(const std::string str);
};

// class csv validator
class CSVVAlidator : public Validator {
private:
    std::vector<std::vector<std::string>> data;

    bool check_id();

    bool check_col_headers();

    bool check_row_headers();

    bool check_cell();

public:
    CSVVAlidator() = default;

    explicit CSVVAlidator(std::vector<std::vector<std::string>> data);;

    ~CSVVAlidator() = default;

    // setter for data (matrix)
    void setData(std::vector<std::vector<std::string>> data);

    void validate();
};
