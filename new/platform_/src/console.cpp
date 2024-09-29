#include "console.hpp"

#define MAX_BUFFER_LENGTH 256

Console::Console() {}

void Console::InitConsole(bool time_prefix)
{
	std::cout << "Initialize console...\n";

	m_Thread = std::thread(&Console::Thread, this);
	
	Printf("Console initialized!\n");
	m_Thread.detach();
}

void Console::Printf(const char* fmt, ...)
{
	char buffer[MAX_BUFFER_LENGTH];

	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	auto currentTime = std::chrono::system_clock::now();
	auto timeT = std::chrono::system_clock::to_time_t(currentTime);

	std::tm localTime = *std::localtime(&timeT);
	char timeBuffer[20];
	strftime(timeBuffer, sizeof(timeBuffer), "%Y/%m/%d %H:%M:%S", &localTime);

	std::string message = "\033[97m[" + std::string(timeBuffer) + "]\033[37m " + std::string(buffer);

	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_MessagesQueue.push(message);
	}

	m_ConditionVariable.notify_one();
}

void Console::Thread()
{

	while (true)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_ConditionVariable.wait(lock, [this] { return !m_MessagesQueue.empty(); });

		while (!m_MessagesQueue.empty())
		{
			std::cout << m_MessagesQueue.front();
			m_MessagesQueue.pop();
		}
	}
}
