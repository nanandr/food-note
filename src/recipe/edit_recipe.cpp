#include "edit_recipe.h"
#include "clear_screen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
UPDATE RESEP MAKANAN
*/
void editRecipe()
{
    ifstream file("./database/recipe.csv");
    if (!file.is_open())
    {
        cout << "Basis data tidak ditemukan!!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    getline(file, line);
    lines.push_back(line);

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    string keyword;
    cout << "Masukkan nama resep yang ingin diedit: ";
    cin.ignore();
    getline(cin, keyword);

    string keywordLower = keyword;
    transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);
    
    bool found = false;
    
    for (int i = 1; i < lines.size(); i++)
    {
        
        stringstream ss(lines[i]);
        string currentRecipeName, bahan, langkah;
        getline(ss, currentRecipeName, ',');
        getline(ss, bahan, ',');
        getline(ss, langkah, ',');
        
        string namaResepLower = currentRecipeName;
        transform(namaResepLower.begin(), namaResepLower.end(), namaResepLower.begin(), ::tolower);
        
        if (!namaResepLower.empty() && namaResepLower.front() == '"')
        namaResepLower = namaResepLower.substr(1, namaResepLower.size() - 2);

        if (namaResepLower == keywordLower)
        {
            found = true;

            cout << "Nama Resep         : " << currentRecipeName << endl;
            cout << "Bahan-bahan        : " << endl;
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
            cout << "Cara Memasak: " << endl;
            stringstream streamStep(langkah);
            string step;
            int nomor = 1;
            while (getline(streamStep, step, '|'))
            {
                cout << " " << nomor++ << ". " << step << endl;
            }

            string input;

            cout << "\nMasukkan nama hidangan baru (jika kosong = tidak diubah): ";
            getline(cin, input);
            if (!input.empty())
                currentRecipeName = "\"" + input + "\"";

            cout << "Masukkan bahan-bahan baru, dengan format [bahan:jumlah;bahan..n] (kosong = tidak diubah): ";
            getline(cin, input);
            if (!input.empty())
                bahan = "\"" + input + "\"";

            cout << "Masukkan langkah memasak baru (JIKA SELESAI, KETIK end): ";

            string langkahBaru = "", barisLangkah;
            int nomors = 1;
            while (true)
            {
                cout << nomors++ << ".";
                getline(cin, barisLangkah);
                if (barisLangkah == "end")
                    break;
                if (!langkahBaru.empty())
                    langkahBaru += "|";
                langkahBaru += barisLangkah;
            }
            if (!langkahBaru.empty())
                langkah = "\"" + langkahBaru + "\"";

            lines[i] = currentRecipeName + "," + bahan + "," + langkah;
            break;
        }
    }

    if (!found)
    {
        cout << "Resep tidak ditemukan!" << endl;
        return;
    }

    ofstream outFile("./database/recipe.csv");
    for (const string &l : lines)
    {
        outFile << l << "\n";
    }
    outFile.close();

    clearScreen();
    cout << "Resep berhasil diperbarui!" << endl;
}