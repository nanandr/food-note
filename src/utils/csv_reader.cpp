#include "utils/csv_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void readCSV(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Gagal membuka file: " << filename << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;

        while (getline(ss, value, ','))
        {
            cout << value << " | ";
        }

        cout << endl;
    }

    file.close();
}
