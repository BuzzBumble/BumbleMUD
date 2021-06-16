#pragma once

#define PLATFORM_WIN 1
#define PLATFORM_MAC 2
#define PLATFORM_UNX 3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WIN
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNX
#endif

#if PLATFORM == PLATFORM_WIN
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

#if PLATFORM == PLATFORM_WIN
#define _WIN32_WINNT 0x0A00
#endif
