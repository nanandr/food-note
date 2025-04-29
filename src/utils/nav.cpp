#include "utils/nav.h"
#include "utils/borders.h"
#include <iostream>
#include <vector>
using namespace std;

int nav(const vector<string> &pages)
{
    int choice;
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i] == "Kembali" || pages[i] == "Keluar")
        {
            cout << "[0] " << pages[i] << endl;
        }
        else
        {
            cout << "[" << i + 1 << "] " << pages[i] << endl;
        }
    }
    cout << border_thin;
    cout << "Navigasi ke halaman: ";
    cin >> choice;
    while (cin.fail())
    {
        cout << "Input tidak valid. Harap masukkan angka." << endl;
        cout << "> ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> choice;
    }
    cout << choice << endl;
    return choice;
}