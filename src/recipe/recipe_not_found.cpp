#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

string border_thick = "======================== \n";
string border_thin = "------------------------ \n";

void title(string *text)
{
    cout << border_thin;
    cout << *text << endl;
    cout << border_thin;
}

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

void recipeNotFound()
{
    string judul = "Resep tidak ditemukan";
    title(&judul);
    nav({"Kembali"});
    return;
}