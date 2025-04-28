#include "recipe_struct.h"
#include "clear_screen.h"
#include "delete_recipe.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
HAPUS RESEP MAKANAN
*/
void deleteRecipe()
{
    ifstream file("database/recipe.csv");
    if (!file.is_open())
    {
        cout << "Gagal membuka arsip!" << endl;
        return;
    }

    Recipe daftar[100];
    string line;
    int jumlah = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string nama, bahan, langkah;

        getline(ss, nama, ',');
        getline(ss, bahan, ',');
        getline(ss, langkah);

        // simpan ke array
        daftar[jumlah].name = nama;
        daftar[jumlah].ingredient = nullptr;
        daftar[jumlah].steps.push_back(langkah);
        jumlah++;
    }
    file.close();

    // Tampilkan daftar resep
    cout << "Daftar Resep:\n";
    for (int i = 0; i < jumlah; i++)
    {
        cout << "[" << i + 1 << "] " << daftar[i].name << endl;
    }

    int nomor;
    cout << "Masukkan nomor resep yang ingin dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > jumlah)
    {
        cout << "Nomor tidak valid!" << endl;
        return;
    }

    nomor--;

    ofstream outfile("database/recipe.csv");
    for (int i = 0; i < jumlah; i++)
    {
        if (i == nomor)
            continue;

        outfile << daftar[i].name << ",,\"";
        for (size_t j = 0; j < daftar[i].steps.size(); ++j)
        {
            outfile << daftar[i].steps[j];
            if (j != daftar[i].steps.size() - 1)
                outfile << "|";
        }
        outfile << "\"" << endl;
    }
    outfile.close();

    clearScreen();
    cout << "Resep berhasil dihapus!" << endl;
}