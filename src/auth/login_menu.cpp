#include "utils/get_db_path.h"
#include "auth/delete_session.h"
#include "auth/login_menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

int loginMenu()
{
    string users_db_path = getDBPath("users.csv");
    string session_db_path = getDBPath("session.csv");

    ifstream rfile(users_db_path, ios::app);
    if (!rfile)
    {
        cout << "Basis data tidak ditemukan!" << endl;
        return -1;
    }
    cout << "\n";

    string line;
    string inp_surel_pengguna;
    string inp_kata_sandi;
    char del = ','; // delimiter pemisah string

    cout << "\n";
    cout << "========================" << endl;
    cout << "|                      |" << endl;
    cout << "|  Masuk               |" << endl;
    cout << "|                      |" << endl;
    cout << "========================" << endl;
    cout << "Masukkan surel pengguna (\"kembali\" untuk kembali ke menu awal)" << endl;
    cout << "> ";
    cin >> inp_surel_pengguna;

    // jadiin lowercase buat input surel
    string surel_pengguna_lower = inp_surel_pengguna;
    transform(surel_pengguna_lower.begin(), surel_pengguna_lower.end(), surel_pengguna_lower.begin(), ::tolower);

    // kalau inputannya "kembali" pas input surel, return -1
    int compare_inp_to_exit = surel_pengguna_lower.compare("kembali");
    if (compare_inp_to_exit == 0) {
        return -1;
    }
    cout << "Masukkan kata sandi " << endl;
    cout << "> ";
    cin >> inp_kata_sandi;
    
    // cek tiap baris csv apakah ada yang serupa
    while (getline(rfile, line))
    {
        stringstream ss(line);
        string id;
        string surel;
        string kata_sandi;
        string nama_pengguna;

        getline(ss, id, ',');
        getline(ss, surel, ',');
        getline(ss, kata_sandi, ',');
        getline(ss, nama_pengguna, ',');

        int compareSurel = surel_pengguna_lower.compare(surel);
        int compareKataSandi = inp_kata_sandi.compare(kata_sandi);

        if ((compareSurel == 0) && (compareKataSandi == 0))
        {
            /* 
            hapus sesi yg lama (kalau ada)
            terus bikin sesi baru dari pengguna yang masuk tadi 
            */
            deleteSession();

            ofstream wsession(session_db_path, ios::app);
            if (wsession.is_open())
            {
                wsession << id << "," << surel << "," << kata_sandi << "," << nama_pengguna << "\n";
                wsession.close();
            }
            else
            {
                cout << "Gagal membuat sesi baru." << endl;
            }

            return 1; // success
        }
    }

    return 0;
}