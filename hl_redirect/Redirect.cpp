#include "Redirect.h"

// Class constructor, initializing sockets and starting threads
Redirect::Redirect(const char* ipv4_address, const uint16_t port, const char* target_ipv4_address, const uint16_t target_port, const uint16_t redirects_number, std::vector<std::string> server_names, std::vector<std::string> player_names) :
	m_ServerNames(server_names), m_PlayerNames(player_names),
	m_IPv4Address((char*) ipv4_address), m_Port(port),
	m_TargetIPv4Address((char*) target_ipv4_address), m_TargetPort(target_port),
	m_TargetSocket(new Socket())
{
	if (m_ServerNames.size() == 0)
	{
		std::cerr << "Not enough server names provided\n";
		exit(EXIT_FAILURE);
	}
                                       
	std::cout << "Starting redirects...\n";
	
	const uint16_t START_PORT = 27216;

    Socket* serverSocket = nullptr;
	std::shared_ptr<FakeServer> fakeServer = nullptr;
	uint16_t currentPort = START_PORT;
	uint16_t failedPorts = 0;
	
	char* tempQueryPacket;
	size_t tempQuerySize;
	size_t serverNamesVectorSize = m_ServerNames.size();

	std::shared_ptr<std::thread> fakeServerThread;


	for (uint16_t iterator = 0; iterator < redirects_number; iterator++)
	{
		serverSocket = new Socket();

		if (!OpenSocket(serverSocket, &currentPort, NO_TIMEOUT))
		{
			failedPorts++;
			currentPort++;
			std::cerr << "Failed to fake server on port " << currentPort << "\n";
			continue;
		}

		fakeServer = std::make_shared<FakeServer>(*serverSocket);

		fakeServer->m_QueryEnginePacket = InterogateHLDSServer(fakeServer.get(), currentPort - 200, fakeServer->m_QueryEnginePacketSize);
		ChangeQueryPacket(fakeServer->m_QueryEnginePacket, fakeServer->m_QueryEnginePacketSize, currentPort - 200);

		fakeServerThread = std::make_shared<std::thread>(&Redirect::StartListening, this, std::move(fakeServer));
		fakeServerThread->detach();

		m_FakeServersThreadPoll.push_back(fakeServerThread);
		
		currentPort++;
	}

	m_iRedirectPort = START_PORT + redirects_number;

	if (failedPorts > 0)
	{
		std::cout << "Failed to open a number of " << failedPorts << " ports\n";
	}

	std::cout << "Started " << m_FakeServersThreadPoll.size() << " redirects\n";

	// Creating target socket address struct
	m_TargetSocket->m_SocketAddrSize = sizeof(m_TargetSocket->m_SocketAddrStruct);
	std::memset(&m_TargetSocket->m_SocketAddrStruct, 0, m_TargetSocket->m_SocketAddrSize);

	m_TargetSocket->m_SocketAddrStruct.sin_family = AF_INET;
	m_TargetSocket->m_SocketAddrStruct.sin_port = htons(m_TargetPort);
	inet_pton(AF_INET, m_TargetIPv4Address, &m_TargetSocket->m_SocketAddrStruct.sin_addr);

	m_ShouldRun = true;
	std::string input;

	while (m_ShouldRun)
	{
		sleep(1);

		std::cin >> input;

		if (input.size() == 0)
		{
			continue;
		}

		if (input == "fake_servers")
		{
			std::cout << "Currently are running a number of " << m_FakeServersThreadPoll.size() << " threads\n";
		}
		else if (input == "clients")
		{
			std::cout << m_ClientsThreadPoll.size() << " clients are connected\n";
		}
		else std::cerr << "Unkown command '" << input << "'\n";

	}

	return;
}

void Redirect::StartListening(std::shared_ptr<FakeServer> fake_server)
{
	Socket receiverSocket{};
	std::shared_ptr<Socket> privateSocket;

	receiverSocket.m_SocketAddrSize = sizeof(receiverSocket.m_SocketAddrStruct);
	std::memset(&receiverSocket.m_SocketAddrStruct, 0, receiverSocket.m_SocketAddrSize);

	char buffer[MAX_BUFFER_LENGTH];
	ssize_t bytesReceived = 0, bytesSent = 0;

	while (true)
	{
		bytesReceived = recvfrom(fake_server->m_Socket.m_SocketHandler, buffer, sizeof(buffer), 0, (sockaddr *) &receiverSocket.m_SocketAddrStruct, &receiverSocket.m_SocketAddrSize);

		if (bytesReceived == SOCKET_ERROR)
		{
			std::cerr << "An error has been occurred while trying to read from socket " << fake_server->GetIPv4Address() << ":" << fake_server->GetPort() << " and the thread stopped\n";
			perror(EMPTY_CHAR);
			break;
		}

		privateSocket = fake_server->GetClientPrivateSocket(std::pair<std::string, uint16_t>(receiverSocket.GetIPv4Address(), receiverSocket.GetPort()));
		
		if (privateSocket != nullptr)
		{
			bytesSent = sendto(privateSocket->m_SocketHandler, buffer, bytesReceived, 0, (sockaddr*)&m_TargetSocket->m_SocketAddrStruct, m_TargetSocket->m_SocketAddrSize);

			if (bytesSent == SOCKET_ERROR)
			{
				perror("Failed to send the challenge packet to the target server");
				return;
			}

			continue;
		}

		if (memcmp(buffer + 4, GET_CHALLANGE_MESSAGE, sizeof(GET_CHALLANGE_MESSAGE)) == 0)
		{
			RegisterUser(fake_server.get(), receiverSocket, buffer);
			std::cout << "[" << fake_server->GetPort() << "]" << " Client " << receiverSocket.GetIPv4Address() << ":" << receiverSocket.GetPort() << " has been registered\n";
			continue;
		}
		if (memcmp(buffer + 4, QUERY_ENGINE_MESSAGE, sizeof(QUERY_ENGINE_MESSAGE)) == 0)
		{
			SendQueryEngineInfo(fake_server.get(), &receiverSocket);
			//std::cout << "[" << fake_server->GetPort() << "]" << " Client " << receiverSocket.GetIPv4Address() << ":" << receiverSocket.GetPort() << " sent query engine message and sent data back from " << fake_server->GetIPv4Address() << ":" << fake_server->GetPort() << "\n";
			continue;
		}
	}
}

void Redirect::StartRedirects()
{
}

void Redirect::RegisterUser(FakeServer* fake_server, const Socket client_socket, const char* get_challenge_packet)
{
	std::shared_ptr<Socket> privateSocket = std::make_shared<Socket>();
	
	if (m_iRedirectPort > 29000)
	{
		m_iRedirectPort = 27415;
	}

	m_iRedirectPort++;

	if (!OpenSocket(privateSocket.get(), &m_iRedirectPort, DEFAULT_CLIENT_SOCKET_TIMEOUT))
	{
		std::cout << "Couldn't open socket at port " << m_iRedirectPort << "\n";
		return;
	}

	std::shared_ptr<std::thread> clientThread = std::make_shared<std::thread>();
	std::thread::id threadID = clientThread->get_id();
	
	std::pair<std::string, uint16_t> key(client_socket.GetIPv4Address(), client_socket.GetPort());

	fake_server->AddClient(key, privateSocket);

	clientThread = std::make_shared<std::thread>(&Redirect::StartListeningClientSocket, this, fake_server, privateSocket, client_socket, threadID);
	clientThread->detach();
	
	ssize_t bytes = sendto(privateSocket->m_SocketHandler, get_challenge_packet, strlen(get_challenge_packet), 0, (sockaddr*)&m_TargetSocket->m_SocketAddrStruct, m_TargetSocket->m_SocketAddrSize);

	if (bytes == SOCKET_ERROR)
	{
		perror("Failed to send the challenge packet to the target server");
		std::cerr << "Error code: " << errno << std::endl;
		fake_server->RemoveClient(key);
		return;
	}
	//std::cout << "Sent " << get_challenge_packet << " size of " << strlen(get_challenge_packet) << "\n";
	
	std::lock_guard<std::mutex>lock(m_ClientsThreadPollMutex);
	m_ClientsThreadPoll.emplace_back(std::move(clientThread));

	return;
}

void Redirect::StartListeningClientSocket(FakeServer* fake_server, std::shared_ptr<Socket> private_socket, const Socket client_socket, const std::thread::id thread_id)
{
	ssize_t receivedBytes, sentBytes;
	char buffer[MAX_BUFFER_LENGTH]{};
	
	while (true)
	{
		receivedBytes = recv(private_socket->m_SocketHandler, buffer, sizeof(buffer), 0);

		if (receivedBytes == SOCKET_ERROR)
		{
			switch (errno)
			{
			case EAGAIN | EWOULDBLOCK:
				goto TIMEOUT_OCCURED;
				break;

			default:
				perror("An error has been occurred while trying to read from private client socket.");
				continue;
			}
		}

		sentBytes = sendto(fake_server->m_Socket.m_SocketHandler, buffer, receivedBytes, 0, (sockaddr*)&client_socket.m_SocketAddrStruct, client_socket.m_SocketAddrSize);

		if (sentBytes == SOCKET_ERROR)
		{
			switch (errno)
			{
			case EAGAIN | EWOULDBLOCK:
				continue;

			default:
				perror("An error has been occurred while trying to send to client using fake server socket.");
				continue;
			}
		}

		//std::cout << "Server sent " << buffer << " to " << client_socket.GetIPv4Address() << ":" << client_socket.GetPort() << "\n";
	}

TIMEOUT_OCCURED:

	private_socket.reset();
	
	std::pair<std::string, uint16_t> key(client_socket.GetIPv4Address(), client_socket.GetPort());
	fake_server->RemoveClient(key);

	std::cout << "Client " << client_socket.GetIPv4Address() << ":" << client_socket.GetPort() << " exited\n";

	std::lock_guard<std::mutex> lock(m_ClientsThreadPollMutex);
	m_ClientsThreadPoll.erase(
			std::remove_if(
				m_ClientsThreadPoll.begin(),
				m_ClientsThreadPoll.end(),
				[thread_id](const std::shared_ptr<std::thread>& thread) {
					return thread->get_id() == thread_id;
				}),
			m_ClientsThreadPoll.end());

	return;
}

void Redirect::SendQueryEngineInfo(const FakeServer* fake_server, const Socket* client_socket) const
{

	ssize_t bytesSent = sendto(fake_server->m_Socket.m_SocketHandler, fake_server->m_QueryEnginePacket, fake_server->m_QueryEnginePacketSize, 0, (sockaddr*)&client_socket->m_SocketAddrStruct, client_socket->m_SocketAddrSize);
	//ssize_t bytesSent = sendto(fake_server->m_Socket.m_SocketHandler, bytes, sizeof(bytes), 0, (sockaddr*)&client_socket->m_SocketAddrStruct, client_socket->m_SocketAddrSize);

	if (bytesSent == SOCKET_ERROR)
	{
		perror("Error sending first query engine packet");
	}

	//std::cout << "[" << fake_server->GetPort() << "]" << " Client " << client_socket->GetIPv4Address() << ":" << client_socket->GetPort() << " sent query engine message and sent data back from " << fake_server->GetIPv4Address() << ":" << fake_server->GetPort() << "\n";
}

bool Redirect::OpenSocket(Socket* sock, uint16_t* port, const int timeout_seconds) const
{
	sock->m_SocketHandler = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (sock->m_SocketHandler == -1) {
		std::cout << "Failed to create socket for port " << *port << "\n";
		perror("Error");
		return false;
	}

	const int opt = 1;

	if (setsockopt(sock->m_SocketHandler, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
		std::cout << "Failed to attach socket for port " << *port << "\n";
		perror("Error");
		return false;
	}

	sock->m_SocketAddrSize = sizeof(sock->m_SocketAddrStruct);
	std::memset(&sock->m_SocketAddrStruct, 0, sock->m_SocketAddrSize);

	sock->m_SocketAddrStruct.sin_family = AF_INET;
	sock->m_SocketAddrStruct.sin_port = htons(*port);
	inet_pton(AF_INET, m_IPv4Address, &sock->m_SocketAddrStruct.sin_addr);

	if (bind(sock->m_SocketHandler, (sockaddr*) &sock->m_SocketAddrStruct, sock->m_SocketAddrSize) != 0)
	{
		std::cout << "Failed to bind socket for port " << *port << "\n";
		perror("Error");
		return false;
	}

	if (timeout_seconds > 0)
	{
		struct timeval timeout {};
		timeout.tv_sec = timeout_seconds;
		timeout.tv_usec = 0;

		if (setsockopt(sock->m_SocketHandler, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
			std::cout << "Failed to set receive timeout for port " << *port << "\n";
			perror("Error");
			return false;
		}
	}

	return true;
}

char* Redirect::InterogateHLDSServer(FakeServer* fake_server, uint16_t hlds_port, size_t& packet_size) const
{
	Socket* hlds = new Socket();

	hlds->m_SocketAddrSize = sizeof(hlds->m_SocketAddrStruct);
	std::memset(&hlds->m_SocketAddrStruct, 0, hlds->m_SocketAddrSize);

	hlds->m_SocketAddrStruct.sin_family = AF_INET;
	hlds->m_SocketAddrStruct.sin_port = htons(hlds_port);
	inet_pton(AF_INET, m_IPv4Address, &hlds->m_SocketAddrStruct.sin_addr);

	ssize_t bytes = sendto(fake_server->m_Socket.m_SocketHandler, "\xff\xff\xff\xffTSource Engine Query\0", 25, 0, (sockaddr *) &hlds->m_SocketAddrStruct, hlds->m_SocketAddrSize);

	if (bytes == SOCKET_ERROR)
	{
		perror("Error while trying to retrieve original TSource Engine Query");
		return "FAILED_TO_SEND";
	}

	char* buffer = new char[MAX_BUFFER_LENGTH];

	while (true)
	{
		bytes = recv(fake_server->m_Socket.m_SocketHandler, buffer, static_cast<size_t>(MAX_BUFFER_LENGTH) + 1, 0);
	
		if (bytes == SOCKET_ERROR)
		{
			switch (errno)
			{
			case EAGAIN:
				std::cerr << "Failed to get HLDS query engine packet from " << hlds->GetIPv4Address() << ":" << hlds->GetPort() << ". Error: ";
				perror(EMPTY_CHAR);
				continue;
			}
		}

		if (bytes > 0)
		{
			packet_size = static_cast<size_t>(bytes);
		}

		break;
	}

	struct timeval timeout {};
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	if (setsockopt(fake_server->m_Socket.m_SocketHandler, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
	{
		perror("Error while resettings fake server timeout.");
	}

	delete hlds;

	return buffer;
}

void Redirect::ChangeQueryPacket(char* packet, size_t& packet_size, uint16_t port)
{
	int iFoundedByte = HOST_NAME;
	size_t iCurrentSize = 6;


	char buffer[MAX_BUFFER_LENGTH] = "\xff\xff\xff\xff\x49\x30";

	for (int i = 6; i <= packet_size; i++)
	{
		if (packet[i] == 0x00)
		{		
			switch (iFoundedByte)
			{
			case HOST_NAME:
			{
				//size_t randomName = (size_t) GenerateRandomNumber(0, m_ServerNames.size() - 1);
				//std::string* hostName = &m_ServerNames.at(randomName);
				//std::memcpy(buffer + iCurrentSize, hostName->c_str(), hostName->size());
				//iCurrentSize += hostName->size();

				std::memcpy(buffer + iCurrentSize, "CS2.SHAINY.RO", 13);
				iCurrentSize += 13;

				buffer[++iCurrentSize] = 0x00;

				iFoundedByte = MAP;
				break;
			}
			
			case MAP:
			{
				std::memcpy(buffer + iCurrentSize, "de_dust2", 8);
				iCurrentSize += 8;
				buffer[++iCurrentSize] = 0x00;

				iFoundedByte = FOLDER;
				break;
			}

			case FOLDER:
			{
				std::memcpy(buffer + iCurrentSize, "cstrike", 7);
				iCurrentSize += 7;
				buffer[++iCurrentSize] = 0x00;

				iFoundedByte = GAME;
				break;
			}

			case GAME:
			{
				std::memcpy(buffer + iCurrentSize, "RomaniaCS16", 11);
				iCurrentSize += 11;
				iFoundedByte = APPID;
				break;
			}
			}
		}

		switch (iFoundedByte)
		{
		case APPID:
		{
			// appid is short = 2 bytes
			buffer[++iCurrentSize] = 0x0A;
			buffer[++iCurrentSize] = 0x00;
			//i += 1;
			iFoundedByte = PLAYERS;
			break;
		}

		case PLAYERS:
		{
			// online players, max players and bots (all 1 byte)
			buffer[++iCurrentSize] = IntToByte(GenerateRandomNumber(28, 31)); // online players
			//i += 1;
			buffer[++iCurrentSize] = 0x20; // max players
			buffer[++iCurrentSize] = 0x00; // bots
			buffer[++iCurrentSize] = 0x64; // server type (dedicated)
			buffer[++iCurrentSize] = 0x6c; // enviroment (linux)
			buffer[++iCurrentSize] = 0x00; // visibility ( 0 public)
			buffer[++iCurrentSize] = 0x01; // VAC Secured ( 1 true)
			buffer[++iCurrentSize] = 0x31; // version start
			buffer[++iCurrentSize] = 0x2e;
			buffer[++iCurrentSize] = 0x31;
			buffer[++iCurrentSize] = 0x2e;
			buffer[++iCurrentSize] = 0x32;
			buffer[++iCurrentSize] = 0x2e;
			buffer[++iCurrentSize] = 0x37;
			buffer[++iCurrentSize] = 0x2f;
			buffer[++iCurrentSize] = 0x53;
			buffer[++iCurrentSize] = 0x74;
			buffer[++iCurrentSize] = 0x64;
			buffer[++iCurrentSize] = 0x69;
			buffer[++iCurrentSize] = 0x6f;
			buffer[++iCurrentSize] = 0x00; // version end
			buffer[++iCurrentSize] = 0x80; // Extra data flag -> 0x80 -> next 2 bytes is port (short)
			buffer[++iCurrentSize] = static_cast<uint8_t>(port & 0xFF); // port
			buffer[++iCurrentSize] = static_cast<uint8_t>((port >> 8) & 0xFF); // port

			//iFoundedByte = FOOTER;
			iFoundedByte = BREAK;
			break;
		}

		case FOOTER:
		{
			buffer[++iCurrentSize] = packet[i];
			break;
		}
		}
	}

	std::memset(packet, 0, sizeof(packet));
	std::memcpy(packet, buffer, iCurrentSize);

	packet_size = iCurrentSize;
}

int Redirect::GenerateRandomNumber(size_t min_value, size_t max_value) const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min_value, max_value);

	return dis(gen);
}

inline char Redirect::IntToByte(int value) const
{
	return static_cast<char>(value);
}