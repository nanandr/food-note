#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::string getDBPath(std::string db_csv)
{
    fs::path project_root = fs::current_path();
    fs::path file_path = project_root / "database" / db_csv;

    return file_path.string();
}