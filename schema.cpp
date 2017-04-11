#include "schema.h"
Schema::Schema(){
    schemaName = "";
    numVar = 0;
    schemaList.clear();
}

//Checks to see if it is the end of the Schema
bool Schema::endOfSchema(const string stringToCheck){
    for(int i = 0; i < stringToCheck.length(); i++){
        if(stringToCheck[i] == ')')
            return true;
        
    }
    return false;
}

//Gets the input of the schema and parses it into its variables, and variable varType
//aka BID:integer = var:vartype
void Schema::getSchemaInput(const int numIter){
    int i = 0;
    string next, trashString;
    schemaVar tempVar;
    std::ifstream fin;
    fin.clear();
    fin.open(INPUTFILE.c_str());

    for(int i = 0; i < numIter - 1; i++){
        std::getline(fin, trashString, ';');
    }

    std::getline(fin, schemaName, '('); //Retrieves the name of the Schema
    do{
        schemaList.push_back(tempVar);
        if(i % 2 == 0){ //Gets the name of the variable up until ':'
            std::getline(fin, next, ':');
            schemaList[i >> 1].varName = next;
        }
        else {
            std::getline(fin, next, ',');
            schemaList[i >> 1].varType = next;
        }
        i++;
    } while(!endOfSchema(next));

}

string Schema::getSchemaName(){
    return schemaName;
}

void Schema::renameSchema(const string toRename){
    schemaName = toRename;
}