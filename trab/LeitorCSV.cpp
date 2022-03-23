#include"LeitorCSV.h"
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

list<vector<string>> LeitorCSV::LerCSV(string path){
    int contador = 0;

    string file_contents;
    list<vector<string>> csv_contents;
    file_contents = readFileIntoString(path);
    istringstream iss(file_contents);
    string line;
    while (getline(iss, line)) {
        istringstream line_stream(line);
        string cell;
        vector<string> csv_row;

        while (getline(line_stream, cell, ',')) {
            csv_row.push_back(cell);
        }
        csv_contents.push_back(csv_row);
    }
    return csv_contents;
}