#include <iostream>
#include <vector>

using namespace std;

string border_thick = "======================== \n";
string border_thin = "------------------------ \n";

void app_name (string text) {
    cout << border_thick;
    cout << text << endl << endl;
    cout << border_thick;
}

// page title (e.g. halaman daftar resep, buat resep)
void title (string text) {
    cout << border_thin;
    cout << text << endl << endl;
    cout << border_thin;
}

// navigate between 1-9, 0 is kembali/keluar
// kembali/keluar has to be in the last (e.g. [buat resep, cari resep, kembali])
int nav (const vector<string>& pages) {
    int choice;
    for (int i = 0; i < pages.size(); i++) {
        if (pages[i] == "Kembali" || pages[i] == "Keluar") {
            cout << "[0] " << pages[i] << endl;       
        }
        else {
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
    // logic to check if navigate_to exists
    return choice;
}


// UI CARI RESEP

// tampilkan resep jika ditemukan
void show_recipe() {
    title("Buat Resep Baru");
    cout << "Nama Hidangan: Rendang\n";
    cout << "Bahan-bahan:\n";
    cout << "[1] Daging 1kg\n";
    cout << "[2] Bawang Merah 2ons\n";
    cout << "[n] Santan 2liter\n";
    cout << "Cara Memasak:\n";
    cout << "[1] Panaskan\n";
    cout << "[2] Aduk\n";
    cout << "[n] Sajikan\n";
    cout << border_thin;

    nav({"Kembali"});
}

// resep tidak ditemukan
void resep_gkada() {
    title("Resep tidak ditemukan");
    nav({"Kembali"});
}

// UI cari resep
void cari_resep() {
    cin.ignore(); 
    title("Cari Resep");

    string keyword;
    cout << "Nama Hidangan: ";
    getline(cin, keyword);

    cout << border_thin;

    if (keyword == "Rendang" || keyword == "rendang") {
        show_recipe();
    } else {
        resep_gkada();
    }
}

// main program
int main() {
    app_name("Cari Resep");

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