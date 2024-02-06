#include "ConfigReader.h"

ConfigReader::ConfigReader(const char* server_names_file, const char* config_files_path) :
    m_ServerNamesFile(server_names_file), m_ConfigFilesPath(config_files_path)
{
    m_ServerNames = GetFileContent(m_ServerNamesFile);
}

std::vector<std::string> ConfigReader::GetFileContent(std::string file_name)
{
    std::string path = m_ConfigFilesPath + file_name;
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file '" << path << "'." << std::endl;
        exit(-1);
    }

    std::vector<std::string> tempVector;
    std::string line;

    while (std::getline(file, line))
    {
        // Remove both newline and carriage return characters
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        tempVector.push_back(line);
    }

    return tempVector;
}

std::vector<std::string> ConfigReader::GetServerNames()
{
    return m_ServerNames;
}