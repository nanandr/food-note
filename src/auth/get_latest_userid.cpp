
#include "utils/get_db_path.h"
#include "auth/get_latest_userid.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int getLatestUserId()
{
    string db_path = getDBPath("users.csv");

    ifstream file(db_path, ios::app);
    string line;
    int maxId = 0;

    if (!file) {
        cout << "Basis data tidak ditemukan!" << endl;
        return 0;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');
        
        int id = stoi(idStr); // stoi: string to integer
        if (id > maxId) {
            maxId = id;
        }
    }

    int nextId = maxId + 1;

    return nextId;
}