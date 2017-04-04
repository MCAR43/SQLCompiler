#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "schema.h"
using std::string;
const string INPUTFILESQL = "testinputSQL.dat";
const string KEYWORDS[18] = {"SELECT", "FROM", "WHERE", "AND", "AS", "INTERSECT", "UNION", "IN", "GROUP BY", "MAX", "MIN",
"AVERAGE", "HAVING", "EXCEPT", "COUNT", "EXISTS", "NOTEXISTS", "CONTAINS"};
struct SELECT{
    std::vector<string> arguments;
};

struct FROM{
    std::vector<string> arguments;
};

struct WHERE{
    std::vector<string> arguments;
};

struct OPERATOR{
    std::vector<string> arguments;
};


class Query{
public: 
    Query();
    void printVector();
    bool endOfQuery(const string stringToCheck, const char charToEnd);
    void Algebra();
    void print();
    void printTree(const string toPrint);
    void queryTree(std::vector<Schema> schema);
    bool checkKeywords(const string keyword);
    WHERE whereStatement;
    FROM fromStatement;
    SELECT selectStatement;
    OPERATOR operatorStatement;
    

private:
    string raw_query;
    std::queue<string> relAlg;

};



#endif /*QUERY_H*/
