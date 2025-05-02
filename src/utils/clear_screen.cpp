#include "utils/clear_screen.h"
#include <iostream>
using namespace std;

// menghapus screen
void clearScreen ()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux / Mac
    #endif
}