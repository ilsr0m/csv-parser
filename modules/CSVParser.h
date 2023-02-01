#pragma once
#include "expression.h"
#include <vector>
#include <string>

class CSVParser {
private:
    // CSVExpressionParser
    class CSVExpressionParser {
    private:
        std::vector<std::vector<std::string>> data;
        // ------------------- //
        // ------------------- //
        // ------------------- //
        // ------------------- //
        // ------------------- //

        // CSVCellAdressParser
        class CSVCellAdressParser {
        private:
            std::vector<std::vector<std::string>> data;

            std::string get_row(std::string);

            std::string get_column(std::string);

            bool get_integer(std::string, int &);
        public:
            CSVCellAdressParser();
            explicit CSVCellAdressParser(std::vector<std::vector<std::string>> data);
            ~CSVCellAdressParser();
            void parse(const std::vector<std::string> &, std::vector<int> &);
        };

        // ------------------- //
        // ------------------- //
        // ------------------- //
        // ------------------- //
        // ------------------- //

        char get_operator(std::string);

        std::vector<std::string> get_exprs();

        std::vector<std::string> get_adresses(std::string);

        CSVCellAdressParser *csvCellAdrParser = nullptr;
    public:
        CSVExpressionParser();

        explicit CSVExpressionParser(std::vector<std::vector<std::string>> data);

        ~CSVExpressionParser();

        void parse(std::vector<Expression> &);
    };

    // ------------------- //
    // ------------------- //
    // ------------------- //
    // ------------------- //
    // ------------------- //

public:
    CSVParser();

    ~CSVParser();

    static void parse(std::vector<std::vector<std::string>> &);
};

