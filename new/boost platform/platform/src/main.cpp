/*
	TODO:
		- Create ThreadPoll classes.
		- Create exit program functionality (for all threads to be stopped correctly).
*/

#include "globals.hpp"
#include "fake_server.hpp"
#include "platform_manager.hpp"
#include "chrono"

int main(int argc, char* argv[])
{
	InitGlobals();

	//if (argc != 4)
	//{
	//	Console::get()->Printf("Invalid number of arguments: %i", argc);
	//	return EXIT_FAILURE;
	//}

	PlatformManager::get()->RegisterSteamCallbacks();
	PlatformManager::get()->StartSteamCallbacksThread();

	//char* ports[2];

	//for (int i = 0; i < argc; i++)
	//{
	//	if (strcmp(argv[i], "--gs_port"))
	//	{
	//		ports[0] = argv[i + 1];
	//	}

	//	if (strcmp(argv[i], "--ms_port"))
	//	{
	//		ports[1] = argv[i + 1];
	//	}
	//}


	PlatformManager::get()->StartFakeServers(10);

	
	std::string input;
	std::cin >> input;

	return 1;
}