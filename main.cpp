#include "query.h"
#include "schema.h"

int numStatements();
int main(){
    std::vector<Schema> schemaInput;
    Query queryInput;
    Schema tempSchema;
    Query tempQuery;
    for(int i = 1; i <= numStatements(); i++){
        schemaInput.push_back(tempSchema);
        schemaInput[i - 1].getSchemaInput(i);
    }



    queryInput.getQuery();
    std::cout << "SQL QUERY:\n" << queryInput.raw_query << std::endl;
    std::cout << "\nRELATIONAL ALGEBRA:\n";
    queryInput.Algebra(queryInput);
    std::cout << "QUERY TREE:\n";
    queryInput.queryTree(schemaInput);


    for(int i = 0; i < queryInput.whereStatement.arguments.size(); i++){
        std::cout << queryInput.whereStatement.arguments[i];
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
