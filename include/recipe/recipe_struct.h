#ifndef RECIPE_STRUCT_H
#define RECIPE_STRUCT_H

#include <string>
#include <vector>
using namespace std;

struct Bahan {
    string nama_bahan;
    string takaran;
    Bahan* next;
};

struct Recipe {
    string name;
    Bahan* ingredient;
    vector<string> steps;
};

#endif