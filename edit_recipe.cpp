#include <iostream>
#include "csv_reader.h"
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


void edit_recipe_makanan(const string& filename) 
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    getline(file, line);
    lines.push_back(line);

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    int id;
    cout << "Masukkan ID resep yang ingin diedit; ";
    cin >> id;
    cin.ignore();

    bool found = false;

    for (int i= 1; i < lines.size(); i++) {
        stringstream ss(lines[i]);
        string token;
        getline(ss, token, ',');
        int currentID = stoi(token);

        if (currentID == id) {
            found = true;
            string nama, bahan, langkah;
            getline(ss, nama, ',');
            getline(ss, bahan, ',');
            getline(ss, langkah, ',');

            cout << "Resep ditemukan!" << endl;
            cout << "Nama Hidangan: " << nama << endl;
            cout << "Bahan-bahan: " << bahan << endl;

            cout << "Cara Memasak: ";
            stringstream streamStep(langkah);
            string step;
            int nomor = 1;
            while(getline(streamStep, step, '|')) {
                cout << " " << nomor++ << ". " << step << endl;
            }

            string input;

            cout << "\nMasukkan nama hidangan baru (jika kosong = tidak diubah): ";
            getline(cin, input);
            if(!input.empty()) nama = input;

            cout << "Masukkan bahan-bahan baru (jika kosong = tidak diubah): ";
            getline(cin, input);
            if(!input.empty()) bahan = input;

            cout << "Masukkan langkah memasak baru (JIKA SELESAI, KETIK end): ";

            string langkahBaru = "", barisLangkah;
            int nomors = 1;
            while (true) {
                cout << nomors++ << ".";
                getline(cin, barisLangkah);
                if (barisLangkah == "end") break;
                if (!langkahBaru.empty()) langkahBaru += "|";
                langkahBaru += barisLangkah;
            }
            if (!langkahBaru.empty()) langkah = langkahBaru;


            lines[i] = to_string(currentID) + "," + nama + "," + bahan + "," + langkah;
            break;
        }
    }

    if (!found) {
        cout << "Resep tidak ditemukan!" << endl;
        return;
    }

    ofstream outFile(filename);
    for(const string& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    cout << "Resep berhasil diperbarui!" << endl;
}

int main() 
{
    int pilihan;
    string filename = "./database/recipe.csv";
    while (true) {
        cout << " ---------- Edit Resep Makanan ---------- " << endl;
        cout << "1. Edit Resep Makanan" << endl;
        cout << "2. Lihat Semua Resep Makanan" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (pilihan == 1) {
            edit_recipe_makanan(filename);
        } else if (pilihan == 2) {

            cout << " ---------- Daftar Resep Makanan ---------- " << endl;
            readCSV(filename);
        } else if (pilihan == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }

    }
    

}



