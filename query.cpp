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
        if(keyword == KEYWORDS[i])
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
    string selectLine, fromLine, whereLine, tempString;
    int newlineCounter = 0;
    string next;
    do{
        if(newlineCounter == 0){
            std::getline(iss,selectLine, '\n');
            std::istringstream selectStream(selectLine);
            std::getline(selectStream, selectStatement.selectSymbol, ' ');
            do{
              std::getline(selectStream, next, ',');
              selectStatement.arguments.push_back(next);
            } while(selectStream);
        }
        else if(newlineCounter == 1){
            std::getline(iss,fromLine, '\n');
            std::istringstream fromStream(fromLine);
            std::getline(fromStream, fromStatement.fromSymbol, ' ');
            do{
              std::getline(fromStream, next, ',');
              fromStatement.arguments.push_back(next);
            } while(fromStream);
        }
        else if(newlineCounter == 2){
            std::getline(iss,whereLine, '\n');
            std::istringstream whereStream(whereLine);
            std::getline(whereStream, whereStatement.whereSymbol, ' ');
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

void Query::getRelationalAlgebra(){
  int i = 0;
  string next;
  istringstream iss(raw_query);
  do{
      if(i == 0){ //SELECT Clause
        std::getline(iss, next,' ');
        std::cout << "1:" << next << std::endl; 
        std::getline(iss, next, ' ');
        if(next == "AVERAGE" || next == "MAX" || next == "MIN" || next == "COUNT" ){
          relAlg.push("F");
          relAlg.push(next);
          std::cout << "2:" << next << std::endl; 
        }
        else{
          relAlg.push("[PROJECT]");
          relAlg.push(next);
          std::cout << "3:" << next << std::endl; 
          print();
        }
        std::getline(iss, next,' ');
        while(!endOfQuery(next, '\n')){
          if(next == "AS")
          {
            relAlg.push("RENAME ");
            std::getline(iss, next,' ');
          }
          relAlg.push("(");
          relAlg.push(next);
          relAlg.push(")");
          std::getline(iss, next,' ');
          std::cout << "4:" << next << std::endl; 
        }
      }
      /*
      else if (i == 1){ //FROM Clause
        std::getline(sin, next, ' ');
      }
      else if(i >= 2){ //WHERE Clause
        std::getline(sin, next,' ');
        if(next == "SELECT"){ //Nested Query
          i = 0; //Resets loop, but have to go through Projection
          if(next == "AVERAGE" || next == "MAX" || next == "MIN" || next == "COUNT" ){
            relAlg.push("F");
            relAlg.push(next);
          }
          else
            relAlg.push("PROJECT");
          std::getline(sin, next,' ');
          while(next != " "){
           if(next == "AS"){
              relAlg.push("RENAME ");
              std::getline(sin, next,' ');
            } //endif
            relAlg.push("(");
            relAlg.push(next);
            relAlg.push(")");
            std::getline(sin, next,' ');
          } // end while
        } //endif
        else if(next == "AND"){
          relAlg.push("JOIN");
        } //end elseif
        else if(next == "IN" || next == "CONTAINS" || next == "INTERSECT")
          relAlg.push("INTERSECTION");
        else if(next == "HAVING" || next == "EXISTS")
          relAlg.push("DIVIDED BY");
        else if(next == "NOTEXISTS")
          relAlg.push("SET DIFFERENCE");
        else if(next == "EXCEPT")
          relAlg.push("SET DIFFERENCE");
        else if(next == "GROUP BY"){
          queue<string> temp = relAlg;
          std::getline(sin, next, '\n');
          for(unsigned int i = 0; i < temp.size(); i++)
            relAlg.pop();
          relAlg.push(next);
            for(unsigned int c = 0; c < temp.size(); c++){
              next = temp.front();
              relAlg.push(next);
            }
          next = "\n";
        }
        else if(next == "UNION")
          relAlg.push("UNION");
        
        else{ //not a keyword
          relAlg.push("(");
          relAlg.push(next);
          relAlg.push(")");
        } // end else
      } //end else if(WHERE CLAUSE)
   */ i++;
  }while(i < 2);//true);


  return;
}

void Query::print()
{
  string temp;
  for(unsigned int c = 0; c < relAlg.size(); c++){

  }
  for(unsigned int i = 0; i < relAlg.size() + 1; i++){
    temp = relAlg.front();
    relAlg.pop();
    cout << temp << " ";
  }
  return;
}
