#include "utils/borders.h"
#include "utils/nav.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void title(string *text)
{
    cout << border_thin;
    cout << *text << endl;
    cout << border_thin;
}

void recipeNotFound()
{
    string judul = "Resep tidak ditemukan";
    title(&judul);
    nav({"Kembali"});
    return;
}