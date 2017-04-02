#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using std::string;
const string INPUTFILESQL = "testinputSQL.dat";
const string KEYWORDS[18] = {"SELECT", "FROM", "WHERE", "AND", "AS", "INTERSECT", "UNION", "IN", "GROUP BY", "MAX", "MIN",
"AVERAGE", "HAVING", "EXCEPT", "COUNT", "EXISTS", "NOTEXISTS", "CONTAINS"};



class Query{
public: 
    Query();
    void getQuery();
    bool endOfQuery(const string stringToCheck);
    void processSelect();
    

private:
    string raw_query;
    string SELECTION, FROM, WHERE;
};

class Selection{
public:
    Selection();

private:
    std::vector<string> arguments;
    char selectionSymbol;
};




#endif /*QUERY_H*/