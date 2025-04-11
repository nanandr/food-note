#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "csv_reader.h"
using namespace std;

struct Bahan {
    string nama_bahan;
    string takaran;
    Bahan *next;
};

struct Recipe {
    string nama_resep;
    Bahan* bahan;
    vector<string> langkah;
};

int main() {
    string filename = "./database/recipes.csv";
    readCSV(filename);
    return 0;
}

