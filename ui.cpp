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


// example usage
int main () {
    title("Aplikasi Catat Resep");
    int navigate_to = nav({"Buat Resep Baru", "Daftar Resep", "Cari Resep", "Kembali"});
    cout << navigate_to;
}