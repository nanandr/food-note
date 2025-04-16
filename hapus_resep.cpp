#include <iostream>
#include <fstream>
using namespace std;

struct recipe_makanan {
    string nama_hidangan;
    string bahan_bahan;
    string cara_memasak;
};

void show_recipe(recipe_makanan daftar[], int jumlah) 
{
    cout << "======================\n";
    cout << "Daftar Resep\n";
    cout << "======================\n";
    for (int i = 0; i < jumlah; i++) 
    {
        cout << i + 1 << ". " << daftar[i].nama_hidangan << endl;
    }
}

int choose_recipe(int jumlah) 
{
    int urutan;
    while (true) 
    {
        cout << "Masukkan nomor resep yang ingin dihapus: ";
        cin >> urutan;

        if (urutan >= 1 && urutan <= jumlah) 
        {
            return urutan - 1;
        } else {
            cout << "Nomor tidak valid! Silahkan coba lagi.\n\n";
        }
    }
}


void delete_recipe(int nomor, int jumlah, recipe_makanan daftar[]) 
{
    ofstream file("database/recipe.csv");
    if (!file.is_open()) 
    {
        cout << "Gagal membuka file" << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        if (i != nomor) {
            file << daftar[i].nama_hidangan << ", "
                 << daftar[i].bahan_bahan << ", "
                 << daftar[i].cara_memasak << "\n";
        }
    }

    file.close();
    cout << "Resep berhasil dihapus!" << endl;
}

int main() 
{
    FILE* file = fopen("database/recipe.csv", "r");
    if (!file) 
    {
        cout << "File tidak ditemukan!" << endl;
        return 1;
    }

    recipe_makanan daftar[100];
    int jumlah = 0;

    char buffer_nama[100], buffer_bahan[200], buffer_cara[300];

    while (fscanf(file, " %99[^,], %199[^,], %[^\n]\n", 
        buffer_nama, buffer_bahan, buffer_cara) == 3) 
        {
        daftar[jumlah].nama_hidangan = buffer_nama;
        daftar[jumlah].bahan_bahan = buffer_bahan;
        daftar[jumlah].cara_memasak = buffer_cara;
        jumlah++;
    }
    fclose(file);

    show_recipe(daftar, jumlah);
    int nomor = choose_recipe(jumlah);
    delete_recipe(nomor, jumlah, daftar);

    return 0;
}
