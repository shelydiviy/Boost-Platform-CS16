#include <iostream>
#include "Server.h"

#define ADDRESS "145.239.138.255"
#define PORT 27016

int main(int argc, char* argv[])
{
	std::cout << "Starting server...\n";

	Server* server = new Server(ADDRESS, PORT);
	server->StartListening();

	return 1;
}