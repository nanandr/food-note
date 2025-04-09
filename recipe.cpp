#include <stdio.h>
#include <iostream>
using namespace std;

struct bahan {
    string nama;
    string takaran;
    bahan *next;
};

struct Recipe {
    string nama_makanan;
    bahan bahan;
    string langkah_langkah[];
};

Recipe r1;
