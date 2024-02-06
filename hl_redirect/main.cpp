#include <iostream>
#include <string>
#include <cstdint>

#include "Redirect.h"
#include "ConfigReader.h"

//constexpr const char* TARGET_IPV4_ADDRESS = "5.252.100.158";
constexpr const char* TARGET_IPV4_ADDRESS = "51.68.162.219";
constexpr const uint16_t TARGET_PORT = 27015;

constexpr const char* REDIRECT_IPV4_ADDRESS = "188.241.241.248";
//constexpr const char* REDIRECT_IPV4_ADDRESS = "54.37.90.50";
constexpr const uint16_t REDIRECT_PORT = 27215;

constexpr const char* SERVER_NAMES_FILE = "server_names.txt";
constexpr const char* CONFIG_FILES_PATH = "/root/projects/hl_redirect/";
//constexpr const int REDIRECTS = 21;
constexpr const int REDIRECTS = 63;

int main(int argc, char* argv[])
{
	ConfigReader configReader(SERVER_NAMES_FILE, CONFIG_FILES_PATH);
	
	std::vector<std::string> vServerNames = configReader.GetServerNames();
	//std::vector<std::string> vPlayerNames = configReader.GetPlayerNames();
	std::vector<std::string> vPlayerNames;

	Redirect* redirect = new Redirect(REDIRECT_IPV4_ADDRESS, REDIRECT_PORT, TARGET_IPV4_ADDRESS, TARGET_PORT, REDIRECTS, vServerNames, vPlayerNames);

	redirect->StartRedirects();

	return 1;
}