#include "query.h"
Query::Query(){
    std::ifstream fin;
    fin.clear();
    fin.open(INPUTFILESQL.c_str());
    std::getline(fin, raw_query, ';');
}

bool Query::endOfQuery(const string stringToCheck){
    for(int i = 0; i < stringToCheck.length(); i++){
        if(stringToCheck[i] == ';')
            return true;

    }
    return false;

}

void Query::getQuery(){
    

    std::istringstream stringstream(raw_query);
    std::getline(stringstream, SELECTION, '\n');
    std::getline(stringstream, FROM, '\n');
    std::getline(stringstream, WHERE, '\n'); 
}