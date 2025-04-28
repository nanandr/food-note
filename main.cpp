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

void app_name(const std::string &text)
{
    cout << border_thick;
    cout << text << endl
         << endl;
    cout << border_thick;
}

void title(string *text)
{
    cout << border_thin;
    cout << *text << endl;
    cout << border_thin;
}

void hapus_sesi()
{
    ofstream file("./database/session.csv", ios::trunc);

    if (file.is_open())
    {
        file.close();
    } else
    {
        cout << "Gagal mengapus sesi." << endl;
    }
}

vector<string> dapatkan_sesi()
{
    // dapetin sesi saat ini kalau login berhasil
    string line;
    ifstream rsession("./database/session.csv", ios::app);
    if (!rsession)
    {
        cout << "Sesi tidak ditemukan!" << endl;
        return {""};
    }
    cout << "\n";

    getline(rsession, line);
    stringstream ss(line);
    string session_id;
    string session_surel;
    string session_kata_sandi;
    string session_nama_pengguna;

    getline(ss, session_id, ',');
    getline(ss, session_surel, ',');
    getline(ss, session_kata_sandi, ',');
    getline(ss, session_nama_pengguna, ',');

    vector<string> current_session = {session_id, session_surel, session_kata_sandi, session_nama_pengguna};

    return current_session;
}

int get_latest_userid()
{
    ifstream file("./database/users.csv");
    string line;
    int maxId = 0;

    if (!file) {
        cout << "Basis data tidak ditemukan!" << endl;
        return 0;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');
        
        int id = stoi(idStr); // stoi: string to integer
        if (id > maxId) {
            maxId = id;
        }
    }

    int nextId = maxId + 1;

    return nextId;
}

void login_signup_menu()
{
    cout << "\n";
    cout << "===========================" << endl;
    cout << "|                         |" << endl;
    cout << "| Selamat datang di       |" << endl;
    cout << "| Food Note!              |" << endl;
    cout << "| Silahkan masuk/daftar   |" << endl;
    cout << "|                         |" << endl;
    cout << "===========================" << endl;
    cout << "|                         |" << endl;
    cout << "|  [1] Masuk              |" << endl;
    cout << "|  [2] Daftar             |" << endl;
    cout << "|  [3] Hentikan Program   |" << endl;
    cout << "|                         |" << endl;
    cout << "===========================" << endl;
    cout << "Navigasi ke halaman > ";
}

int login_menu()
{
    ifstream rfile("./database/users.csv", ios::app);
    if (!rfile)
    {
        cout << "Basis data tidak ditemukan!" << endl;
        return 0;
    }
    cout << "\n";

    string line;
    string inp_surel_pengguna;
    string inp_kata_sandi;
    char del = ','; // delimiter pemisah string

    cout << "\n";
    cout << "========================" << endl;
    cout << "|                      |" << endl;
    cout << "|  Masuk               |" << endl;
    cout << "|                      |" << endl;
    cout << "========================" << endl;
    cout << "Masukkan surel pengguna (\"kembali\" untuk kembali ke menu awal)" << endl;
    cout << "> ";
    cin >> inp_surel_pengguna;

    // jadiin lowercase buat input surel
    string surel_pengguna_lower = inp_surel_pengguna;
    transform(surel_pengguna_lower.begin(), surel_pengguna_lower.end(), surel_pengguna_lower.begin(), ::tolower);

    // kalau inputannya "kembali" pas input surel, return -1
    int compareInputToExit = surel_pengguna_lower.compare("kembali");
    if (compareInputToExit == 0) {
        return -1;
    }
    cout << "Masukkan kata sandi " << endl;
    cout << "> ";
    cin >> inp_kata_sandi;
    
    // cek tiap baris csv apakah ada yang serupa
    while (getline(rfile, line))
    {
        stringstream ss(line);
        string id;
        string surel;
        string kata_sandi;
        string nama_pengguna;

        getline(ss, id, ',');
        getline(ss, surel, ',');
        getline(ss, kata_sandi, ',');
        getline(ss, nama_pengguna, ',');

        int compareSurel = surel_pengguna_lower.compare(surel);
        int compareKataSandi = inp_kata_sandi.compare(kata_sandi);

        if ((compareSurel == 0) && (compareKataSandi == 0))
        {
            /* 
            hapus sesi yg lama (kalau ada)
            terus bikin sesi baru dari pengguna yang masuk tadi 
            */
            hapus_sesi();

            ofstream wsession("./database/session.csv", ios::app);
            if (wsession.is_open())
            {
                wsession << id << "," << surel << "," << kata_sandi << "," << nama_pengguna << "\n";
                wsession.close();
            }
            else
            {
                cout << "Gagal membuat sesi baru." << endl;
            }

            return 1; // success
        }
    }

    return 0;
}

int register_menu()
{
    string line;
    string inp_surel_pengguna;
    string inp_kata_sandi;
    string inp_nama_pengguna;
    char del = ','; // delimiter pemisah string

    cout << "\n";
    cout << "========================" << endl;
    cout << "|                      |" << endl;
    cout << "|  Daftar Pengguna     |" << endl;
    cout << "|  Baru                |" << endl;
    cout << "|                      |" << endl;
    cout << "========================" << endl;
    cout << "Masukkan surel pengguna (\"kembali\" untuk kembali ke menu awal)" << endl;
    cout << "> ";
    cin >> inp_surel_pengguna;

    // jadiin lowercase buat input surel
    string surel_pengguna_lower = inp_surel_pengguna;
    transform(surel_pengguna_lower.begin(), surel_pengguna_lower.end(), surel_pengguna_lower.begin(), ::tolower);

    // kalau inputannya "kembali" pas input surel, return -1
    int compareInputToExit = surel_pengguna_lower.compare("kembali");
    if (compareInputToExit == 0) {
        return -1;
    }
    cin.ignore();

    cout << "Masukkan nama pengguna" << endl;
    cout << "> ";
    getline(cin, inp_nama_pengguna);
    
    cout << "Buat kata sandi baru" << endl;
    cout << "> ";
    cin >> inp_kata_sandi;

    // ambil id terbesar dan terbaru di users.csv
    int id = get_latest_userid();
    if (id == 0)
    {
        cout << "Gagal mendaftar pengguna baru." << endl;
        return 0;
    }

    // tambah kredensial pengguna baru ke dalem csv, tulis baris baru
    ofstream wregistuser("./database/users.csv", ios::app);
    if (wregistuser.is_open())
    {
        wregistuser << id << "," << inp_surel_pengguna << "," << inp_kata_sandi << "," << inp_nama_pengguna << "\n";
        wregistuser.close();

        cout << "Registrasi Berhasil!" << endl;
    }
    else
    {
        cout << "Gagal mendaftar pengguna baru." << endl;
    }

    return 0;
}

// menghapus screen
void clearScreen ()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux / Mac
    #endif
}

void show_main_menu()
{
    cout << "\n";
    cout << "========================" << endl;
    cout << "|                      |" << endl;
    cout << "|      Food Note       |" << endl;
    cout << "|                      |" << endl;
    cout << "========================" << endl;
    cout << "|                      |" << endl;
    cout << "| [1] Buat Resep Baru  |" << endl;
    cout << "| [2] Daftar Resep     |" << endl;
    cout << "| [3] Cari Resep       |" << endl;
    cout << "| [4] Edit Resep       |" << endl;
    cout << "| [5] Hapus Resep      |" << endl;
    cout << "| [0] Keluar           |" << endl;
    cout << "|                      |" << endl;
    cout << "------------------------" << endl;
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
        cout << "Basis data tidak ditemukan!!" << endl;
        return;
    }

    cout << "\n";

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
        ingreadientStream << current->name << ":" << current->amount << "";
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
    clearScreen ();
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
        cout << "Basis data tidak ditemukan!!" << endl;
        return;
    }

    string line;
    int count_resep = 1;

    cout << border_thick;
    cout << "| Daftar Resep Makanan |" << endl;
    cout << border_thick;
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

        cout << "[" << count_resep << "] " << nama << endl;
        count_resep += 1;
        cout << border_thin;
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
        cout << "Basis data tidak ditemukan!!" << endl;
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

    string keyword;
    cout << "Masukkan nama resep yang ingin diedit: ";
    cin.ignore();
    getline(cin, keyword);

    string keywordLower = keyword;
    transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);
    
    bool found = false;
    
    for (int i = 1; i < lines.size(); i++)
    {
        
        stringstream ss(lines[i]);
        string currentRecipeName, bahan, langkah;
        getline(ss, currentRecipeName, ',');
        getline(ss, bahan, ',');
        getline(ss, langkah, ',');
        
        string namaResepLower = currentRecipeName;
        transform(namaResepLower.begin(), namaResepLower.end(), namaResepLower.begin(), ::tolower);
        
        if (!namaResepLower.empty() && namaResepLower.front() == '"')
        namaResepLower = namaResepLower.substr(1, namaResepLower.size() - 2);

        if (namaResepLower == keywordLower)
        {
            found = true;

            cout << "Nama Resep         : " << currentRecipeName << endl;
            cout << "Bahan-bahan        : " << endl;
            stringstream bahanSS(bahan);
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
            cout << "Cara Memasak: " << endl;
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
                currentRecipeName = "\"" + input + "\"";

            cout << "Masukkan bahan-bahan baru, dengan format [bahan:jumlah;bahan..n] (kosong = tidak diubah): ";
            getline(cin, input);
            if (!input.empty())
                bahan = "\"" + input + "\"";

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
                langkah = "\"" + langkahBaru + "\"";

            lines[i] = currentRecipeName + "," + bahan + "," + langkah;
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

    clearScreen ();
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

void lihat_semua_resep_makanan()
{
    ifstream *file = new ifstream("./database/recipe.csv");
    if (!file->is_open())
    {
        cout << "Basis data tidak ditemukan!!" << endl;
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
    return;
}

void cari_resep_makanan()
{
    cin.ignore();
    cout << border_thick;
    cout << "|  Cari Resep Makanan  |" << endl;
    cout << border_thick;

    string keyword;
    cout << "Nama Hidangan: ";
    getline(cin, keyword);

    ifstream *file = new ifstream("./database/recipe.csv");
    if (!file->is_open())
    {
        cout << "Basis data tidak ditemukan!!" << endl;
        delete file;
        return;
    }

    string line;
    bool found = false;
    while (getline(*file, line))
    {
        stringstream ss(line);
        string namaResep, bahan, langkah;
        getline(ss, namaResep, ',');
        if (!namaResep.empty() && namaResep.front() == '"')
            namaResep = namaResep.substr(1, namaResep.size() - 2);

        getline(ss, bahan, ',');
        getline(ss, langkah);

        // jadiin lowercase dulu keyword sama nama resep nya
        string namaResepLower = namaResep;
        string keywordLower = keyword;
        transform(namaResepLower.begin(), namaResepLower.end(), namaResepLower.begin(), ::tolower);
        transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

        // komparasi keyword dengan namaresep, apakah sama atau tidak
        int compare = keywordLower.compare(namaResepLower);
        if (compare == 0)
        {
            cout << endl;
            cout << border_thin;
            cout << "|   Resep ditemukan!   |\n";
            cout << border_thin;

            cout << "Nama Resep     : " << namaResep << endl;
            cout << "Bahan-bahan    : " << endl;
            stringstream bahanSS(bahan);
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

            cout << "How to Cook    :" << endl;
            stringstream langkahSS(langkah);
            string step;
            int stepNum = 1;
            while (getline(langkahSS, step, '|'))
            {
                cout << "Langkah " << stepNum++ << ": " << step << endl;
            }

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

void hapus_resep()
{
    ifstream file("database/recipe.csv");
    if (!file.is_open())
    {
        cout << "Gagal membuka arsip!" << endl;
        return;
    }

    Recipe daftar[100];
    string line;
    int jumlah = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string nama, bahan, langkah;

        getline(ss, nama, ',');
        getline(ss, bahan, ',');
        getline(ss, langkah);

        // simpan ke array
        daftar[jumlah].name = nama;
        daftar[jumlah].ingredient = nullptr;
        daftar[jumlah].steps.push_back(langkah);
        jumlah++;
    }
    file.close();

    // Tampilkan daftar resep
    cout << "Daftar Resep:\n";
    for (int i = 0; i < jumlah; i++)
    {
        cout << "[" << i + 1 << "] " << daftar[i].name << endl;
    }

    int nomor;
    cout << "Masukkan nomor resep yang ingin dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > jumlah)
    {
        cout << "Nomor tidak valid!" << endl;
        return;
    }

    nomor--;

    ofstream outfile("database/recipe.csv");
    for (int i = 0; i < jumlah; i++)
    {
        if (i == nomor)
            continue;

        outfile << daftar[i].name << ",,\"";
        for (size_t j = 0; j < daftar[i].steps.size(); ++j)
        {
            outfile << daftar[i].steps[j];
            if (j != daftar[i].steps.size() - 1)
                outfile << "|";
        }
        outfile << "\"" << endl;
    }
    outfile.close();

    clearScreen ();
    cout << "Resep berhasil dihapus!" << endl;
}

int main()
{
    int nav = 0;
    bool logout = false;

    // login/register loop
    while (true)
    {
        login_signup_menu();
        cin >> nav;
        clearScreen ();

        if (nav == 1)
        {
            while(true) {
                int login_status = login_menu();

                if (login_status == 1)
                {
                    // dapetin sesi saat ini kalau login berhasil
                    vector<string> current_session = dapatkan_sesi();
                    
                    clearScreen ();
                    cout << "Anda berhasil masuk." << endl;
                    cout << "Selamat datang " << current_session[3] << "!" << endl;
                    nav = 0;
    
                    while (true)
                    {
                        show_main_menu();
                        cin >> nav;
    
                        // Buat Resep Baru
                        if (nav == 1)
                        {
                            clearScreen ();
                            tambah_resep_makanan();
                        }
                        // Daftar Resep
                        else if (nav == 2)
                        {
                            clearScreen ();
                            lihat_resep_makanan();
                        }
                        // Cari Resep
                        else if (nav == 3)
                        {
                            clearScreen ();
                            cari_resep_makanan();
                        }
                        // Edit Resep
                        else if (nav == 4)
                        {
                            clearScreen ();
                            edit_resep_makanan();
                        }
                        // Delete Resep
                        else if (nav == 5)
                        {
                            clearScreen ();
                            hapus_resep();
                        }
                        // Keluar
                        else if (nav == 0)
                        {
                            clearScreen ();
                            hapus_sesi();
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
            register_menu();
        }
        else if (nav == 3)
        {
            cout << "Terima kasih telah menggunakan Food Note!";
            hapus_sesi();
            break;
        }
        else
        {
            cout << "Input tidak valid." << endl;
        }
    }
}