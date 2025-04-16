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