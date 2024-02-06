#if !defined REDIRECT
#define REDIRECT

#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <vector>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <cstdint>
#include <map>
#include <random>
#include <thread>
#include <unistd.h>
#include <memory>
#include <functional>
#include <mutex>
#include <iomanip>

#include "Socket.h"
#include "FakeServer.h"

constexpr int SOCKET_ERROR = -1;
constexpr const char* EMPTY_CHAR = "";
constexpr int MAX_BUFFER_LENGTH = 2048;
constexpr const unsigned char NULL_BYTES[4] = { 0xff, 0xff, 0xff, 0xff };
constexpr const unsigned char QUERY_ENGINE_MSG_HEADER[2] = { 0x49, 0x30 }; //I0
constexpr const short CURRENT_SERVER_NAME = 0;

constexpr const char* QUERY_ENGINE_MESSAGE = "TSource Engine Query";
constexpr const char* GET_CHALLANGE_MESSAGE = "getchallenge steam";

constexpr const int DEFAULT_CLIENT_SOCKET_TIMEOUT = 15;
constexpr const int NO_TIMEOUT = 0;

enum
{
	HOST_NAME,
	MAP,
	FOLDER,
	GAME,
	APPID,
	PLAYERS,
	FOOTER,
	BREAK
};

class Redirect
{
public:
	Redirect(const char* ipv4_address,
		const uint16_t port,
		const char* target_ipv4_address,
		const uint16_t target_port,
		const uint16_t redirects_number,
		std::vector<std::string> server_names,
		std::vector<std::string> player_names);
	void StartRedirects();

private:
	std::vector<std::string> m_ServerNames;
	std::vector<std::string> m_PlayerNames;
	
	std::mutex m_ClientsThreadPollMutex;
	std::vector<std::shared_ptr<std::thread>> m_FakeServersThreadPoll;
	std::vector<std::shared_ptr<std::thread>> m_ClientsThreadPoll;
	
	Socket *m_TargetSocket;
	char* m_IPv4Address;
	char* m_TargetIPv4Address;
	uint16_t m_TargetPort;
	uint16_t m_Port;
	uint16_t m_CurrentPort;
	uint16_t m_iRedirectPort;

	bool m_ShouldRun;

	bool OpenSocket(Socket* sock, uint16_t* port, const int timeout_seconds) const;
	char* InterogateHLDSServer(FakeServer* fake_server, uint16_t hlds_port, size_t& packet_size) const;
	void ChangeQueryPacket(char* packet, size_t& packet_size, uint16_t port);

	void SendQueryEngineInfo(const FakeServer* fake_server, const Socket* client_socket) const;
	int GenerateRandomNumber(size_t min_value, size_t max_value) const;
	inline char IntToByte(int value) const;
	void RegisterUser(FakeServer* fake_server, const Socket client_socket, const char* get_challenge_packet);
	void StartListeningClientSocket(FakeServer* fake_server, std::shared_ptr<Socket> private_socket, const Socket client_socket, const std::thread::id thread_id);
	void StartListening(std::shared_ptr<FakeServer> fake_server);
};
#endif