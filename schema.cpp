#include "schema.h"
Schema::Schema(){
    schemaName = "";
    numVar = 0;
    schemaList.clear();
}

bool Schema::endOfSchema(const string stringToCheck){
    for(int i = 0; i < stringToCheck.length(); i++){
        if(stringToCheck[i] == ')')
            return true;
        
    }
    return false;
}

void Schema::getSchemaInput(){
    int i = 0;
    string next;
    schemaVar tempVar;
    std::ifstream fin;

    fin.clear();
    fin.open(INPUTFILE.c_str());
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
