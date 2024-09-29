#ifndef _CONSOLE
#define _CONSOLE
#pragma once

/*
	!FIXME!
		- Sometimes, when pushing a message to the queue before using exit function, the message it's not printed:
			* Causes: Console thread is destroyed before printing the message.
			* Solution: Create a new ErrLog function.

	TODO:
		- Create special log files (stdout.log stderr.log)
*/

#include <iostream>
#include <string.h>
#include <cstdarg>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <iomanip>
#include <sstream>

class Console
{
public:
	Console();
	Console(const Console&) = delete;
	Console(Console&&) = delete;
	~Console();

	static Console* get();
	void Printf(const char* fmt, ...);

private:
	static Console* m_Console;
	void Thread();

	std::queue<std::string> m_MessagesQueue;
	std::mutex m_Mutex;
	std::thread m_Thread;
	std::condition_variable m_ConditionVariable;
	bool m_TimePrefix;
};
#endif