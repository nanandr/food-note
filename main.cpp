/* 
UTS SDA KELOMPOK 4 
Aplikasi Manajemen Resep Makanan (Food Note)

1. Nandana Rafi Ardika (2404158)
2. Hilmi Mithwa Ramadhan (2404042)
3. Febriansyah Nugraha (2408163)
4. Raden Hamizan Rizky Kusuma (2403657)
5. Raihan Fauzi Rakhman (2403872)
*/

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

struct Ingredient {
    string name;
    string amount;
    Ingredient *next;
};

struct Recipe {
    string name;
    Ingredient* ingredient;
    vector<string> steps;
};

int main() {
    // navigation value
    int nav = 0;

    // main loop
    while (true) {
    // title
    // title();

    // navigation
    // int nav = navigate_to({"Buat Resep Baru", "Daftar Resep", "Cari Resep", "Keluar"});
    
    // Buat Resep Baru
        if (nav == 1) {
            Recipe recipe;

            Ingredient* tail = nullptr;

            int i = 0;
            int j = 0;
            string name, amount, step;

            // header("Buat Resep Baru");
            cout << "Nama Hidangan: ";
            cin >> recipe.name;
            // cout << border_thin;
            
            cout << "Bahan-bahan: \n";
            // input loop, type 0 to finish
            while (true) {
                cout << "[" << i+1 << "] Nama Bahan: ";
                cin >> name;
                if (name == "0") break;

                cout << "     Jumlah: ";
                cin >> amount;
                
                Ingredient* ingredient = new Ingredient;
                ingredient->name = name;
                ingredient->amount = amount;
                ingredient->next = nullptr;

                if (recipe.ingredient == nullptr) {
                    recipe.ingredient = ingredient;
                }
                else {
                    tail->next = ingredient;
                }
                tail = ingredient;
                i++;
            }

            // Cara memasak:
            // border_thin();
            cout << "Cara memasak: \n";
            // steps loop
            while (true) {
                cout << "[" << i+1 << "] ";
                cin >> step;
                if (step == "0") break;

                // put to steps vector
            }
        }
        // Daftar Resep
        else if (nav == 2) {
            // header("Daftar Resep");
            
        } 
        // Cari Resep
        else if (nav == 3) {
            // header("Cari Resep");
            
        }
        // Keluar
        else if (nav == 0) {
            break;
        }
    }
}