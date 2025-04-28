#include "delete_session.h"
#include <iostream>
#include <fstream>
using namespace std;

void deleteSession()
{
    ofstream file("../database/session.csv", ios::trunc);

    if (file.is_open())
    {
        file.close();
    } else
    {
        cout << "Gagal mengapus sesi." << endl;
    }
}