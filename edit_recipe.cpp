#include <iostream>
#include "csv_reader.h"
#include <fstream>
using namespace std;



void edit_recipe_makanan() 
{
    string database_name = "./database/recipe.csv";
    readCSV(database_name);
}

int main() {
    edit_recipe_makanan();
    return 0;
}




