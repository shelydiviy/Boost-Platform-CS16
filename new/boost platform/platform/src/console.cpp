#include "console.hpp"

constexpr size_t MAX_BUFFER_LENGTH = 512;
Console* Console::m_Console = nullptr;

Console::Console()
{
    m_Thread = std::thread(&Console::Thread, this);
    m_Thread.detach();
}

Console::~Console() {}

Console* Console::get()
{
    if (m_Console == nullptr)
    {
        m_Console = new Console();
    }

    return m_Console;
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
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()) % 1000;

    std::tm localTime = *std::localtime(&timeT);
    char timeBuffer[24];
    strftime(timeBuffer, sizeof(timeBuffer), "%Y/%m/%d %H:%M:%S.", &localTime);

    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << milliseconds.count();
    strcat(timeBuffer, ss.str().c_str());

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