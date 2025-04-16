/*
UTS SDA KELOMPOK 4
Aplikasi Manajemen Resep Makanan (Food Note)

1. Nandana Rafi Ardika (2404158)
2. Hilmi Mithwa Ramadhan (2404042)
3. Febriansyah Nugraha (2408163)
4. Raden Hamizan Rizky Kusuma (2403657)
5. Raihan Fauzi Rakhman (2403872)
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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

void app_name(const std::string &text)
{
    cout << border_thick;
    cout << text << endl
         << endl;
    cout << border_thick;
}

void title(string* text) {
    cout << border_thin;
    cout << *text << endl << endl;
    cout << border_thin;
}

void show_main_menu()
{
    cout << "\n";
    cout << "========================"    << endl;
    cout << "|                      |"    << endl;
    cout << "|      Food Note       |"    << endl;
    cout << "|                      |"    << endl;
    cout << "========================"    << endl;
    cout << "|[1] Buat Resep Baru   |"    << endl;
    cout << "|[2] Daftar Resep      |"    << endl;
    cout << "|[3] Cari Resep        |"    << endl;
    cout << "|[4] Edit Resep        |"    << endl;
    cout << "|[5] Hapus Resep       |"    << endl;
    cout << "|[0] Keluar            |"    << endl;
    cout << "|                      |"  << endl;
    cout << "------------------------"    << endl;
    cout << "Navigasi ke halaman > ";
}

/*
TAMBAH RESEP MAKANAN
*/
void tambah_resep_makanan()
{
    Recipe resep;
    ofstream file("./database/recipe.csv", ios::app);

    if (!file)
    {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    cout << "\n" ;

    cout << border_thick;
    cout << "| Tambah Resep Makanan |" << endl;
    cout << border_thick;

    cout << "Nama Hidangan: ";
    cin.ignore();
    getline(cin, resep.name);

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
    resep.ingredient = head;

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
        resep.steps.push_back(step);
        step_count++;
    }

    file << "\"" << resep.name << "\","; // simpen ke dalam format csv

    // BAHAN-BAHAN
    stringstream ingreadientStream;
    Ingredient *current = resep.ingredient;
    while (current)
    {
        ingreadientStream << current->name << ":" << current->amount;
        if (current->next)
            ingreadientStream << ";";
        current = current->next;
    }
    file << "\"" << ingreadientStream.str() << "\",";

    // LANGKAH-LANGKAH
    stringstream stepsStream;
    for (size_t i = 0; i < resep.steps.size(); i++)
    {
        stepsStream << resep.steps[i];
        if (i != resep.steps.size() - 1)
            stepsStream << "|";
    }
    file << "\"" << stepsStream.str() << "\"" << endl;

    file.close();
    cout << "Resep makanan berhasil ditambahkan." << endl;
}

/*
LIHAT RESEP MAKANAN
*/
void lihat_resep_makanan()
{
    ifstream file("./database/recipe.csv");
    if (!file)
    {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    string line;
    cout << " ---------- Daftar Resep Makanan ---------- " << endl;
    while (getline(file, line))
    {
        stringstream ss(line);
        string nama, bahanCSV, langkahCSV;

        getline(ss, nama, ',');
        getline(ss, bahanCSV, ',');
        getline(ss, langkahCSV, ',');

        if (!nama.empty() && nama.front() == '"')
            nama = nama.substr(1, nama.size() - 2);
        if (!bahanCSV.empty() && bahanCSV.front() == '"')
            bahanCSV = bahanCSV.substr(1, bahanCSV.size() - 2);
        if (!langkahCSV.empty() && langkahCSV.front() == '"')
            langkahCSV = langkahCSV.substr(1, langkahCSV.size() - 2);

        cout << "Nama Hidangan : " << nama << endl;

        cout << "Bahan-bahan   :" << endl;
        stringstream bahanSS(bahanCSV);
        string pair;
        while (getline(bahanSS, pair, ';'))
        {
            size_t pos = pair.find(':');
            if (pos != string::npos)
            {
                string ingName = pair.substr(0, pos);
                string ingAmount = pair.substr(pos + 1);
                cout << "- " << ingName << " (" << ingAmount << ")" << endl;
            }
        }

        cout << "Cara Memasak  :" << endl;
        stringstream langkahSS(langkahCSV);
        string step;
        int stepNum = 1;
        while (getline(langkahSS, step, '|'))
        {
            cout << "Langkah " << stepNum++ << ": " << step << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    file.close();
}

/*
UPDATE RESEP MAKANAN
*/
void edit_resep_makanan()
{
    ifstream file("./database/recipe.csv");
    if (!file.is_open())
    {
        cout << "Database tidak ditemukan!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    getline(file, line);
    lines.push_back(line);

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    int id;
    cout << "Masukkan ID resep yang ingin diedit; ";
    cin >> id;
    cin.ignore();

    bool found = false;

    for (int i = 1; i < lines.size(); i++)
    {
        stringstream ss(lines[i]);
        string token;
        getline(ss, token, ',');
        int currentID = stoi(token);

        if (currentID == id)
        {
            found = true;
            string nama, bahan, langkah;
            getline(ss, nama, ',');
            getline(ss, bahan, ',');
            getline(ss, langkah, ',');

            cout << "Resep ditemukan!" << endl;
            cout << "Nama Hidangan: " << nama << endl;
            cout << "Bahan-bahan: " << bahan << endl;

            cout << "Cara Memasak: ";
            stringstream streamStep(langkah);
            string step;
            int nomor = 1;
            while (getline(streamStep, step, '|'))
            {
                cout << " " << nomor++ << ". " << step << endl;
            }

            string input;

            cout << "\nMasukkan nama hidangan baru (jika kosong = tidak diubah): ";
            getline(cin, input);
            if (!input.empty())
                nama = input;

            cout << "Masukkan bahan-bahan baru (jika kosong = tidak diubah): ";
            getline(cin, input);
            if (!input.empty())
                bahan = input;

            cout << "Masukkan langkah memasak baru (JIKA SELESAI, KETIK end): ";

            string langkahBaru = "", barisLangkah;
            int nomors = 1;
            while (true)
            {
                cout << nomors++ << ".";
                getline(cin, barisLangkah);
                if (barisLangkah == "end")
                    break;
                if (!langkahBaru.empty())
                    langkahBaru += "|";
                langkahBaru += barisLangkah;
            }
            if (!langkahBaru.empty())
                langkah = langkahBaru;

            lines[i] = to_string(currentID) + "," + nama + "," + bahan + "," + langkah;
            break;
        }
    }

    if (!found)
    {
        cout << "Resep tidak ditemukan!" << endl;
        return;
    }

    ofstream outFile("./database/recipe.csv");
    for (const string &l : lines)
    {
        outFile << l << "\n";
    }
    outFile.close();

    cout << "Resep berhasil diperbarui!" << endl;
}

/*
ALGORITMA MENCARI RESEP
*/
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
    if (choice < 0 || choice > pages.size())
    {
        cout << "Pilihan tidak valid" << endl;
        return -1;
    }
    cout << endl;
    return choice;
}

void lihat_semua_resep_makanan()
{
    ifstream *file = new ifstream("database/recipe.csv");
    if (!file->is_open())
    {
        cout << "Database tidak ditemukan!" << endl;
        delete file;
        return;
    }

    string line;
    cout << " ---------- Daftar Resep Makanan ---------- " << endl;
    while (getline(*file, line))
    {
        cout << line << endl;
    }
    file->close();
    delete file;
    cout << "-------------------------------------------" << endl;
}

void resep_gkada()
{
    string judul = "Resep tidak ditemukan";
    title(&judul);
    nav({"Kembali"});
}

void cari_resep_makanan()
{
    cin.ignore();
    string judul = "Cari Resep";
    title(&judul);

    string keyword;
    cout << "Nama Hidangan: ";
    getline(cin, keyword);

    cout << border_thin;

    ifstream *file = new ifstream("database/recipe.csv");
    if (!file->is_open())
    {
        cout << "Database tidak ditemukan!" << endl;
        delete file;
        return;
    }

    string line;
    bool found = false;
    while (getline(*file, line))
    {
        stringstream ss(line);
        string id, namaResep, bahan, langkah;
        getline(ss, id, ',');
        getline(ss, namaResep, ',');
        getline(ss, bahan, ',');
        getline(ss, langkah);

        if (keyword == namaResep)
        {
            cout << "Resep ditemukan!\n";
            cout << "Nama   : " << namaResep << endl;
            cout << "Bahan  : " << bahan << endl;
            cout << "Langkah: " << langkah << endl;
            found = true;
            break;
        }
    }

    file->close();
    delete file;

    if (!found)
    {
        resep_gkada();
    }
}

/*
HAPUS RESEP MAKANAN
*/
int pilih_resep_akan_dihapus(int jumlah)
{
    int urutan;
    while (true)
    {
        cout << "Masukkan nomor resep yang ingin dihapus: ";
        cin >> urutan;

        if (urutan >= 1 && urutan <= jumlah)
        {
            return urutan - 1;
        }
        else
        {
            cout << "Nomor tidak valid! Silahkan coba lagi.\n\n";
        }
    }
}

void hapus_resep(int nomor, int jumlah, Recipe daftar[])
{
    ofstream file("database/recipe.csv");
    if (!file.is_open())
    {
        cout << "Gagal membuka file" << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++)
    {
        if (i != nomor)
        {
            // jadiin steps biar satu string aja
            string combinedSteps;
            for (size_t j = 0; j < daftar[i].steps.size(); ++j)
            {
                combinedSteps += daftar[i].steps[j];
                if (j != daftar[i].steps.size() - 1)
                {
                    combinedSteps += " | ";
                }
            }

            file << daftar[i].name << ", "
                 << daftar[i].ingredient << ", "
                 << combinedSteps << "\n";
        }
    }

    file.close();
    cout << "Resep berhasil dihapus!" << endl;
}

int main()
{
    int nav = 0;

    // main loop
    while (true)
    {
        show_main_menu();
        cin >> nav;

        // Buat Resep Baru
        if (nav == 1)
        {
            tambah_resep_makanan();
        }
        // Daftar Resep
        else if (nav == 2)
        {
            lihat_resep_makanan();
        }
        // Cari Resep
        else if (nav == 3)
        {
            cari_resep_makanan();
        }
        // Edit Resep
        else if (nav == 4)
        {
            edit_resep_makanan();
        }
        // Delete Resep
        else if (nav == 5)
        {
            lihat_resep_makanan();
        }

        // Keluar
        else if (nav == 0)
        {
            break;
        }

        else
        {
            cout << "Input tidak valid!" << endl;
        }
    }
}