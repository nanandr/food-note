#include <iostream>
#include "csv_reader.h"
#include <fstream>
using namespace std;


void baca_database(string nama_file) 
{
    string filename = nama_file;
    ifstream file(filename);

    if (!file) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }
}
void edit_recipe_makanan() 
{
    baca_database("recipe.csv");
    return ;
}

int main() {
    edit_recipe_makanan();
}

