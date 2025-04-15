/* 
UTS SDA KELOMPOK 4 
Aplikasi Manajemen Resep Makanan (Food Note)

1. Nandana Rafi Ardika (2404158)
2. Hilmi Mithwa Ramadhan (2404042)
3. Febriansyah Nugraha (2408163)
4. Raden Hamizan Rizky Kusuma (2403657)
5. Raihan Fauzi Rakhman (2403872)
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Ingredient {
    string name;
    string amount;
    Ingredient *next;
};

struct Recipe {
    string name;
    Ingredient* ingredient;
    vector<string> steps;
};

void tambah_recipe_makanan() {
    Recipe resep;
    ofstream file("./database/recipe.csv", ios::app);

    if (!file) {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    cout << "Nama Hidangan: ";
    cin.ignore();
    getline(cin, resep.name);

    cout << "Masukkan bahan-bahan (ketik 'end' untuk selesai): " << endl;
    Ingredient *head = nullptr, *tail = nullptr;
    
    while (true) {
        string name, amount;

        cout << "Nama bahan: ";
        getline(cin, name);
        if (name == "end") break;

        cout << "Jumlah: ";
        getline(cin, amount);

        Ingredient* new_ingredient = new Ingredient{name, amount, nullptr};
        if (!head) head = tail = new_ingredient;
        else {
            tail->next = new_ingredient;
            tail = new_ingredient;
        }
    }
    resep.ingredient = head;

    // INPUT LANGKAH-LANGKAH
    cout << "Masukkan cara memasak (ketik 'end' untuk selesai): " << endl;
    int step_count = 1;
    while(true) {
        string step;
        cout << "Langkah " << step_count << ": ";
        getline(cin, step);
        if (step == "end") break;
        resep.steps.push_back(step);
        step_count++;
    }

    file << "\"" << resep.name << "\","; // simpen ke dalam format csv

    // BAHAN-BAHAN
    stringstream ingreadientStream;
    Ingredient* current = resep.ingredient;
    while (current) {
        ingreadientStream << current->name << ":" << current->amount;
        if (current->next) ingreadientStream << ";";
        current = current->next;
    }
    file << "\"" << ingreadientStream.str() << "\",";

    // LANGKAH-LANGKAH
    stringstream stepsStream;
    for (size_t i = 0; i < resep.steps.size(); i++) {
        stepsStream << resep.steps[i];
        if (i != resep.steps.size() - 1) stepsStream << "|";
    }
    file << "\"" << stepsStream.str() << "\"" << endl;

    file.close();
    cout << "Resep makanan berhasil ditambahkan." << endl;

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
        string nama, bahanCSV, langkahCSV;

        getline(ss, nama, ',');
        getline(ss, bahanCSV, ',');
        getline(ss, langkahCSV, ',');

        if (!nama.empty() && nama.front() == '"') nama = nama.substr(1, nama.size() - 2);
        if (!bahanCSV.empty() && bahanCSV.front() == '"') bahanCSV = bahanCSV.substr(1, bahanCSV.size() - 2);
        if (!langkahCSV.empty() && langkahCSV.front() == '"') langkahCSV = langkahCSV.substr(1, langkahCSV.size() - 2);

        cout << "Nama Hidangan : " << nama << endl;

        cout << "Bahan-bahan   :" << endl;
        stringstream bahanSS(bahanCSV);
        string pair;
        while (getline(bahanSS, pair, ';')) {
            size_t pos = pair.find(':');
            if (pos != string::npos) {
                string ingName = pair.substr(0, pos);
                string ingAmount = pair.substr(pos + 1);
                cout << "- " << ingName << " (" << ingAmount << ")" << endl;
            }
        }

        cout << "Cara Memasak  :" << endl;
        stringstream langkahSS(langkahCSV);
        string step;
        int stepNum = 1;
        while (getline(langkahSS, step, '|')) {
            cout << "Langkah " << stepNum++ << ": " << step << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    file.close();
}


int main() {
    // navigation value
    int nav = 0;

    // main loop
    while (true) {
    // title
    // title();

    // navigation
    // int nav = navigate_to({"Buat Resep Baru", "Daftar Resep", "Cari Resep", "Keluar"});
    
    // Buat Resep Baru
        if (nav == 1) {
            Recipe recipe;

            Ingredient* tail = nullptr;

            int i = 0;
            int j = 0;
            string name, amount, step;

            // header("Buat Resep Baru");
            cout << "Nama Hidangan: ";
            cin >> recipe.name;
            // cout << border_thin;
            
            cout << "Bahan-bahan: \n";
            // input loop, type 0 to finish
            while (true) {
                cout << "[" << i+1 << "] Nama Bahan: ";
                cin >> name;
                if (name == "0") break;

                cout << "     Jumlah: ";
                cin >> amount;
                
                Ingredient* ingredient = new Ingredient;
                ingredient->name = name;
                ingredient->amount = amount;
                ingredient->next = nullptr;

                if (recipe.ingredient == nullptr) {
                    recipe.ingredient = ingredient;
                }
                else {
                    tail->next = ingredient;
                }
                tail = ingredient;
                i++;
            }

            // Cara memasak:
            // border_thin();
            cout << "Cara memasak: \n";
            // steps loop
            while (true) {
                cout << "[" << i+1 << "] ";
                cin >> step;
                if (step == "0") break;

                // put to steps vector
            }
        }
        // Daftar Resep
        else if (nav == 2) {
            // header("Daftar Resep");
            
        } 
        // Cari Resep
        else if (nav == 3) {
            // header("Cari Resep");
            
        }
        // Keluar
        else if (nav == 0) {
            break;
        }
    }
}