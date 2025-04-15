#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct recipe_makanan {
    string nama_hidangan;
    string bahan_bahan;
    string cara_memasak;
};

int main() {
    FILE* file = fopen("database/recipe.csv", "r");
    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return 1;
    }

    recipe_makanan daftar[100];
    int jumlah = 0;

    // Gunakan char[] untuk buffer sementara
    char buffer_nama[100], buffer_bahan[200], buffer_cara[300];

    // Baca file dan masukkan ke struct dengan string
    while (fscanf(file, " %99[^,], %199[^,], %[^\n]\n", 
        buffer_nama, buffer_bahan, buffer_cara) == 3) {

        daftar[jumlah].nama_hidangan = buffer_nama;
        daftar[jumlah].bahan_bahan = buffer_bahan;
        daftar[jumlah].cara_memasak = buffer_cara;
        jumlah++;
    }
    fclose(file);

    // Tampilkan data
    cout << "======================\n";
    cout << "Daftar Resep\n";
    cout << "======================\n";
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << daftar[i].nama_hidangan << endl;
    }

    // Pilih data yang akan dihapus
    int hapus;
    cout << "Masukkan nomor resep yang ingin dihapus: ";
    cin >> hapus;

    if (hapus < 1 || hapus > jumlah) {
        cout << "Nomor tidak valid!" << endl;
        return 1;
    }

    // Tulis ulang ke file, kecuali data yang dihapus
    file = fopen("database/recipe.csv", "w");
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return 1;
    }

    for (int i = 0; i < jumlah; i++) {
        if (i != hapus - 1) {
            fprintf(file, "%s, %s, %s\n",
                daftar[i].nama_hidangan.c_str(),
                daftar[i].bahan_bahan.c_str(),
                daftar[i].cara_memasak.c_str());
        }
    }
    fclose(file);

    cout << "Resep berhasil dihapus!" << endl;
    return 0;
}
