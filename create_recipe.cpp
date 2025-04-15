#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct recipe_makanan {
    string nama_hidangan;
    string bahan_bahan;
    string cara_memasak;
};

void tambah_recipe_makanan() {
    recipe_makanan resep;
    ofstream file("./database/recipe.csv", ios::app);

    if (!file) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    cout << "Nama Hidangan: ";
    cin.ignore();
    getline(cin, resep.nama_hidangan);

    cout << "Bahan-bahan: ";
    getline(cin, resep.bahan_bahan);

    cout << "Cara Memasak: (Jika sudah selesai ketik (end))" << endl;
    string procedur;
    resep.cara_memasak = "";
    int step_count = 1;
    while (true) {
        cout << "Langkah " << step_count << ": ";
        getline(cin, procedur);
        if (procedur == "end") break;
        resep.cara_memasak += "Langkah " + to_string(step_count) + ": " + procedur + " | ";
        step_count++;
    }

    if (!resep.cara_memasak.empty() && resep.cara_memasak.back() == ' ') {
        resep.cara_memasak.erase(resep.cara_memasak.size() - 3);
    }

    // simpen ke format csv
    file << "\"" << resep.nama_hidangan << "\","
         << "\"" << resep.bahan_bahan << "\","
         << "\"" << resep.cara_memasak << "\"" << endl;

    file.close();
    cout << "Resep makanan berhasil ditambahkan!" << endl;
}

void lihat_recipe_makanan() {
    ifstream file("./database/recipe.csv");
    if (!file) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    string line;
    cout << " ---------- Daftar Resep Makanan ---------- " << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string nama, bahan, cara;

        getline(ss, nama, ',');
        getline(ss, bahan, ',');
        getline(ss, cara, ',');

        // Remove surrounding quotes if present
        if (!nama.empty() && nama[0] == '"') nama = nama.substr(1, nama.length() - 2);
        if (!bahan.empty() && bahan[0] == '"') bahan = bahan.substr(1, bahan.length() - 2);
        if (!cara.empty() && cara[0] == '"') cara = cara.substr(1, cara.length() - 2);

        cout << "Nama Hidangan : " << nama << endl;
        cout << "Bahan-bahan   : " << bahan << endl;
        cout << "Cara Memasak  : " << endl << cara << endl;
        cout << "-------------------------------------------" << endl;
    }

    file.close();
}

int main() {
    int choice;
    while (true) {
        cout << " ---------- Buat Resep Makanan ---------- " << endl;
        cout << "1. Tambah resep makanan" << endl;
        cout << "2. Lihat semua resep makanan" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> choice;

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
