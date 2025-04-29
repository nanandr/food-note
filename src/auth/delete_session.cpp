
#include "utils/get_db_path.h"
#include "auth/delete_session.h"
#include <iostream>
#include <fstream>
using namespace std;

void deleteSession()
{
    string db_path = getDBPath("session.csv");

    ofstream file(db_path, ios::trunc);

    if (file.is_open())
    {
        file.close();
    } else
    {
        cout << "Gagal menghapus sesi." << endl;
    }
}