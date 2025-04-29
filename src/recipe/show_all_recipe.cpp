#include "utils/get_db_path.h"
#include "utils/borders.h"
#include "recipe/show_all_recipe.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
LIHAT RESEP MAKANAN
*/
void showAllRecipe()
{
    string db_path = getDBPath("recipe.csv");

    ifstream file(db_path);
    if (!file)
    {
        cout << "Basis data tidak ditemukan!!" << endl;
        return;
    }

    string line;
    int count_resep = 1;

    cout << border_thick;
    cout << "| Daftar Resep Makanan |" << endl;
    cout << border_thick;
    while (getline(file, line))
    {
        stringstream ss(line);
        string nama, bahanCSV, langkahCSV;

        getline(ss, nama, ',');
        getline(ss, bahanCSV, ',');
        getline(ss, langkahCSV, ',');

        if (!nama.empty() && nama.front() == '"')
            nama = nama.substr(1, nama.size() - 2);
        if (!bahanCSV.empty() && bahanCSV.front() == '"')
            bahanCSV = bahanCSV.substr(1, bahanCSV.size() - 2);
        if (!langkahCSV.empty() && langkahCSV.front() == '"')
            langkahCSV = langkahCSV.substr(1, langkahCSV.size() - 2);

        cout << "[" << count_resep << "] " << nama << endl;
        count_resep += 1;
        cout << border_thin;
    }

    file.close();
}