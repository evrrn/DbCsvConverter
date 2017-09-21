#include <csvtodb.h>
#include <Vector>
//https://www.codeproject.com/Articles/6343/CppSQLite-C-Wrapper-for-SQLite
void converter(ifstream input){
    vector<int> name = new vector;
    while (input != "\n"){
        char * temp;
        input>>temp;
        name.push_back(temp);
    }

}
