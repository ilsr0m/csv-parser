#include  <iostream>
#include "modules/error.h"
#include "modules/csvfilereader.h"
#include "modules/CSVParser.h"
#include "modules/print.h"


using namespace std;

int main() {
    cout << "Input file path (.csv): \n";
    string filepath;
    getline(cin, filepath);
    cout << endl;
    // file path of .csv
    // future data from given file path
    vector<vector<string>> data;
    try {
        // extract data
        CSVFileReader::read(filepath, data);
    }
    catch (File_error &e) { // error occurred
        cout << "Error: " << e << endl;
    }
    // parse part
    auto parser = new CSVParser();
    try {
        parser->parse(data);
        print(data);
    }
    catch (Runtime_error &e) {
        cout << "Error: " << e << endl;
    }
    catch (Syntax_error &e) {
        cout << "Error: " << e << endl;
    }
    delete parser;


}
