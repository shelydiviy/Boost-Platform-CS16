#include "Server.h"


Server::Server(const char* address, const int port)
{
    m_ServerSock = new Socket();

    m_ServerSock->m_SocketHandler = (SocketHandler)socket(AF_INET, SOCK_DGRAM, 0);

    if (m_ServerSock->m_SocketHandler < 0)
    {
        perror("Failed to create the socket");
        exit(EXIT_FAILURE);
    }

    const int opt = 1;

    if (setsockopt(m_ServerSock->m_SocketHandler, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Failed to attach socket.\n");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, address, &(serv_addr.sin_addr));
    
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

    int flags = fcntl(m_ServerSock->m_SocketHandler, F_GETFL, 0);
    fcntl(m_ServerSock->m_SocketHandler, F_SETFL, flags | O_NONBLOCK);

    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    ssize_t bytesRead;
    char buffer[1024];
    char clientAddress[INET_ADDRSTRLEN];

    while (m_ShouldRun)
    {
        bytesRead = recvfrom(m_ServerSock->m_SocketHandler, buffer, sizeof(buffer), 0, (sockaddr*)&clientAddr, &clientAddrLen);
        
        if (bytesRead == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                continue;

            perror("Error while reading UDP packets:\n");
            continue;
        }

        if (bytesRead == 0)
            continue;

        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientAddress, INET_ADDRSTRLEN);

        if (    static_cast<unsigned char>(buffer[0]) != 0xFF
            ||  static_cast<unsigned char>(buffer[1]) != 0xFF
            ||  static_cast<unsigned char>(buffer[2]) != 0xFF
            ||  static_cast<unsigned char>(buffer[3]) != 0xFF)
        {
            std::cout << "Client '" << clientAddress << "' may have tried to send an invalid Valve UDP Packet.";
            continue;
        }

        //std::cout << "Received data from client (" << clientAddress << ") with a size of " << bytesRead << ": " << buffer << "\n";

        removeNullBytes(buffer);

        std::cout << "Received '" << buffer << "' from address " << clientAddress << "\n";
    
        if (buffer[13] == 's' && buffer[14] == 't' && buffer[15] == 'e')
        {
            std::cout << "Steam ON player tries to connect to the redirect\n";
        }
        else if (buffer[13] == 'v' && buffer[14] == 'a' && buffer[15] == 'l')
        {
            std::cout << "Steam OFF (VALVER) trie to connect to the redirect\n";
        }
        else
        {
            std::cout << "Undentified user tried to connect to the redirect\n";
        }
    }
}

void Server::removeNullBytes(char* buffer) {
    size_t iLen = strlen(buffer);
    char tempBuffer[iLen - 3];

    size_t i = 4;
    size_t j = 0;

    while (i < iLen) {
        if (buffer[i] == '\0' || buffer[i] == '\n') {
            ++i;
            continue;
        }

        tempBuffer[j] = buffer[i];
        ++i;
        ++j;
    }

    tempBuffer[j] = '\0';

    std::memset(buffer, '\0', iLen);
    std::memcpy(buffer, tempBuffer, j + 1);
}
