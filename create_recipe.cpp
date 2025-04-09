#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct recipe_makanan {
    string nama_makanan;
    string alat_bahan;
    string langkah_pembuatan;
};

void tambah_recipe_makanan()
{

};

void lihat_recipe_makanan()
{
    recipe_makanan rm;
    
};


int main () 
{
    int choice;
    while (true) {
    cout << " ---------- Buat Resep Makanan ---------- " << endl;
    cout << "1. Tambah resep makanan" << endl;
    cout << "2. Lihat semua resep makanan" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih menu: " << endl;
    cin >> choice;

    if (choice == 1) {
        tambah_recipe_makanan();
    } else if (choice == 2) {
        lihat_recipe_makanan();
    } else if (choice == 3) {
        break;
    }
}

}







