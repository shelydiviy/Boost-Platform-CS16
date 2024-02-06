#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <cerrno>

constexpr int MAX_PACKET_LENGTH = 1420;

typedef enum
{
    SEND_CHALLANGE,
    WAIT_CHALLANGE_ID,
    SEND_INFO,
    VALIDATE_INFO,
    IDLE
} CLIENT_STATE;

int g_iSocketHandler;
CLIENT_STATE g_csClientState = SEND_CHALLANGE;

sockaddr_in g_TargetStruct;

int CreateSocket();
void HandleClientState();
void SendPacket(const char* buffer, size_t buffer_size);
char* ExtractChallengeNumber(const char* buffer, char* extracted_content, size_t max_length);
void HandleServerMessage(char* buffer, size_t buffer_size);

char CLIENT_INFO_PACKET[] = {
'\x22', '\x5c', '\x70', '\x72', '\x6f', '\x74', '\x5c', '\x33', '\x5c', '\x75', '\x6e', '\x69',
'\x71', '\x75', '\x65', '\x5c', '\x2d', '\x31', '\x5c', '\x72', '\x61', '\x77', '\x5c', '\x73', '\x74', '\x65', '\x61', '\x6d',
'\x5c', '\x63', '\x64', '\x6b', '\x65', '\x79', '\x5c', '\x62', '\x66', '\x39', '\x31', '\x35', '\x33', '\x65', '\x30', '\x35',
'\x65', '\x64', '\x35', '\x66', '\x32', '\x33', '\x34', '\x36', '\x66', '\x33', '\x66', '\x36', '\x32', '\x36', '\x39', '\x66',
'\x62', '\x65', '\x36', '\x62', '\x32', '\x66', '\x63', '\x22', '\x20', '\x22', '\x5c', '\x5f', '\x63', '\x6c', '\x5f', '\x61',
'\x75', '\x74', '\x6f', '\x77', '\x65', '\x70', '\x73', '\x77', '\x69', '\x74', '\x63', '\x68', '\x5c', '\x31', '\x5c', '\x62',
'\x6f', '\x74', '\x74', '\x6f', '\x6d', '\x63', '\x6f', '\x6c', '\x6f', '\x72', '\x5c', '\x36', '\x5c', '\x63', '\x6c', '\x5f',
'\x64', '\x6c', '\x6d', '\x61', '\x78', '\x5c', '\x35', '\x31', '\x32', '\x5c', '\x63', '\x6c', '\x5f', '\x6c', '\x63', '\x5c',
'\x31', '\x5c', '\x63', '\x6c', '\x5f', '\x6c', '\x77', '\x5c', '\x31', '\x5c', '\x63', '\x6c', '\x5f', '\x75', '\x70', '\x64',
'\x61', '\x74', '\x65', '\x72', '\x61', '\x74', '\x65', '\x5c', '\x31', '\x30', '\x32', '\x5c', '\x6d', '\x6f', '\x64', '\x65',
'\x6c', '\x5c', '\x67', '\x6f', '\x72', '\x64', '\x6f', '\x6e', '\x5c', '\x6e', '\x61', '\x6d', '\x65', '\x5c', '\x6c', '\x65',
'\x78', '\x7a', '\x6f', '\x72', '\x5c', '\x74', '\x6f', '\x70', '\x63', '\x6f', '\x6c', '\x6f', '\x72', '\x5c', '\x33', '\x30',
'\x5c', '\x5f', '\x76', '\x67', '\x75', '\x69', '\x5f', '\x6d', '\x65', '\x6e', '\x75', '\x73', '\x5c', '\x31', '\x5c', '\x5f',
'\x61', '\x68', '\x5c', '\x31', '\x5c', '\x5f', '\x43', '\x53', '\x5c', '\x6c', '\x65', '\x78', '\x7a', '\x6f', '\x72', '\x5c',
'\x5f', '\x63', '\x6c', '\x61', '\x73', '\x73', '\x79', '\x5c', '\x67', '\x69', '\x67', '\x69', '\x62', '\x65', '\x63', '\x61',
'\x6c', '\x69', '\x5c', '\x5f', '\x70', '\x77', '\x5c', '\x70', '\x61', '\x72', '\x6f', '\x6c', '\x61', '\x5c', '\x62', '\x6f',
'\x6f', '\x73', '\x74', '\x5c', '\x31', '\x5c', '\x25', '\x73', '\x5c', '\x31', '\x5c', '\x6c', '\x61', '\x6e', '\x67', '\x5c',
'\x65', '\x6e', '\x5c', '\x72', '\x61', '\x74', '\x65', '\x5c', '\x31', '\x30', '\x30', '\x30', '\x30', '\x30', '\x22', '\x0a',
'\x14', '\x00', '\x00', '\x00', '\x71', '\x14', '\xcd', '\x0b', '\x57', '\x8f', '\xb6', '\xfa', '\x55', '\xa8', '\x92', '\x06',
'\x01', '\x00', '\x10', '\x01', '\x81', '\xff', '\xa4', '\x65', '\xb2', '\x00', '\x00', '\x00', '\x32', '\x00', '\x00', '\x00',
'\x04', '\x00', '\x00', '\x00', '\x55', '\xa8', '\x92', '\x06', '\x01', '\x00', '\x10', '\x01', '\x0a', '\x00', '\x00', '\x00',
'\x88', '\xa7', '\x4e', '\x52', '\x85', '\x01', '\xa8', '\xc0', '\x00', '\x00', '\x00', '\x00', '\x4d', '\x51', '\xa4', '\x65',
'\xcd', '\x00', '\xc0', '\x65', '\x01', '\x00', '\x07', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x98', '\x53',
'\xaf', '\x8d', '\xa7', '\x37', '\xee', '\x05', '\x20', '\xcd', '\x04', '\x51', '\x0f', '\xba', '\x9c', '\xda', '\x07', '\xb4',
'\xfe', '\xcb', '\x77', '\x4a', '\x34', '\xd6', '\x4c', '\x1a', '\xe5', '\x8e', '\xa2', '\x0b', '\x85', '\x4b', '\xdf', '\x30',
'\xf2', '\x6f', '\x4e', '\x23', '\x6f', '\x28', '\xbb', '\xd5', '\x6f', '\x47', '\x8e', '\x4d', '\xe5', '\x3e', '\x62', '\xfa',
'\x02', '\xf8', '\xa1', '\xbd', '\xdc', '\x33', '\x06', '\x5e', '\xe8', '\xb6', '\x23', '\x3c', '\x94', '\x23', '\xa8', '\x80',
'\x56', '\x7d', '\xde', '\x41', '\xfb', '\x8d', '\xcb', '\x42', '\x78', '\x8a', '\xc9', '\x8f', '\x25', '\x98', '\xb3', '\xe5',
'\xd1', '\x69', '\xb3', '\xe9', '\x1f', '\x0b', '\xec', '\xec', '\xb5', '\x19', '\xec', '\x27', '\x4e', '\x57', '\x07', '\x99',
'\x88', '\x34', '\xf9', '\xd0', '\x28', '\x9a', '\x71', '\x57', '\x59', '\x09', '\xba', '\x64', '\x22', '\x8d', '\xbb', '\xcd',
'\x32', '\x0c', '\x54', '\xe1', '\x08', '\xa8', '\x27', '\xc6', '\x33', '\x02', '\x5e', '\xc9', '\xd0', '\xd5',
};
char VALIDATE_INFO_PACKET[] = { '\x04', '\x00', '\x00', '\x00', '\x02', '\x00', '\x00', '\x80', '\x5f', '\x19', '\x01', '\x05', '\x1f', '\x01', '\x11', '\x45'};

//char CLIENT_INFO_PACKET[] = { "\x22\\prot\\3\\unique\\ - 1\\raw\\steam\\cdkey\\bf9153e05ed5f2346f3f6269fbe6b2fc\\x22\\x20\\x22\\_cl_autowepswitch\\1\\bottomcolor\\6\cl_dlmax\\512\cl_lc\\1\cl_lw\1\cl_updaterate\\102\\model\\gordon\\name\\lexzor\\topcolor\\30\\_vgui_menus\\1\\_ah\\1\\_CS\\lexzor\\_classy\\gigibecali\\_pw\\parola\\boost\\1\\%s\\1\\lang\\en\\rate\\100000" };

int main()
{
    std::cout << "Starting client" << std::endl;
	g_iSocketHandler = CreateSocket();

    char buffer[MAX_PACKET_LENGTH];
    ssize_t bytes;

    while (true)
    {
        HandleClientState();

        bytes = recv(g_iSocketHandler, buffer, sizeof(buffer), 0);

        if (bytes == -1)
        {
            perror("Error occure while trying to read from socket");
            exit(EXIT_FAILURE);
        }

        HandleServerMessage(buffer, (size_t) bytes);

        std::cout << "Received " << buffer << std::endl;
    }

    return 1;
}

void HandleClientState()
{
    switch (g_csClientState)
    {
    case SEND_CHALLANGE:
        SendPacket("\xff\xff\xff\xffgetchallenge steam\x0a", 23);
        
        g_csClientState = WAIT_CHALLANGE_ID;
        break;

    case SEND_INFO:
        SendPacket(CLIENT_INFO_PACKET, sizeof(CLIENT_INFO_PACKET));

        g_csClientState = IDLE;
        break;
    case IDLE:
        break;
    }
}

void SendPacket(const char* buffer, size_t buffer_size)
{
    if (sendto(g_iSocketHandler, buffer, buffer_size, 0, (sockaddr*)&g_TargetStruct, sizeof(g_TargetStruct)) == -1)
    {
        perror("Error occured while trying to send packet to target server");
        exit(EXIT_FAILURE);
    }

    std::cout << "Sent " << buffer << std::endl;
}

int CreateSocket()
{
	int socket_handler = socket(AF_INET, SOCK_DGRAM, 0);

	if (socket_handler == 0)
	{
		perror("Error occured while opening socket");
        exit(EXIT_FAILURE);
    }

    const int opt = 1;

    if (setsockopt(socket_handler, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Failed to attach socket.\n");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(27005);
    inet_pton(AF_INET, "51.89.8.25", &(serv_addr.sin_addr));

    if (bind(socket_handler, (sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
    {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    g_TargetStruct.sin_family = AF_INET;
    g_TargetStruct.sin_port = htons(27015);
    inet_pton(AF_INET, "188.212.101.238", &(g_TargetStruct.sin_addr));

    std::cout << "Ready to receive and send packets" << std::endl;

    return socket_handler;
}

char* ExtractChallengeNumber(const char* buffer, char* extracted_content, size_t max_length)
{
    const char* keyword_start = "A00000000";
    const char* start_position = strstr(buffer, keyword_start);

    if (start_position != nullptr)
    {
        start_position += strlen(keyword_start);

        while (*start_position && *start_position == ' ')
        {
            ++start_position;
        }

        size_t length = 0;
        while (*start_position && (isdigit(*start_position)) && length < max_length - 1)
        {
            extracted_content[length++] = *start_position;
            ++start_position;
        }

        extracted_content[length] = '\x20';
        extracted_content[length + 1] = '\x00';

        return extracted_content;
    }
    else
    {
        std::cout << "Start keyword not found in the buffer." << std::endl;
        exit(EXIT_FAILURE);
    }

    return nullptr;
}

void HandleServerMessage(char* buffer, size_t buffer_size)
{
    switch (g_csClientState)
    {
    case VALIDATE_INFO:
        SendPacket(VALIDATE_INFO_PACKET, sizeof(VALIDATE_INFO_PACKET));
        break;

    case WAIT_CHALLANGE_ID:
        char challengeNumber[MAX_PACKET_LENGTH];
        char* extractedChallenge = ExtractChallengeNumber(buffer, challengeNumber, sizeof(challengeNumber));

        if (extractedChallenge != nullptr)
        {
            // Get the length of the challenge number
            size_t challengeLength = strlen(extractedChallenge);

            const char* fixedPart = "\xff\xff\xff\xff\x63\x6f\x6e\x6e\x65\x63\x74\x20\x34\x38\x20";
            size_t clientInfoLength = strlen(fixedPart);

            char modifiedClientInfo[MAX_PACKET_LENGTH];
            memcpy(modifiedClientInfo, fixedPart, clientInfoLength);

            // Make sure to not exceed the buffer size
            if ((clientInfoLength + challengeLength + sizeof(CLIENT_INFO_PACKET)) < MAX_PACKET_LENGTH)
            {
                memcpy(modifiedClientInfo + clientInfoLength, extractedChallenge, challengeLength);
                memcpy(modifiedClientInfo + clientInfoLength + challengeLength, CLIENT_INFO_PACKET, sizeof(CLIENT_INFO_PACKET));

                // Use modifiedClientInfoLength instead of sizeof(modifiedClientInfo)
                SendPacket(modifiedClientInfo, clientInfoLength + challengeLength + sizeof(CLIENT_INFO_PACKET));
            }
            else
            {
                std::cerr << "Modified client info exceeds the buffer size." << std::endl;
            }

            g_csClientState = IDLE;
        }
        else
        {
            std::cerr << "Failed to extract challenge number." << std::endl;
        }

        g_csClientState = VALIDATE_INFO;

        break;
    }
}