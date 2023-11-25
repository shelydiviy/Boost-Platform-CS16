#ifndef _SERVER_GUARD
#define _SERVER_GUARD

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <cstdint>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <string.h>
#include <cerrno>

typedef int SocketHandler;

struct Socket {

public:
	 SocketHandler m_SocketHandler;
	 sockaddr_in m_SocketAddrStruct;
};

class Server
{
public:
	Server(const char* address, const int port);
	void StartListening();

private:
	Socket* m_ServerSock;
	bool m_ShouldRun;

	void removeNullBytes(char* buffer, char* output);
};
#endif