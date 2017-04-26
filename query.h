#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
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
    string rawWhereLine;
};

struct OPERATOR{
    std::vector<string> arguments;
    std::string opType;
};


class Query{
public: 
    Query();
    Query(const string newraw_query);
    void getQuery();
    void printVector();
    bool endOfQuery(const string stringToCheck, const char charToEnd);
    void Algebra(Query query);
    void print();
    void printStack(std::stack<string> myStack);
    void queryTree(std::vector<Schema> schema);
    bool checkKeywords(const string keyword);
    WHERE whereStatement;
    FROM fromStatement;
    SELECT selectStatement;
    OPERATOR operatorStatement;
    string raw_query, nestedPortion;
    bool isNested;
    

private:
    std::queue<string> relAlg;
    std::stack<string> queryStack;

};



#endif /*QUERY_H*/
