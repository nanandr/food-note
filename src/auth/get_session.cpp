#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

vector<string> getSession()
{
    // dapetin sesi saat ini kalau login berhasil
    string line;
    ifstream rsession("./database/session.csv", ios::app);
    if (!rsession)
    {
        cout << "Sesi tidak ditemukan!" << endl;
        return {""};
    }
    cout << "\n";

    getline(rsession, line);
    stringstream ss(line);
    string session_id;
    string session_surel;
    string session_kata_sandi;
    string session_nama_pengguna;

    getline(ss, session_id, ',');
    getline(ss, session_surel, ',');
    getline(ss, session_kata_sandi, ',');
    getline(ss, session_nama_pengguna, ',');

    vector<string> current_session = {session_id, session_surel, session_kata_sandi, session_nama_pengguna};

    return current_session;
}