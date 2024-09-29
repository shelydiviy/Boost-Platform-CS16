#include "fake_server.hpp"
#include "globals.hpp"
#include "network.hpp"

FakeServer::FakeServer(uint16 port, uint16 masterserver_port) :
	m_Socket(new Socket()),
	m_MasterServer(new MasterServer()),
	m_QueryPacket(new CDataParser(MAX_SOCKET_BUFFER_LENGTH)),
	m_SecondQueryPacket(new CDataParser(MAX_SOCKET_BUFFER_LENGTH)),
	m_GamePort(port),
	m_MasterServerPort(masterserver_port),
	m_AccountsPool(new SteamAccountPool()),
	m_Packets(false)
{
	BuildPackets();

	if (!m_MasterServer->Init(m_MasterServerPort, m_GamePort))
	{
		Console::get()->Printf("[CRITICAL] [FakeServer] Failed to initialize MasterServer for %s:%i", IPV4_ADDRESS, m_GamePort);
		exit(EXIT_FAILURE);
		return;
	}
}

FakeServer::~FakeServer() {}

void FakeServer::ListenSocket()
{
	CDataParser* data = new CDataParser(MAX_SOCKET_BUFFER_LENGTH);
	ssize_t bytes;


	while (true)
	{
		data->ClearAllBuf();
		data->SetOffset(0);

		bytes = m_Socket->Recv(data->GetFullData(), data->GetFullSize());

		if (data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF)
		{

			ManageSteamFakerPacket(data);
			continue;
		}

		data->SetOffset(0);

		if (data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF &&
			data->GetByte() == 0xFF)
		{
			ManagePlayerPacket(data, bytes);
			continue;
		}

		ManagePlayerPacket(data, bytes);
	}

	delete data;
}

void FakeServer::StartListening()
{
	m_Socket->CreateSocket(m_GamePort);
	std::thread(&FakeServer::ListenSocket, this).detach();
	Console::get()->Printf("[FakeServer] Listening to %s:%i\n", IPV4_ADDRESS, m_GamePort);
}

uint16* FakeServer::GetPort()
{
	return &m_GamePort;
}

void FakeServer::BuildPackets()
{

	m_QueryPacket->ClearAllBuf();
	m_QueryPacket->SetOffset(0);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0xFF);
	m_QueryPacket->SetByte(0x49); // header
	m_QueryPacket->SetByte(0x30); // protocol
	m_QueryPacket->SetString("CS.MUIE.RO"); // host name
	m_QueryPacket->SetString("_aa"); // map
	m_QueryPacket->SetString("cstrike"); // folder
	m_QueryPacket->SetString("Counter-Strike"); // full name of the game name
	m_QueryPacket->SetShort(10); // appid
	m_QueryPacket->SetByte(0x20); // players
	m_QueryPacket->SetByte(0x20); // max players
	m_QueryPacket->SetByte(0x01); // bots
	m_QueryPacket->SetByte(0x64); // server type [0x64 = d (dedicated)]
	m_QueryPacket->SetByte(0x6C); // enviroment [0x6c = l (linux)]
	m_QueryPacket->SetByte(0x00); // visibility [private]
	m_QueryPacket->SetByte(0x01); // VAC [secured]
	m_QueryPacket->SetString("1.1.2.7/Stdio"); // version of the game installed on server
	m_QueryPacket->SetByte(0x80); // EDF - Extra Data Flag [0x80 = game port in short]
	m_QueryPacket->SetShort(m_GamePort); // Game port
}

void FakeServer::ManagePlayerPacket(CDataParser* data, int datalen)
{
	byte opcode = data->GetByte();

	switch (opcode)
	{
	case A2S_INFO:
	{
		BuildPackets();
		m_Socket->Send(m_QueryPacket->GetFullData(), m_QueryPacket->GetOffset());
		Console::get()->Printf("Received A2S_INFO from %s:%i\n", m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
		break;
	}

	case A2S_CHALLANGE:
	{
		m_Socket->Send(m_SecondQueryPacket->GetFullData(), m_SecondQueryPacket->GetOffset());
		Client* client = new Client(m_Socket, m_Socket->GetSenderAddrStruct(), m_Socket->GetSenderAddrStructSize());

		std::unique_lock<std::mutex>lock(m_ClientVMutex);
		m_Clients.push_back(client);

		client->SendPacket(data->GetFullData(), datalen);

		Console::get()->Printf("Received A2S_CHALLANGE from %s:%i\n", m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
	}

	default: 
	{
		data->SetOffset(0);

		std::vector<Client*> TempVector;
		
		{
			std::unique_lock<std::mutex>lock(m_ClientVMutex);
			TempVector = m_Clients;
		}

		for (Client* client : TempVector)
		{
			if (
				client->GetClientAddr()->sin_addr.s_addr == m_Socket->GetSenderAddrStruct()->sin_addr.s_addr &&
				client->GetClientPort() == m_Socket->GetSenderPort()
				)
			{
				client->SendPacket(data->GetFullData(), datalen);

				break;
			}
		}
	}
	}
}

void FakeServer::ManageSteamFakerPacket(CDataParser* data)
{
	byte opcode = data->GetByte();
	uint64 SteamID = data->GetUInt64();

	SteamAccount* account = m_AccountsPool->GetAccount(SteamID);

	switch (opcode)
	{
	case PLATFORM_S2A_INFO:
	{
		data->ClearAllBuf();
		data->SetOffset(0);
		
		if (account != nullptr)
		{
			Console::get()->Printf("[FakeServer] [WARNING] SteamFaker %s:%i tried to register an existent Steam account\n", m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			Console::get()->Printf("[FakeServer] [WARNING] Steam account registered on %s:%i. Request to register on %s:%i\n", IPV4_ADDRESS, *GetPort(), IPV4_ADDRESS, m_GamePort);

			data->SetByte(PLATFORM_A2S_ACCOUNT_EXISTS);
			data->SetShort(*GetPort());

#ifdef PLATFORM_DEBUG
			if (m_Socket->Send(data->GetFullData(), data->GetOffset()) == SOCKET_ERROR_CODE)
				Console::get()->Printf("[FakeServer] [WARNING] [Port %i] Failed to send PLATFORM_A2S_ACCOUNT_EXISTS to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			else
				Console::get()->Printf("[FakeServer] [Port %i] Succesfully sent PLATFORM_A2S_ACCOUNT_EXISTS to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
#else
			m_Socket->Send(data->GetFullData(), data->GetOffset());
#endif
			// TODO: Trying to disconnect user to retry login..

			return;
		}

		data->SetByte(PLATFORM_A2S_INFO);
		data->SetUInt64(m_MasterServer->GetSteamID());


#ifdef PLATFORM_DEBUG
		if (m_Socket->Send(data->GetFullData(), data->GetOffset()) == SOCKET_ERROR_CODE)
			Console::get()->Printf("[FakeServer] [WARNING] [Port %i] Failed to send PLATFORM_A2S_INFO to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
		else
			Console::get()->Printf("[FakeServer] [Port %i] Succesfully sent PLATFORM_A2S_INFO to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
#else
		m_Socket->Send(data->GetFullData(), data->GetOffset());
#endif

		m_AccountsPool->AddAccount(SteamID, *m_Socket->GetSenderAddrStruct(), *m_Socket->GetSenderAddrStructSize());

		break;
	}
	
	case PLATFORM_S2A_TICKET:
	{
		CSteamID ReturnedSteamID;

		if (!m_MasterServer->LoginUser(m_Socket->GetSenderAddressInt(), data->GetFullData() + data->GetOffset(), data->GetFullSize() - data->GetOffset(), &ReturnedSteamID))
		{
			account->m_Tries++;

			data->ClearAllBuf();
			data->SetOffset(0);

			if (account->m_Tries == 10)
			{
				data->SetByte(PLATFORM_A2S_ACCOUNT_EXISTS);
				
				Console::get()->Printf("[FakeServer] [Port %i] Failed to send ticket. Removing account\n", m_GamePort);

#ifdef PLATFORM_DEBUG
				if (m_Socket->Send(data->GetFullData(), data->GetOffset()) == SOCKET_ERROR_CODE)
					Console::get()->Printf("[FakeServer] [WARNING] [Port %i] Failed to send PLATFORM_A2S_MESSAGE to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
				else
					Console::get()->Printf("[FakeServer] [Port %i] Succesfully sent PLATFORM_A2S_MESSAGE to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
#else
				m_Socket->Send(data->GetFullData(), data->GetOffset());
#endif
				return;
			}


			Console::get()->Printf("[FakeServer] [Port %i] Failed to register SteamFaker client %s:%i.\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			Console::get()->Printf("[FakeServer] [Port %i] Waiting for Steam servers response..\n", m_GamePort);

			data->SetByte(PLATFORM_A2S_MESSAGE);
			data->SetString("It seems the SteamAPI refused the registration ticket, but we will wait a conclundent response\n");
		
#ifdef PLATFORM_DEBUG
			if (m_Socket->Send(data->GetFullData(), data->GetOffset()) == SOCKET_ERROR_CODE)
				Console::get()->Printf("[FakeServer] [WARNING] [Port %i] Failed to send PLATFORM_A2S_MESSAGE to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
			else
				Console::get()->Printf("[FakeServer] [Port %i] Succesfully sent PLATFORM_A2S_MESSAGE to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
#else
			m_Socket->Send(data->GetFullData(), data->GetOffset());
#endif
			NotifySteamFakerClientDisconnect(SteamID, k_EDenyInvalid, "invalid_ticket");

			return;
		}

		Console::get()->Printf("[FakeServer] [Port %i] SteamFaker account registered via SteamAPI. Waiting a concludent response from Steam servers.\n", m_GamePort);

		data->ClearAllBuf();
		data->SetOffset(0);

		data->SetByte(PLATFORM_A2S_MESSAGE);
		data->SetString("Registered via SteamGameServerAPI, but we are waiting a conclundent response from Steam servers.");

#ifdef PLATFORM_DEBUG
		if (m_Socket->Send(data->GetFullData(), data->GetOffset()) == SOCKET_ERROR_CODE)
			Console::get()->Printf("[FakeServer] [WARNING] [Port %i] Failed to send PLATFORM_A2S_MESSAGE to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
		else
			Console::get()->Printf("[FakeServer] [Port %i] Succesfully sent PLATFORM_A2S_MESSAGE to %s:%i\n", m_GamePort, m_Socket->GetSenderAddressStr(), m_Socket->GetSenderPort());
#else
		m_Socket->Send(data->GetFullData(), data->GetOffset());
#endif

		m_AccountsPool->GetAccount(SteamID)->SetState(CONNECTED);

		data->ClearAllBuf();
		data->SetOffset(0);

		break;
	}
	}

	return;
}

void FakeServer::NotifySteamFakerClientDisconnect(uint64 steamid, EDenyReason deny_reason, char reason_text[128])
{
	Console::get()->Printf("[FakeServer] [WARNING] [Port %i] SteamFaker client has been disconnected from masterserver. Retrying reconnection.\n", m_GamePort);
	Console::get()->Printf("[FakeServer] [WARNING] [Port %i] DenyCode: %i. Reason: %s.\n", m_GamePort, deny_reason, reason_text);
	

	SteamAccount* account = m_AccountsPool->GetAccount(steamid);

	account->SetState(SHOULD_RECONNECT);
	m_MasterServer->DisconnectUser(account->GetSteamID());

	CDataParser* data = new CDataParser(129);

	data->SetByte(PLATFORM_A2S_NEED_RECONNECT);
	data->SetString(reason_text);

#ifdef PLATFORM_DEBUG
	if (m_Socket->SendTo(data->GetFullData(), data->GetOffset(), account->GetAddrStruct(), account->GetAddrSize()) == SOCKET_ERROR_CODE)
		Console::get()->Printf("[FakeServer] [CRITICAL] [Port %i] Failed to send PLATFORM_A2S_NEED_RECONNECT to SteamFaker client.\n", m_GamePort);
	else
		Console::get()->Printf("[FakeServer] [CRITICAL] [Port %i] Succesfully sent PLATFORM_A2S_NEED_RECONNECT to SteamFaker client.\n", m_GamePort);
#else
	m_Socket->SendTo(data->GetFullData(), data->GetOffset(), account->GetAddrStruct(), account->GetAddrSize());
#endif

	data->ClearAllBuf();
	data->SetOffset(0);

	data->SetByte(PLATFORM_A2S_INFO);
	data->SetUInt64(SteamGameServer()->GetSteamID().ConvertToUint64());

#ifdef PLATFORM_DEBUG
	if (m_Socket->SendTo(data->GetFullData(), data->GetOffset(), account->GetAddrStruct(), account->GetAddrSize()) == SOCKET_ERROR_CODE)
		Console::get()->Printf("[FakeServer] [CRITICAL] [Port %i] Failed to send PLATFORM_A2S_INFO to SteamFaker client. (NotifySteamFakerClientDisconnect)\n", m_GamePort);
	else
		Console::get()->Printf("[FakeServer] [CRITICAL] [Port %i] Succesfully sent PLATFORM_A2S_INFO to SteamFaker client. (NotifySteamFakerClientDisconnect)\n", m_GamePort);
#else
	m_Socket->SendTo(data->GetFullData(), data->GetOffset(), account->GetAddrStruct(), account->GetAddrSize());
#endif

	delete data;
}

void FakeServer::NotifySteamFakerClientConnect(uint64 steamid)
{
	Console::get()->Printf("[FakeServer] [Port %i] Steam account registered succesfully!\n", m_GamePort);

	SteamAccount* account = m_AccountsPool->GetAccount(steamid);

	account->SetState(CONNECTED);

	CDataParser* data = new CDataParser(9);
	data->SetByte(PLATFORM_A2S_TICKET);
	data->SetString("success");

#ifdef PLATFORM_DEBUG
	if (m_Socket->SendTo(data->GetFullData(), data->GetOffset(), account->GetAddrStruct(), account->GetAddrSize()) == SOCKET_ERROR_CODE)
		Console::get()->Printf("[FakeServer] [CRITICAL] [Port %i] Failed to send PLATFORM_A2S_TICKET to SteamFaker client. (NotifySteamFakerClientConnect)\n", m_GamePort);
	else
		Console::get()->Printf("[FakeServer] [CRITICAL] [Port %i] Succesfully sent PLATFORM_A2S_TICKET to SteamFaker client. (NotifySteamFakerClientConnect)\n", m_GamePort);
#else
	m_Socket->SendTo(data->GetFullData(), data->GetOffset(), account->GetAddrStruct(), account->GetAddrSize());
#endif
}

void FakeServer::SetSteamID(uint64 steamid)
{
	m_SteamID = steamid;
}
