#pragma once
#ifndef _GLOBALS
#define _GLOBALS

#include "console.hpp"
#include "steamtypes.h"

// Uncommenting this will disable platform logs
#define PLATFORM_DEBUG

extern const size_t MAX_SOCKET_BUFFER_LENGTH;
extern const char* IPV4_ADDRESS;
extern const int INIT_STEAM_SERVERS_SECONDS;
extern const int STEAM_CALLBACKS_MILLISECOONDS;
extern uint32 UINT32_IP;

void InitGlobals();

#endif