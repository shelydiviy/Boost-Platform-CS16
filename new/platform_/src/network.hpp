#ifndef _NETWORK
#define _NETWORK
/*
*	The SteamFaker and Platform application communicate between each other based on a request and response model.
* SteamFaker will always send a account steamid.
*
*	Legend:
*	A2S -> Application (Steam Faker) to server (Platform)
*	S2A -> Server to application
*
*/

#define S2A_TICKET_REGISTER_FAIL "fail"
#define S2A_TICKET_REGISTER_SUCCESS "success"

typedef enum {
	PLATFORM_S2A_INFO = 0x01,
	PLATFORM_A2S_INFO = 0x02,
	PLATFORM_S2A_TICKET = 0x03,
	PLATFORM_A2S_TICKET = 0x04,
	PLATFORM_A2S_ACCOUNT_EXISTS = 0x05,
	PLATFORM_A2S_NEED_RECONNECT = 0x06,
	PLATFORM_A2S_MESSAGE = 0x07
} SteamFakerPacketOpcode;

typedef enum {
	REQUEST_CONNECT,
	WAITING_STEAM_RESPONSE,
	CONNECTED,
	SHOULD_RECONNECT
} SteamAccountState;



/*
* Flow for the SteamFaker <-> Application communication:
*
*	PLATFORM_S2A_INFO:
*		The network packet sent by SteamFaker to announce his presence and to request the fake game server SteamID. This is the first network packet sent by
*	SteamFaker. It will also contain account SteamID which will be used for SteamGameServer Callbacks API.
*
*		Format:
*			- Opcode: Byte
*			- Account SteamID: uint64 (network byte order)
*
*
* ---------------------------------------------------------------------------------------------
*
*
*	PLATFORM_A2S_INFO:
*		This network packet is sent as a response for PLATFORM_S2A_INFO from SteamFaker. The SteamFaker it's requesting the fake game server SteamID returned by
*	Steam servers which will be used to request a game connection ticket from Steam servers.
*
*		Format:
*			- Opcode: Byte
*			- Server SteamID: uint64 (network byte order)
*
*
* ---------------------------------------------------------------------------------------------
*
*
*	PLATFORM_S2A_TICKET:
*		Network packet that will contain the registration ticket. The registration ticket will be send to MasterServer class for validating it.
*
*		Format:
*			- Opcode: Byte
*			- Account SteamID: uint64 (network byte order)
*			- Steam Registration Ticket: Format of a X number of bytes
*
*	NOTE:	 The Steamworks SDK documentation it's telling us the minimum size of the allocated memory where the ticket will be saved must be at least 2048, but
*		  the returned ticket it's always 206 bytes. When the ticket request fails, the returned number of bytes it's 28, so an approach for this situation
*		  would be to mark the 28 bytes game connection ticket as fail without verifying it on the application side.
*			 For "better be safe than sorry" reasons we will instantiate the both ticket holder variables with a memory size of 4096.
*
*
* ---------------------------------------------------------------------------------------------
*
*
*	PLATFORM_A2S_TICKET:
*		The network packet sent as a response of PLATFORM_S2A_TICKET. The application it's announcing the SteamFaker if the Steam game connection ticket it's valid.
*
*		Format:
*			- Opcode: Byte
*			- Ticket validation response: string ("success" or "fail")
*
*
* ---------------------------------------------------------------------------------------------
*
*
*	PLATFORM_A2S_ACCOUNT_EXISTS:
*		Sent after PLATFORM_S2A_INFO in case the account has been already registered in the platform.
*
*		Format:
*			- Opcode: Byte
*
*
* ---------------------------------------------------------------------------------------------
*
* 
* // TODO: Make SteamFaker to retry register without sending againt PLATFORM_A2S_INFO
* 
*	PLATFORM_A2S_NEED_RECONNECT:
*		MasterServer function returned false. Actually we don't know why the Steam servers refused the ticket. SteamAPI callbacks will tell us this.
*
*		Format:
*			- Opcode: Byte
*			- Reason: String
* 
* 
* * ---------------------------------------------------------------------------------------------
*
* 
*	PLATFORM_A2S_MESSAGE:
*		Sending a message to the SteamFaker client.
*
*		Format:
*			- Opcode: Byte
*			- Message: String
*
*/

#endif