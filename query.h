#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using std::string;
const string INPUTFILESQL = "testinputSQL.dat";
class Query{
public: 
    Query();
    void processQuery();

private:
    string raw_query;
    std::vector<string> SELECTION;
    std::vector<string> FROM;
    std::vector<string> WHERE;

};



#endif /*QUERY_H*/