#pragma once
#ifndef _GLOBALS
#define _GLOBALS

#include "console.hpp"

#define Printf PlatformConsole->Printf

extern size_t MAX_SOCKET_BUFFER_LENGTH;;
extern Console* PlatformConsole;
extern const char* IPV4_ADDRESS;

void InitGlobals();
void InitSteam();

#endif