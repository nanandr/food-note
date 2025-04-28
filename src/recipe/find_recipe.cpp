#include "recipe_not_found.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

string border_thick = "======================== \n";
string border_thin = "------------------------ \n";

void findRecipe()
{
    cin.ignore();
    cout << border_thick;
    cout << "|  Cari Resep Makanan  |" << endl;
    cout << border_thick;

    string keyword;
    cout << "Nama Hidangan: ";
    getline(cin, keyword);

    ifstream *file = new ifstream("./database/recipe.csv");
    if (!file->is_open())
    {
        cout << "Basis data tidak ditemukan!!" << endl;
        delete file;
        return;
    }

    string line;
    bool found = false;
    while (getline(*file, line))
    {
        stringstream ss(line);
        string namaResep, bahan, langkah;
        getline(ss, namaResep, ',');
        if (!namaResep.empty() && namaResep.front() == '"')
            namaResep = namaResep.substr(1, namaResep.size() - 2);

        getline(ss, bahan, ',');
        getline(ss, langkah);

        // jadiin lowercase dulu keyword sama nama resep nya
        string namaResepLower = namaResep;
        string keywordLower = keyword;
        transform(namaResepLower.begin(), namaResepLower.end(), namaResepLower.begin(), ::tolower);
        transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

        // komparasi keyword dengan namaresep, apakah sama atau tidak
        int compare = keywordLower.compare(namaResepLower);
        if (compare == 0)
        {
            cout << endl;
            cout << border_thin;
            cout << "|   Resep ditemukan!   |\n";
            cout << border_thin;

            cout << "Nama Resep     : " << namaResep << endl;
            cout << "Bahan-bahan    : " << endl;
            stringstream bahanSS(bahan);
            string pair;
            while (getline(bahanSS, pair, ';'))
            {
                size_t pos = pair.find(':');
                if (pos != string::npos)
                {
                    string ingName = pair.substr(0, pos);
                    string ingAmount = pair.substr(pos + 1);
                    cout << "- " << ingName << " (" << ingAmount << ")" << endl;
                }
            }

            cout << "How to Cook    :" << endl;
            stringstream langkahSS(langkah);
            string step;
            int stepNum = 1;
            while (getline(langkahSS, step, '|'))
            {
                cout << "Langkah " << stepNum++ << ": " << step << endl;
            }

            found = true;
            break;
        }
    }

    file->close();
    delete file;

    if (!found)
    {
        recipeNotFound();
    }
}