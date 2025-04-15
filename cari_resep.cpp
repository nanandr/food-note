#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

string border_thick = "======================== \n";
string border_thin = "------------------------ \n";

void app_name(string* text) {
    cout << border_thick;
    cout << *text << endl << endl;
    cout << border_thick;
}

void title(string* text) {
    cout << border_thin;
    cout << *text << endl << endl;
    cout << border_thin;
}

int nav(const vector<string>& pages) {
    int choice;
    for (int i = 0; i < pages.size(); i++) {
        if (pages[i] == "Kembali" || pages[i] == "Keluar") {
            cout << "[0] " << pages[i] << endl;       
        } else {
            cout << "[" << i + 1 << "] " << pages[i] << endl;
        }
    }
    cout << border_thin;
    cout << "Navigasi ke halaman: ";
    cin >> choice;
    if (choice < 0 || choice > pages.size()) {
        cout << "Pilihan tidak valid" << endl;
        return -1;
    }
    cout << endl;
    return choice;
}

void lihat_recipe_makanan() {
    ifstream* file = new ifstream("database/recipe.csv");
    if (!file->is_open()) {
        cout << "Database tidak ditemukan!" << endl;
        delete file;
        return;
    }

    string line;
    cout << " ---------- Daftar Resep Makanan ---------- " << endl;
    while (getline(*file, line)) {
        cout << line << endl;
    }
    file->close();
    delete file;
    cout << "-------------------------------------------" << endl;
}

void resep_gkada() {
    string judul = "Resep tidak ditemukan";
    title(&judul);
    nav({"Kembali"});
}

void cari_resep() {
    cin.ignore();
    string judul = "Cari Resep";
    title(&judul);

    string keyword;
    cout << "Nama Hidangan: ";
    getline(cin, keyword);

    cout << border_thin;

    ifstream* file = new ifstream("database/recipe.csv");
    if (!file->is_open()) {
        cout << "Database tidak ditemukan!" << endl;
        delete file;
        return;
    }

    string line;
    bool found = false;
    while (getline(*file, line)) {
        stringstream ss(line);
        string id, namaResep, bahan, langkah;
        getline(ss, id, ',');
        getline(ss, namaResep, ',');
        getline(ss, bahan, ',');
        getline(ss, langkah);
    
        if (keyword == namaResep) {
            cout << "Resep ditemukan!\n";
            cout << "Nama   : " << namaResep << endl;
            cout << "Bahan  : " << bahan << endl;
            cout << "Langkah: " << langkah << endl;
            found = true;
            break;
        }
    }
    

    file->close();
    delete file;

    if (!found) {
        resep_gkada();
    }
}

int main() {
    string nama_aplikasi = "Cari Resep";
    app_name(&nama_aplikasi);

    while (true) {
        int choice = nav({"Cari Resep", "Keluar"});
        if (choice == 1) {
            cari_resep();
        } else if (choice == 0) {
            cout << "Terimakasih!\n";
            break;
        }
    }

    return 0;
}
