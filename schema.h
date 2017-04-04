#ifndef SCHEMA_H
#define SCHEMA_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using std::string;
const string INPUTFILE = "testinput.dat";
const int MAX_NUM_SCHEMA = 50;


struct schemaVar{
    string varName;
    string varType;
};




class Schema{
public:
    Schema();
    void getSchemaInput();
    string getSchemaName();
    bool endOfSchema(const string stringToCheck);
private:
    string testVar;
    string schemaName;
    int numVar;
    std::vector<schemaVar> schemaList;
};


#endif /*SCHEMA_H*/