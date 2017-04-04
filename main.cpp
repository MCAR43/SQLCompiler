#include "query.h"
#include "schema.h"

int main(){
    std::vector<Schema> tempSchemas;
    std::string next;
    Schema tempSchema;
    tempSchemas.push_back(tempSchema);

    Query testquery;
    testquery.getQuery();
    std::cout << testquery.whereStatement.arguments[2];
    std::cout << testquery.whereStatement.arguments[3];
    std::cout << testquery.whereStatement.arguments[4];
    std::cout << testquery.whereStatement.arguments[5];

    return 0;
}
