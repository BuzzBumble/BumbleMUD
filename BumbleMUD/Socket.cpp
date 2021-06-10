#include "Socket.h"

#if PLATFORM == PLATFORM_WIN
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

#include <iostream>
#include "Address.h"

namespace net {
	Socket::~Socket() {
		Close();
	}

	bool Socket::Open(unsigned short port) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(port);
		handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (handle <= 0) {
			std::cerr << "Failed to create socket" << std::endl;
			return false;
		}

		if (bind(handle, (const sockaddr*)&addr, sizeof(sockaddr_in)) < 0) {
			std::cerr << "Failed to bind socket" << std::endl;
			return false;
		}

#if PLATFORM == PLATFORM_WIN
		DWORD nonBlock = 1;
		if (ioctlsocket(handle, FIONBIO, &nonBlock) != 0) {
			std::cerr << "Failed to set socket to non-blocking" << std::endl;
			return false;
		}
#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
		int nonBlock = 1;
		if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlock) == -1) {
			std::cerr << "Failed to set socket to non-blocking" << std::endl;
			return false;
		}
#endif

		return handle > 0;
		}

	void Socket::Close() {
#if (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX)
		close(handle);
#elif PLATFORM == PLATFORM_WINDOWS
		closesocket(handle);
#endif
		handle = -1;
	}

	bool Socket::IsOpen() const {
		return handle != -1;
	}

	bool Socket::Send(const Address& dest, const void* data, int size) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(dest.GetAddress());
		addr.sin_port = htons(dest.GetPort());
		int sent_bytes = sendto(handle,
			static_cast<const char*>(data),
			size,
			0,
			(sockaddr*)&addr,
			sizeof(sockaddr_in));

		if (sent_bytes != size) {
			std::cerr << "Failed to send packet" << std::endl;
			return false;
		}

		std::cout << "Successfully sent packet of size " << sent_bytes << std::endl;

		return true;
	}

	int Socket::Receive(Address& sender, void* data, int size) {
		unsigned int max_packet_size = MAX_PACKET_SIZE;

		sockaddr_in addr;
		int addr_size = sizeof(sockaddr_in);

		int read_bytes = recvfrom(handle,
			static_cast<char*>(data),
			max_packet_size,
			0,
			(sockaddr*)&addr,
			&addr_size);

		if (read_bytes <= 0) {
			//std::cerr << "NO BYTE" << std::endl;
		}

		return read_bytes;
	}
}
