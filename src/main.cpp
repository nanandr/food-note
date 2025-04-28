/*
UTS SDA KELOMPOK 4
Aplikasi Manajemen Resep Makanan (Food Note)

1. Nandana Rafi Ardika (2404158)
2. Hilmi Mithwa Ramadhan (2404042)
3. Febriansyah Nugraha (2408163)
4. Raden Hamizan Rizky Kusuma (2403657)
5. Raihan Fauzi Rakhman (2403872)
*/

#include "../include/recipe/add_recipe.h"
#include "../include/recipe/delete_recipe.h"
#include "../include/recipe/edit_recipe.h"
#include "../include/recipe/find_recipe.h"
#include "../include/recipe/recipe_struct.h"
#include "../include/recipe/recipe_not_found.h"
#include "../include/recipe/show_all_recipe.h"
#include "../include/recipe/show_main_menu.h"

#include "../include/auth/login_menu.h"
#include "../include/auth/login_signup_menu.h"
#include "../include/auth/register_menu.h"
#include "../include/auth/get_session.h"
#include "../include/auth/delete_session.h"
#include "../include/auth/get_latest_userid.h"

#include "../include/utils/clear_screen.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

string border_thick = "======================== \n";
string border_thin = "------------------------ \n";

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

int main()
{
    int nav = 0;
    bool logout = false;

    // login/register loop
    while (true)
    {
        loginSignupMenu();
        cin >> nav;
        clearScreen();

        if (nav == 1)
        {
            while(true) {
                int login_status = loginMenu();

                if (login_status == 1)
                {
                    // dapetin sesi saat ini kalau login berhasil
                    vector<string> current_session = getSession();
                    
                    clearScreen();
                    cout << "Anda berhasil masuk." << endl;
                    cout << "Selamat datang " << current_session[3] << "!" << endl;
                    nav = 0;
    
                    while (true)
                    {
                        showMainMenu();
                        cin >> nav;
    
                        // Buat Resep Baru
                        if (nav == 1)
                        {
                            clearScreen();
                            addRecipe();
                        }
                        // Daftar Resep
                        else if (nav == 2)
                        {
                            clearScreen();
                            showAllRecipe();
                        }
                        // Cari Resep
                        else if (nav == 3)
                        {
                            clearScreen();
                            findRecipe();
                        }
                        // Edit Resep
                        else if (nav == 4)
                        {
                            clearScreen();
                            editRecipe();
                        }
                        // Delete Resep
                        else if (nav == 5)
                        {
                            clearScreen();
                            deleteRecipe();
                        }
                        // Keluar
                        else if (nav == 0)
                        {
                            clearScreen();
                            deleteSession();
                            logout = true;
                            break;
                        }
                        else
                        {
                            cout << "Input tidak valid!" << endl;
                        }
                    }
                }
                else if (login_status == 0)
                {
                    cout << "Surel atau kata sandi salah. Harap ulangi kembali." << endl;
                }
                else if (login_status == -1)
                {
                    break;
                }

                // langsung ke halaman awal kalau udah logout
                if (logout) break;
            }
        }
        else if (nav == 2)
        {
            registerMenu();
        }
        else if (nav == 3)
        {
            cout << "Terima kasih telah menggunakan Food Note!";
            deleteSession();
            break;
        }
        else
        {
            cout << "Input tidak valid." << endl;
        }
    }
}