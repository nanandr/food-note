#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct recipe_makanan {
    string nama_hidangan;
    string bahan_bahan;
    string cara_memasak;
};

void tambah_recipe_makanan()
{
    recipe_makanan resep;
    ofstream file("resep_makanan.txt", ios::app);
    if (!file) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    cout << "Nama Hidangan: ";
    getline(cin, resep.nama_hidangan);
    cout << "Bahan-bahan: ";
    getline(cin, resep.bahan_bahan);

    cout << "Cara Memasak: (Jika sudah selesai ketik (end) ) ";
    string procedur;

    resep.cara_memasak = "";
    int step_count = 1;
    while(true) {
        cout << "Langkah " << step_count << ": ";
        getline(cin, procedur);
        if (procedur == "end") {
            break;
        }
        resep.cara_memasak += "Langkah " + to_string(step_count) + ": " + procedur + "\n";
        step_count++;
    }


    file << "Nama Hidangan: " << resep.nama_hidangan << endl;
    file << "Bahan-bahan: " << resep.bahan_bahan << endl;
    file << "Cara Memasak: " << endl;
    file << resep.cara_memasak << endl;

    file.close();
    cout << "Resep makanan berhasil ditambahkan!" << endl;
}

void lihat_recipe_makanan()
{
    ifstream file("resep_makanan.txt");
    if (!file) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    string line;
    cout << " ---------- Daftar Resep Makanan ---------- " << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    cout << "-------------------------------------------" << endl;
    
}

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
    cin.ignore();

    if (choice == 1) {
        tambah_recipe_makanan();
    } else if (choice == 2) {
        lihat_recipe_makanan();
    } else if (choice == 3) {
        break;
    } else {
        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
    }
}

}







