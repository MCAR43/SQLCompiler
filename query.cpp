#include "query.h"
Query::Query(){
    std::ifstream fin;
    fin.clear();
    fin.open(INPUTFILESQL.c_str());
    std::getline(fin, raw_query, ';');
    raw_query.push_back(';');
}

bool Query::endOfQuery(const string stringToCheck){
    for(int i = 0; i < stringToCheck.length(); i++){
        if(stringToCheck[i] == ';')
            return true;

    }
    return false;

}

void Query::getQuery(){
    std::istringstream iss(raw_query);
    int newlineCounter = 0;
    bool loopCondition = false;
    string next;
    do{
        if(newlineCounter == 0){
            std::getline(iss, SELECTION, '\n');
            next = SELECTION;
        }
        else if(newlineCounter == 1){
            std::getline(iss, FROM, '\n');
            next = FROM;
        }
        else if(newlineCounter == 2){
            std::getline(iss, WHERE, '\n');
            next = WHERE;
        }
        newlineCounter++;
            

        
    } while(!endOfQuery(next));

}

void Query::processSelect(){

}

Selection::Selection(){
    std::cout << selectionSymbol;
}
