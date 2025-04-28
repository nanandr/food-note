#include "clear_screen.h"
#include "add_recipe.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Ingredient
{
    string name;
    string amount;
    Ingredient *next;
};

struct Recipe
{
    string name;
    Ingredient *ingredient;
    vector<string> steps;
};

string border_thick = "======================== \n";
string border_thin = "------------------------ \n";

/*
TAMBAH RESEP MAKANAN
*/
void addRecipe()
{
    Recipe recipe;
    ofstream file("./database/recipe.csv", ios::app);

    if (!file)
    {
        cout << "Basis data tidak ditemukan!!" << endl;
        return;
    }

    cout << "\n";

    cout << border_thick;
    cout << "| Tambah Resep Makanan |" << endl;
    cout << border_thick;

    cout << "Nama Hidangan: ";
    cin.ignore();
    getline(cin, recipe.name);

    cout << "Masukkan bahan-bahan (ketik 'end' untuk selesai): " << endl;
    Ingredient *head = nullptr, *tail = nullptr;

    while (true)
    {
        string name, amount;

        cout << "Nama bahan: ";
        getline(cin, name);
        if (name == "end")
            break;

        cout << "Jumlah: ";
        getline(cin, amount);

        Ingredient *new_ingredient = new Ingredient{name, amount, nullptr};
        if (!head)
            head = tail = new_ingredient;
        else
        {
            tail->next = new_ingredient;
            tail = new_ingredient;
        }
    }
    recipe.ingredient = head;

    // INPUT LANGKAH-LANGKAH
    cout << "Masukkan cara memasak (ketik 'end' untuk selesai): " << endl;
    int step_count = 1;
    while (true)
    {
        string step;
        cout << "Langkah " << step_count << ": ";
        getline(cin, step);
        if (step == "end")
            break;
        recipe.steps.push_back(step);
        step_count++;
    }

    file << "\"" << recipe.name << "\","; // simpen ke dalam format csv

    // BAHAN-BAHAN
    stringstream ingredient_stream;
    Ingredient *current = recipe.ingredient;
    while (current)
    {
        ingredient_stream << current->name << ":" << current->amount << "";
        if (current->next)
            ingredient_stream << ";";
        current = current->next;
    }
    file << "\"" << ingredient_stream.str() << "\",";

    // LANGKAH-LANGKAH
    stringstream stepsStream;
    for (size_t i = 0; i < recipe.steps.size(); i++)
    {
        stepsStream << recipe.steps[i];
        if (i != recipe.steps.size() - 1)
            stepsStream << "|";
    }
    file << "\"" << stepsStream.str() << "\"" << endl;

    file.close();
    clearScreen();
    cout << "Resep makanan berhasil ditambahkan." << endl;
}