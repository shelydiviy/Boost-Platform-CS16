#include <iostream>
#include "Server.h"
#include <thread>
#include <chrono>
#include <unistd.h>

int main(int argc, char* argv[])
{
	std::cout << "Starting server...\n";

	Server* server = new Server();
	server->StartListening();

	return 1;
}