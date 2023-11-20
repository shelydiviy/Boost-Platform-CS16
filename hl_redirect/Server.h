#ifndef _SERVER_GUARD
#define _SERVER_GUARD

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <arpa/inet.h>


typedef uint8_t SocketHandler;

struct Socket {

public:
	 SocketHandler m_SocketHandler;
	 sockaddr_in m_SocketAddrStruct;
};


class Server
{
public:
	Server();
	void StartListening();

private:
	Socket* m_ServerSock;
	bool m_ShouldRun;
};
#endif