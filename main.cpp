#include "query.h"
#include "schema.h"

int main(){
    std::vector<Schema> tempSchemas;
    std::string next;
    Schema tempSchema;
    tempSchemas.push_back(tempSchema);

    Query testquery;
    testquery.getQuery();
    //for(int i = 0; i < testquery.selectStatement.arguments.size() - 1; i++){
      //  std::cout << testquery.selectStatement.arguments[i];
   // }
    //testquery.Algebra();
    //testquery.queryTree(tempSchemas);
    testquery.Algebra();

    return 0;
}
