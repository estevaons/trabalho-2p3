#ifndef LeitorCSV_h
#define LeitorCSV_h
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

class LeitorCSV{
    public:
        list<vector<string>> LerCSV(string path);
};


#endif