#include "query.h"
using namespace std;

Query::Query(){
    std::ifstream fin;
    fin.clear();
    fin.open(INPUTFILESQL.c_str());
    std::getline(fin, raw_query, ';');
    raw_query.append(";");

}

bool Query::checkKeywords(const string keyword){
    for(int i = 0; i < 18; i++){ //18 is the amount of keywords, don'tbe a dumbass fis this later'
        if(keyword.find(KEYWORDS[i]))
          return true;
    }
    return false;
}

bool Query::endOfQuery(const string stringToCheck, const char charToEnd){
    for(unsigned int i = 0; i < stringToCheck.length(); i++){
        if(stringToCheck[i] == charToEnd)
            return true;

    }
    return false;

}

void Query::getQuery(){
    std::istringstream iss(raw_query);
    string selectLine, fromLine, whereLine, extraLine, tempString, trashString;
    int newlineCounter = 0;
    int embeddedCounter = 0;
    string next;
    do{
        if(newlineCounter == 0){
            std::getline(iss,selectLine, '\n');
            std::istringstream selectStream(selectLine);
            std::getline(selectStream, next, ' ');
            while(selectStream >> next){
              selectStatement.arguments.push_back(next);
            }
        }
        else if(newlineCounter == 1){
            std::getline(iss,fromLine, '\n');
            std::istringstream fromStream(fromLine);
            std::getline(fromStream, next, ' ');
            fromStatement.arguments.push_back(next);
            while(fromStream >> next){
              fromStatement.arguments.push_back(next);
            }
        }
        else if(newlineCounter == 2){
            std::getline(iss,whereLine, '\n');
            std::istringstream whereStream(whereLine);
            std::getline(whereStream, next, ' ');
            whereStatement.arguments.push_back(next);
            while(whereStream >> next){
              whereStatement.arguments.push_back(next);
            }
        }
        else{
            std::getline(iss, extraLine, '\n');
            std::istringstream extraStream(extraLine);
            std::getline(iss, next, ' ');
            while(extraStream >> next){
              operatorStatement.arguments.push_back(next);
            }

        }
        newlineCounter++;
    } while(!endOfQuery(next, ';'));

}


void Query::print()
{
  string temp;
  while(!relAlg.empty()){
    temp = relAlg.front();
    relAlg.pop();
    cout << temp << " ";
  }

  cout << endl;
  return;
}

void Query::printTree(const string toPrint){
  std::cout << "-------------------\n"
            << "|                 |\n|\t"
            << toPrint << std::endl
            << "|                 |\n"
            << "-------------------\n";
}

void Query::Algebra(){
  string arg = "";
  int counter = 0;
  for(int i = 0; i < selectStatement.arguments.size(); i++){
    arg = selectStatement.arguments[i];
    if(i == 0){
      relAlg.push("[PROJECT]");
      relAlg.push(selectStatement.arguments[i]);
    }
    else if(arg == "COUNT" || arg == "AVERAGE" || arg == "MIN" || arg == "MAX"){
      relAlg.push("[F]");
      relAlg.push(selectStatement.arguments[i]);
      relAlg.push(selectStatement.arguments[i+1]);
      i++;
    }
    else
      relAlg.push(selectStatement.arguments[i]);
  }
  for(int i = 0; i < fromStatement.arguments.size(); i++){

  }
  for(int i = 0; i < whereStatement.arguments.size(); i++){
    if(i == 0)
      relAlg.push("[SELECTION] (");
    
    else if(whereStatement.arguments[i] == "SELECT") //NESTED QUERY
      cout << "NOT NOW"; //Probably need to split the whereStatement vector apart from what it is now, 
                         //and redistribute it through the getQuery function or something like that.
    
    else if(whereStatement.arguments[i] == "AND")
      relAlg.push("[JOIN]");
    
    else if(whereStatement.arguments[i] == "IN" ||
            whereStatement.arguments[i] == "CONTAINS" ||
            whereStatement.arguments[i] == "INTERSECT")
      relAlg.push("[INTERSECTION]");
    
    else if(whereStatement.arguments[i] == "HAVING" ||
            whereStatement.arguments[i] == "EXISTS")
      relAlg.push("[DIVIDE]");
    
    else if(whereStatement.arguments[i] == "EXCEPT" ||
            whereStatement.arguments[i] == "NOTEXISTS")
      relAlg.push("[SET DIFFERENCE]");
    
    else if(whereStatement.arguments[i] == "GROUP BY")
    {                             //This needs some fixing up. it will replace[PROJECT] at the 
      queue<string> temp = relAlg;//front. Also, there may be more than one attribute. Could be 
      arg = whereStatement.arguments[i+1];  //a problem that may be difficult to fix.
      for(unsigned int f = 0; f < temp.size(); f++)
        relAlg.pop();
      relAlg.push(arg);
      for(unsigned int c = 0; c < temp.size(); c++){
        arg = temp.front();
        relAlg.push(arg);
      }
    }

    else if(whereStatement.arguments[i] == "UNION")
      relAlg.push("[UNION]");

    else{
      relAlg.push("(");
      relAlg.push(whereStatement.arguments[i]);
      //print();
      relAlg.push(")");
    }
    //printVector();
  }
  cout << endl;
  relAlg.push(")");
  print();

}

void Query::queryTree(std::vector<Schema> schemaList){
  for(int i = 0; i < schemaList.size(); i++){
    std::cout << schemaList[i].getSchemaName();
    for(int j = 0; j < fromStatement.arguments.size(); j++){
      //std::cout << "FROM: " << fromStatement.arguments[i] << std::endl;
      //std::cout << "SCHEMANAME: " << schemaList[i].getSchemaName() << std::endl;
      if(fromStatement.arguments[j] == schemaList[i].getSchemaName()){
        printTree(fromStatement.arguments[j]);
      }
    }
  }
}



