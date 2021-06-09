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
#define _WIN32_WINNT 0x0A00
#endif

class Address;

class Socket {
public:
	Socket() = default;

	~Socket();

	bool Open(unsigned short port);

	void Close();

	bool IsOpen() const;

	bool Send(const Address& dest, const void* data, int size);

	int Receive(Address& sender, void* data, int size);

private:
	int handle = -1;
};
