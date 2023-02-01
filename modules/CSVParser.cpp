#include "CSVParser.h"
#include "simplearithmetics.h"
#include "error.h"
#include <regex>
#include "csvvalidator.h"

//CSVParser
CSVParser::CSVParser() = default;

CSVParser::~CSVParser() = default;

// parsing data
void CSVParser::parse(std::vector<std::vector<std::string>> &data) {
    std::vector<Expression> expressions;
    auto *valid = new CSVVAlidator(data);
    valid->validate();
    auto csvExprParser = new CSVExpressionParser(data);
    csvExprParser->parse(expressions);
    if (expressions.empty()) return;
    std::vector<int> results;
    for (const auto &e: expressions) {
        int res = SimpleArithmetics::calculate(e);
        results.emplace_back(res);
    }
    for (auto &i: data) {
        for (auto &j: i) {
            if (j[0] == '=') {
                if (results.empty()) return;
                j.clear();
                j += std::to_string(*results.begin());
                results.erase(results.begin());
            }
        }
    }
    delete csvExprParser;
}

// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //

// CSVExpressionParser
CSVParser::CSVExpressionParser::CSVExpressionParser() = default;

CSVParser::CSVExpressionParser::CSVExpressionParser(std::vector<std::vector<std::string>> data) {
    this->data = std::move(data);
    csvCellAdrParser = new CSVCellAdressParser(this->data);
}

CSVParser::CSVExpressionParser::~CSVExpressionParser() {
    delete csvCellAdrParser;
}

char CSVParser::CSVExpressionParser::get_operator(std::string expr) {
    int found = expr.find_first_of("-+/*");
    int check_found = expr.find_last_of("-+/*");
    if (found != check_found)
        throw Syntax_error{"more than one operator"};
    if (found == std::string::npos) {
        throw Syntax_error{"no operators in cell expression found"};
    }
    //throw Syntax_error{"no operators in cell expression found"};
    return expr[found];
}

std::vector<std::string> CSVParser::CSVExpressionParser::get_exprs() {
    std::vector<std::string> exprs;
    // push expressions in vector
    for (auto i: data)
        for (auto j: i)
            if (j[0] == '=')
                exprs.push_back(j);

    return exprs;
}

std::vector<std::string> CSVParser::CSVExpressionParser::get_adresses(std::string expr) {
    // remove all spaces in order to be sure in correctness of following operations
    std::remove_if(expr.begin(), expr.end(), isspace);
    // delete '='
    expr.erase(0, 1);
    // delimiting operand adresses by operators using regular expression
    std::regex reg("[^\\s-*/+]+");

    auto words_begin = std::sregex_iterator(expr.begin(), expr.end(), reg);
    auto words_end = std::sregex_iterator();

    // if no mathces
    if (words_begin == std::sregex_iterator())
        throw Syntax_error{"no cell address matches found"};

    // vector of extracted operand addresses
    std::vector<std::string> adresses;

    // get addresses
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        adresses.push_back((*i).str());

    // in case more or less than 2 operand addresses extracted
    if (adresses.size() != 2)
        throw Syntax_error{"operand count in cell expression is invalid\n Must be 2 operands only"};

    return adresses;
}

void CSVParser::CSVExpressionParser::parse(std::vector<Expression> &num_exprs) {
    // get vector of expressions
    std::vector<std::string> exprs = get_exprs();
    // delimiters - operators
    // loop expressions one by one
    for (const auto &ex: exprs) {
        char op = get_operator(ex);
        // get adresses
        std::vector<std::string> adresses = get_adresses(ex);
        // parse adresses into numeric operands
        std::vector<int> opers;
        if (!csvCellAdrParser) return;
        csvCellAdrParser->parse(adresses, opers);
        if (opers.empty()) return;
        std::tuple<int, int> tup = std::tuple<int, int>{opers[0], opers[1]};
        // allocate Expression
        // Expression e = Expression(tup, op);
        num_exprs.emplace_back(tup, op);
    }
}

// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //
// ------------------------------------- //

CSVParser::CSVExpressionParser::CSVCellAdressParser::CSVCellAdressParser() = default;

CSVParser::CSVExpressionParser::CSVCellAdressParser::CSVCellAdressParser(std::vector<std::vector<std::string>> data) {
    this->data = std::move(data);
}

CSVParser::CSVExpressionParser::CSVCellAdressParser::~CSVCellAdressParser() = default;

std::string CSVParser::CSVExpressionParser::CSVCellAdressParser::get_column(std::string val) {
    std::string col;
    for (char &it: val)
        if (isalpha(it))
            col.push_back(it);
    return col;
}

std::string CSVParser::CSVExpressionParser::CSVCellAdressParser::get_row(std::string val) {
    std::string row;
    for (char &it: val)
        if (isdigit(it))
            row.push_back(it);
    return row;
}

bool CSVParser::CSVExpressionParser::CSVCellAdressParser::get_integer(std::string adrr, int &num) {
    bool flag = !Validator().isalpha_str(adrr);
    if (flag) num = std::atoi(adrr.c_str());
    return flag;
}

void CSVParser::CSVExpressionParser::CSVCellAdressParser::parse(const std::vector<std::string> &addresses,
                                                                std::vector<int> &values) {

    // split adress into row and column
    std::string row, col;
    for (const auto &adrr: addresses) {
        int num;
        // if address has all integers - it is operand
        if (get_integer(adrr, num)) {
            values.push_back(num);
            continue;
        }
        // split address into row and column
        row = get_row(adrr);
        col = get_column(adrr);
        // look for the concrete value
        for (auto &i: data) {
            for (int j = 0; j < i.size(); j++) {
                if (i[0] == row && data[0][j] == col) {
                    // check if not expression
                    for (auto c: i[j]) {
                        if (isalpha(c)) throw Syntax_error{"desired address has an expression"};
                    }
                    num = std::atoi(i[j].c_str());
                    values.push_back(num);
                }
            }
        }
    }
    if (addresses.size() != values.size()) throw Syntax_error{"wrong cell address given"};
}




