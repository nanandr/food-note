#include <stdio.h>
#include <vector>
#include <iostream>
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
    Recipe resep1;
    resep1.nama_resep = "Ayam Goreng";
}

