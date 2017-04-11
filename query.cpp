#include "query.h"
using namespace std;

Query::Query(){
    std::ifstream fin;
    fin.clear();
    fin.open(INPUTFILESQL.c_str());
    std::getline(fin, raw_query, ';');
    raw_query.append(";");

}

Query::Query(const string newraw_query){
  raw_query = newraw_query;
  raw_query.append(";");
  //cout << "\n\n\n\n\n\n\n" << raw_query << endl;
}

//checks the string passed to see if it matches any SQL keywords
bool Query::checkKeywords(const string keyword){
    for(int i = 0; i < 18; i++){ //18 is the amount of keywords, don'tbe a dumbass fis this later'
        //if(keyword.find(KEYWORDS[i]))
        if(keyword == KEYWORDS[i])
          return true;
    }
    return false;
}

//Returns true if it is the end of the query, and false otherwise
bool Query::endOfQuery(const string stringToCheck, const char charToEnd){
    for(unsigned int i = 0; i < stringToCheck.length(); i++){
        if(stringToCheck[i] == charToEnd)
            return true;

    }
    return false;

}

//A function to take in the entire query, split it into three seperate objects, SELECT, FROM, and WHERE
//and then parse those objects into arguments
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
            whereStatement.rawWhereLine = whereLine;
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
            //std::getline(iss, next, ' ');
            while(extraStream >> next){
             whereStatement.arguments.push_back(next);
            }

        }
        newlineCounter++;
    } while(!endOfQuery(next, ';'));
}

//Prints the relational Algebra
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

//Prints the Query Tree
void Query::printStack(std::stack<string> myStack){
  string temp;
  std::stack<string> tempStack = myStack;
  while(!tempStack.empty()){
    temp = tempStack.top();
    std::cout << "[ "<< temp << "]";
    tempStack.pop();
    std::cout << "<---";
  }
  std::cout<<std::endl;
}

void Query::Algebra(Query Q){ //RELATIONAL ALGEBRA FUNCTION
  string arg = "";
  bool nested = false;
  
  for(int i = 0; i < Q.selectStatement.arguments.size(); i++){ //SELECT CLAUSE
    cout << Q.selectStatement.arguments[i] << endl << endl;
    arg = Q.selectStatement.arguments[i];
    //SELECT TOKEN
    if(i == 0){
      relAlg.push("[PROJECT]");
      relAlg.push(Q.selectStatement.arguments[i]);
    }
    //AGGREGATE FUNCTIONS
    else if(arg == "COUNT" || arg == "AVERAGE" || arg == "MIN" || arg == "MAX"){
      relAlg.push("[F]");
      relAlg.push(Q.selectStatement.arguments[i-1]);
      relAlg.push(Q.selectStatement.arguments[i]);
      i++;
    } 
    //EVERYTHING ELSE
    else
     relAlg.push(Q.selectStatement.arguments[i-1]);
  }

  //NO FROM CLAUSE BECAUSE IT IS UNNECESSARY FOR THE RELATIONAL ALGEBRA

  for(int i = 0; i < Q.whereStatement.arguments.size(); i++){ //WHERE CLAUSE
    //WHERE TOKEN
  //  cout << Q.whereStatement.arguments[i];
    if(i == 0)
      relAlg.push("[SELECTION] (");
    
    else if(Q.whereStatement.arguments[i] == "SELECT"){ //NESTED QUERY
      string newraw_query;
      for(int c = i; c < Q.whereStatement.arguments.size(); c++){ //MAKES NEW QUERY WITH ONLY THE SUBQUERIES ELEMENTS
        //newraw_query.append(Q.whereStatement.arguments[c-1]);
        //IF IT IS A MAJOR KEY WORD, ADD A NEW LINE
        //cout << endl << endl << Q.whereStatement.arguments[c];
        if(Q.whereStatement.arguments[c] == "SELECT" ||
           Q.whereStatement.arguments[c] == "FROM" ||
           Q.whereStatement.arguments[c] == "WHERE" ||
           Q.whereStatement.arguments[c] == "GROUP BY" ){
          newraw_query.append("\n");
          newraw_query.append(Q.whereStatement.arguments[c]);
        }
        else{   //OTHERWISE, A SPACE
          newraw_query.append(" ");
          newraw_query.append(Q.whereStatement.arguments[c]); 
        }
      }
      //cout << endl << "NEW RAW FUCKING QUERY BITCHEZ     " << newraw_query << endl;
      //RUNS THE FUNCTION AGAIN, OUR SOLUTION FOR RECURSION
      Query nestedQuery(newraw_query);
      nestedQuery.getQuery();
      Algebra(nestedQuery);
//      nested = true;
    }  
    
    //AND STATEMENTS
    else if(whereStatement.arguments[i] == "AND")
      relAlg.push("[JOIN]");
    
    //INTERSECTION OR EQUIVALENT KEYWORD STATEMENTS
    else if(whereStatement.arguments[i] == "IN" ||
            whereStatement.arguments[i] == "CONTAINS" ||
            whereStatement.arguments[i] == "INTERSECT")
      relAlg.push("[INTERSECTION]");
    
    //DIVISION STATEMENTS
    else if(whereStatement.arguments[i] == "HAVING" ||
            whereStatement.arguments[i] == "EXISTS")
      relAlg.push("[DIVIDE]");
   
    //SET DIFFERENCE STATEMENTS
    else if(whereStatement.arguments[i] == "EXCEPT" ||
            whereStatement.arguments[i] == "NOTEXISTS")
      relAlg.push("[SET DIFFERENCE]");
    
    //GROUPING ATTRIBUTES
    else if(whereStatement.arguments[i] =="GROUP" && whereStatement.arguments[i+1] == "BY")
    {                    
      queue<string> temp; 
      arg = whereStatement.arguments[i+2];
      int size = relAlg.size();
      //FINDS WHERE [F] IS IN THE ORIGINAL STRING, PUTS THE ATTRIBUTE IN FRONT OF IT
      for(unsigned int f = 0; f < size; f++){
        if(relAlg.front() == "[F]")
          temp.push(arg);
        temp.push(relAlg.front());
        relAlg.pop();
      }
      cout << endl << endl;
      //THEN APPENDS THE OLD STRING ONTO THE NEW ONE WITH THE GROUPING ATTRIBUTES
      for(unsigned int c = 0; c < size+1; c++){
        arg = temp.front();
        temp.pop();
        relAlg.push(arg);
      }
      i++;
    }
    //UNION STATEMENTS
    else if(whereStatement.arguments[i] == "UNION")
      relAlg.push("[UNION]");
      
    //ANYTHING ELSE
    else{
      relAlg.push("(");
      relAlg.push(whereStatement.arguments[i]);
      relAlg.push(")");
    }
    if(nested)
      i = whereStatement.arguments.size();
  }
  relAlg.push(")");
  print();

  cout << endl;
    
}

//Takes an input of SchemaList (Which is just the list of schema names)
//Checks the SELECT, FROM, and WHERE clauses and translates them into a query Tree
void Query::queryTree(std::vector<Schema> schemaList){
  string toCheck;
  int embeddedCounter = 0;
  string toPush, toPushSelect, trashString, toPushWhere, next;
  std::stack<string> tempStack;

  //FROM STATEMENT PROCESSING 
  for(int i = 1; i < fromStatement.arguments.size(); i++){
    for(int j = 0; j < schemaList.size(); j++){
        toCheck = schemaList[j].getSchemaName();
        if(j > 0){
          toCheck.erase(toCheck.begin(), toCheck.begin() + 1);
        }
        if(fromStatement.arguments[i] == toCheck){
          queryStack.push(toCheck);
        }
    }
  }

  //WHERE STATEMENT PROCESSING
  for(int i = 1; i < whereStatement.arguments.size(); i++){
    next = whereStatement.arguments[i];
    if(checkKeywords(next)){
      queryStack.push(toPushWhere);
      toPushWhere = "";
    }
    else{
      toPushWhere+=next;
    }
  }
  queryStack.push(toPushWhere);

  //SELECT STATEMENT PROCESSING
  for(int i = 0; i < selectStatement.arguments.size(); i++){  
    toPushSelect+=selectStatement.arguments[i];
  }
  queryStack.push("[PI]" + toPushSelect);
  printStack(queryStack);
}



