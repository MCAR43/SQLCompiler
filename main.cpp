#include "query.h"
#include "schema.h"

int numStatements();
void printQueryLine(Query query, const int lineNum);
int main(){
    std::vector<Schema> schemaInput;
    std::vector<Query> nestedQueries;
    Query tempQuery;
    Query queryInput;
    Schema tempSchema;
    nestedQueries.push_back(queryInput);
    


    //This is getting the Schema 
    //Initial push_back of the schema is to not overflow

    for(int i = 1; i <= numStatements(); i++){
        schemaInput.push_back(tempSchema);
        schemaInput[i - 1].getSchemaInput(i);
    }


    return 0;
}


int numStatements(){
    int counter = 0;
    string next;
    std::ifstream fin;
    fin.open(INPUTFILE.c_str());
    while(fin >> next){
        for(int i = 0; i < next.length(); i++){
            if(next[i] == ';')
                counter++;
        }
    }
    
    return counter;
}

void printQueryLine(Query query, const int lineNum){
    for(int i = 0; i < query.whereStatement.arguments.size(); i++){
        std::cout << query.whereStatement.arguments[i];
    }
}
