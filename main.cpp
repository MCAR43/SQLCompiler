#include "query.h"
#include "schema.h"

int numStatements();
int main(){
    std::vector<Schema> schemaInput;
    std::vector<Query> queryInput;
    std::string next;
    Schema tempSchema;
    Query tempQuery;
    for(int i = 1; i <= numStatements(); i++){
        schemaInput.push_back(tempSchema);
        schemaInput[i - 1].getSchemaInput(i);
    }

    queryInput.push_back(tempQuery);
    queryInput[0].getQuery();

   // queryInput[0].queryTree(schemaInput);
    

    return 0;
}







//So unoptimized i might die
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
