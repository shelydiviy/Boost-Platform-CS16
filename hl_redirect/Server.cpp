#include "Server.h"
#include <fcntl.h>


Server::Server()
{
    m_ServerSock = new Socket();

    m_ServerSock->m_SocketHandler = (SocketHandler)socket(AF_INET, SOCK_DGRAM, 0);

    if (m_ServerSock->m_SocketHandler < 0)
    {
        perror("Failed to create the socket");
        exit(EXIT_FAILURE);
    }

    //const int opt = 1;

    //if (setsockopt(m_ServerSock->m_SocketHandler, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    //    &opt, sizeof(opt)))
    //{
    //    perror("Failed to attach socket.\n");
    //    exit(EXIT_FAILURE);
    //}

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(27016);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(m_ServerSock->m_SocketHandler, (sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
    {
        perror("Failed to bind socket\n");
        exit(EXIT_FAILURE);
    }

    m_ServerSock->m_SocketAddrStruct = serv_addr;
}

void Server::StartListening()
{
    m_ShouldRun = true;

    std::cout << "Server is listening on " << inet_ntoa(m_ServerSock->m_SocketAddrStruct.sin_addr) << ":" << ntohs(m_ServerSock->m_SocketAddrStruct.sin_port) << std::endl;

    //int flags = fcntl(m_ServerSock->m_SocketHandler, F_GETFL, 0);
    //fcntl(m_ServerSock->m_SocketHandler, F_SETFL, flags | O_NONBLOCK);

    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    ssize_t bytesRead;
    char buffer[1024];
    char clientIP[INET_ADDRSTRLEN];


    while (m_ShouldRun)
    {
        bytesRead = recvfrom(m_ServerSock->m_SocketHandler, buffer, sizeof(buffer), 0, (sockaddr*)&clientAddr, &clientAddrLen);

        if (bytesRead > 0)
        {
            inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);

            std::cout << "Received data from client (" << clientIP << ") with a size of " << bytesRead << ": " << buffer << std::endl;
        }
    }
}

