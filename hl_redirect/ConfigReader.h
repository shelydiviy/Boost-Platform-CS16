#ifndef CONFIG_READER
#define CONFIG_READER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <algorithm>

namespace fs = std::experimental::filesystem;

class ConfigReader
{
public:
    ConfigReader(const char* server_names_file, const char* config_files_path);
    std::vector<std::string> GetServerNames();

private:
    std::string m_ServerNamesFile;
    std::string m_ConfigFilesPath;

    std::vector<std::string> m_ServerNames;
    std::vector<std::string> m_PlayerNames;

    std::vector<std::string> GetFileContent(std::string file_name);
};

#endif
