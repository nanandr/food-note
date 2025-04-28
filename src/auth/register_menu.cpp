#include "register_menu.h"
#include "get_latest_userid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

int registerMenu()
{
    string line;
    string inp_surel_pengguna;
    string inp_kata_sandi;
    string inp_nama_pengguna;
    char del = ','; // delimiter pemisah string

    cout << "\n";
    cout << "========================" << endl;
    cout << "|                      |" << endl;
    cout << "|  Daftar Pengguna     |" << endl;
    cout << "|  Baru                |" << endl;
    cout << "|                      |" << endl;
    cout << "========================" << endl;
    cout << "Masukkan surel pengguna (\"kembali\" untuk kembali ke menu awal)" << endl;
    cout << "> ";
    cin >> inp_surel_pengguna;

    // jadiin lowercase buat input surel
    string surel_pengguna_lower = inp_surel_pengguna;
    transform(surel_pengguna_lower.begin(), surel_pengguna_lower.end(), surel_pengguna_lower.begin(), ::tolower);

    // kalau inputannya "kembali" pas input surel, return -1
    int compareInputToExit = surel_pengguna_lower.compare("kembali");
    if (compareInputToExit == 0) {
        return -1;
    }
    cin.ignore();

    cout << "Masukkan nama pengguna" << endl;
    cout << "> ";
    getline(cin, inp_nama_pengguna);
    
    cout << "Buat kata sandi baru" << endl;
    cout << "> ";
    cin >> inp_kata_sandi;

    // ambil id terbesar dan terbaru di users.csv
    int id = getLatestUserId();
    if (id == 0)
    {
        cout << "Gagal mendaftar pengguna baru." << endl;
        return 0;
    }

    // tambah kredensial pengguna baru ke dalem csv, tulis baris baru
    ofstream wregistuser("./database/users.csv", ios::app);
    if (wregistuser.is_open())
    {
        wregistuser << id << "," << inp_surel_pengguna << "," << inp_kata_sandi << "," << inp_nama_pengguna << "\n";
        wregistuser.close();

        cout << "Registrasi Berhasil!" << endl;
    }
    else
    {
        cout << "Gagal mendaftar pengguna baru." << endl;
    }

    return 0;
}