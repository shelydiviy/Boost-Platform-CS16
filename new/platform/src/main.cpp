#include <thread>
#include "globals.hpp"
#include "fake_server.hpp"
#include <cstdint>
#include <chrono>

/*
	TODO:
		- Create ThreadPoll classes.
		- Create exit program functionality (for all threads to be stopped correctly).
*/

int main()
{
	InitGlobals();
	//InitSteam();

	int16_t iFakeNum = 2;
	int16_t iStartPort = 27016;
	FakeServer* fakeServer = nullptr;
	std::vector<FakeServer*> fakeServers;

	for (
		int16_t iGamePort = iStartPort,
		iMasterServerPort = 21000;
		iGamePort != iStartPort + iFakeNum;
		iGamePort++ && iMasterServerPort++
		)
	{
		fakeServer = new FakeServer(iGamePort, iMasterServerPort);
		fakeServers.push_back(fakeServer);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	std::string input;

	while (true)
	{
		std::cin >> input;

		if (input == "increase_players")
		{
			fakeServer->IncreasePlayers();
		}
		else if(input == "decrease_players")
		{
			fakeServer->DecreasePlayers();
		}
	}

	return 1;
}