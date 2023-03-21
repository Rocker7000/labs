
#include <iostream>
#include <fstream>
#include <string>
#define VARIANT1

using namespace std;




int main()
{
    string sentence1 = "this is string one";
    string sentence2 = "this is string two";
    string result;
   
#ifdef VARIANT1 
        result =  sentence1;
#else 
        result = sentence2;
#endif

ofstream file("file.txt");

    if (file.is_open()) {
        file << result;

        file.close();
    }  
    
    return 1;
}
