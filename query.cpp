#include "query.h"
Query::Query(){
    std::ifstream fin;
    fin.clear();
    fin.open(INPUTFILESQL.c_str());
    std::getline(fin, raw_query, ';');
}

void Query::processQuery(){
    //We want to process in the order FROM -> WHERE -> SELECT
    
}