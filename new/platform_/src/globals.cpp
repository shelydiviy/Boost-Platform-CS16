#include "globals.hpp"
#include <steam_api.h>

Console* PlatformConsole;
size_t MAX_SOCKET_BUFFER_LENGTH = 2048;
const char* IPV4_ADDRESS = "51.89.8.25";

void InitGlobals()
{
	PlatformConsole = new Console();
	PlatformConsole->InitConsole(true);

	Printf("[WARNING] Socket it's temporarly configured only for UDP stream!\n");
}

void InitSteam()
{
	if (!SteamAPI_Init())
	{
		Printf("[CRITICAL] Failed to init Steam API.\n");
		exit(EXIT_FAILURE);
	}

	Printf("Steam API has been initialized succesfully.\n");
}