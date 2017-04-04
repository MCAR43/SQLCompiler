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
    string selectLine, fromLine, whereLine, tempString, trashString;
    int newlineCounter = 0;
    int embeddedCounter = 0;
    string next;
    do{
        if(newlineCounter == 0){
            std::getline(iss,selectLine, '\n');
            std::istringstream selectStream(selectLine);
            std::getline(selectStream, trashString, ' ');
            do{
              std::getline(selectStream, next, ' ');
              selectStatement.arguments.push_back(next);
              embeddedCounter++;
            } while(selectStream) ;
        }
        else if(newlineCounter == 1){
            std::getline(iss,fromLine, '\n');
            std::istringstream fromStream(fromLine);
            std::getline(fromStream, next, ' ');
            fromStatement.arguments.push_back(next);
            do{
              std::getline(fromStream, next, ',');
              fromStatement.arguments.push_back(next);
            } while(fromStream);
        }
        else if(newlineCounter == 2){
            std::getline(iss,whereLine, '\n');
            std::istringstream whereStream(whereLine);
            std::getline(whereStream, next, ' ');
            whereStatement.arguments.push_back(next);
            do{
                do{
                  whereStream >> next;
                  tempString+=next;
              } while(checkKeywords(next));
              whereStatement.arguments.push_back(tempString);
              tempString = "";
            } while(whereStream);
        }
        newlineCounter++;
    } while(!endOfQuery(next, ';'));

}

void Query::getRelationalAlgebra(){/*
  int i = 0;
  int k = 0;
  string next;
  do{
      if(i == 0){ //SELECT Clause
        //std::cout << "1:" << next << std::endl; 
        next = selectStatement.arguments[0];
        //cout << "This is " << next  << " which is what this is\n";
        if(next == "AVERAGE" || next == "MAX" || next == "MIN" || next == "COUNT" ){
          relAlg.push("F");
          relAlg.push(next);
          //std::cout << "2:" << next << std::endl; 
        }
        else{
          relAlg.push("[PROJECT]");
          relAlg.push(next);
          //std::cout << "3:" << next << std::endl; 
          //print();
        }
        next = selectStatement.arguments[1];
        //cout << "this is : " << next << " which I hope is Slim Shady\n";
        while(!endOfQuery(next, '\n')){
          if(next == "AVERAGE" || next == "MAX" || next == "MIN" || next == "COUNT" ){
            relAlg.push("F");
            relAlg.push(next);
            //std::cout << "2:" << next << std::endl; 
          }
          if(next == "AS")
          {
            relAlg.push("RENAME ");
            std::getline(iss, next,' ');
          }
          relAlg.push("(");
          relAlg.push(next);
          relAlg.push(")");
          std::getline(iss, next,' ');
          //std::cout << "4:" << next << std::endl; 
        }
        //cout << "EXITS WHILE\n";
      }
      
      else if (i == 1){ //FROM Clause
        std::getline(iss, next);
        cout << next;
        cout << "\nFROM SHOULD BE GONE DAMNIT.\n";
      }

      else if(i >= 2){ //WHERE Clause
        //cout << "ENTERS WHERE\n";
        std::getline(iss, next,' ');
        if(k == 0){
          k++;
          relAlg.push("[SELECTION]");
        }
        
        if(next == "SELECT"){ //Nested Query
          i = 0; //Resets loop, but have to go through Projection
          k = 0;
          if(next == "AVERAGE" || next == "MAX" || next == "MIN" || next == "COUNT" ){
            relAlg.push("F");
            relAlg.push(next);
          }
          else
            relAlg.push("[PROJECT]");
          std::getline(iss, next,' ');
          
          while(next != " "){
           if(next == "AS"){
              relAlg.push("[RENAME]");
              std::getline(iss, next,' ');
            } //endif
            relAlg.push("(");
            relAlg.push(next);
            relAlg.push(")");
            std::getline(iss, next,' ');
          } // end while
        } //endif
        
        else if(next == "AND"){
          relAlg.push("[JOIN]");
        } //end elseif
        
        else if(next == "IN" || next == "CONTAINS" || next == "INTERSECT")
          relAlg.push("[INTERSECTION]");
        
        else if(next == "HAVING" || next == "EXISTS")
          relAlg.push("[DIVIDED BY]");
        
        else if(next == "NOTEXISTS")
          relAlg.push("[SET DIFFERENCE]");
        
        else if(next == "EXCEPT")
          relAlg.push("[SET DIFFERENCE]");
        
        else if(next == "GROUP BY"){
          queue<string> temp = relAlg;
          std::getline(iss, next, '\n');
          for(unsigned int f = 0; f < temp.size(); f++)
            relAlg.pop();
          relAlg.push(next);
          for(unsigned int c = 0; c < temp.size(); c++){
            next = temp.front();
            relAlg.push(next);
          }
          next = "\n";
        }
        
        else if(next == "UNION")
          relAlg.push("[UNION]");
        
        else{ //not a keyword
          relAlg.push("(");
          relAlg.push(next);
          relAlg.push(")");
        } // end else
      } //end else if(WHERE CLAUSE)
    i++;
  }while(!endOfQuery(next, ';'));//true);
  print();
  */

  return;
}

void Query::print()
{
  string temp;
  for(unsigned int i = 0; i < relAlg.size() + 1; i++){
    temp = relAlg.front();
    relAlg.pop();
    cout << temp << " ";
  }
  return;
}

void Query::printVector(){
  for(int i = 0; i < selectStatement.arguments.size() - 1; i++){
    std::cout << selectStatement.arguments[i] << " ";
  }
}

void Query::Algebra(){
  string arg = "";
  int counter = 0;
  for(int i = 0; i < selectStatement.arguments.size() - 1; i++){
    arg = selectStatement.arguments[i];
    if(i == 0){
      relAlg.push("[PROJECT]");
      relAlg.push(selectStatement.arguments[i + 1]);
      i++;
    }
    if(arg == "COUNT" || arg == "AVERAGE" || arg == "MIN" || arg == "MAX"){
      relAlg.push("[F]");
      relAlg.push(arg);
      relAlg.push(selectStatement.arguments[i+1]);
      i++;
    }
  }
  print();

}



