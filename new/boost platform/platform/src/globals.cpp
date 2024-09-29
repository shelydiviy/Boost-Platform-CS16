#include "globals.hpp"
#include "sys/socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

const size_t MAX_SOCKET_BUFFER_LENGTH = 4096;
const char* IPV4_ADDRESS = "51.89.8.25";
const int STEAM_CALLBACKS_MILLISECOONDS = 15;
uint32 UINT32_IP;

void InitGlobals()
{
	Console::get()->Printf("Initializing globals..\n");

	struct in_addr addr;
	std::memset(&addr, 0, sizeof(addr));
	inet_pton(AF_INET, IPV4_ADDRESS, &addr);
	UINT32_IP = ntohl(addr.s_addr);
}