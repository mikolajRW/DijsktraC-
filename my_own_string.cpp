#include <iostream>
#include "my_own_string.h"
using namespace std;


My_own_string::My_own_string() : my_string(nullptr), size(0) // default constructor
{
}



My_own_string::My_own_string(const My_own_string& orig)
{
    my_string = new char[strlen(orig.my_string) + 1];
    strcpy(my_string, orig.my_string);
    my_string[strlen(orig.my_string)] = '\0';
}

My_own_string::My_own_string(My_own_string&& orig)
{
    my_string = orig.my_string;
    size = orig.size;

    orig.my_string = nullptr;
    orig.size = 0;
}

My_own_string::My_own_string(char* val)
{
    if (val == nullptr) {
        my_string = new char[1];
        my_string[0] = '\0';
    }

    else {

        my_string = new char[strlen(val)];
        strcpy(my_string, val);
        my_string[strlen(val)] = '\0';
    }
}