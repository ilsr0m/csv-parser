#include "csvfilereader.h"
#include "error.h"
#include <fstream>
#include <sstream>

CSVFileReader::CSVFileReader() = default;

CSVFileReader::~CSVFileReader() = default;

// copy data form given file
void CSVFileReader::read(const std::string& path, std::vector<std::vector<std::string>> &data) {
    std::ifstream file(path);

    // in case file does not exist
    if (file.fail())
        throw File_error{"file does not exist"};
    // extension check

    if (path.substr(path.find_last_of(".") + 1) != "csv")
        throw File_error{"no '.csv' extension"};

    std::string tokens;            // temporary token line
    std::string token;             // temporary token
    std::vector<std::string> temp; // temporary row line

    if (file.is_open()) {
        // get each row
        while (getline(file, tokens)) {
            std::istringstream it(tokens);
            // get each cell
            while (getline(it, token, ','))
                temp.push_back(token);
            data.push_back(temp);
            temp.clear();
        }
    } else
        throw File_error{"impossible to open file"};

    // if empty file
    if (data.empty())
        throw File_error{"file is empty"};
}
