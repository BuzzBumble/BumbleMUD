#include <iostream>

#include "TCPSocket.h"
#include "Address.h"

namespace net {
	TCPSocket::~TCPSocket() {
		Close();
	}

	bool TCPSocket::Open() {
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (handle <= 0) {
			std::cerr << "Failed to create socket" << std::endl;
			return false;
		}

		return handle > 0;
	}

	bool TCPSocket::Bind(unsigned short port) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(port);

		if (bind(handle, (const sockaddr*)&addr, sizeof(sockaddr_in)) < 0) {
			std::cerr << "Failed to bind socket" << std::endl;
			return false;
		}

		return true;
	}

	void TCPSocket::Close() {
		#if (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX)
			close(handle);
		#elif PLATFORM == PLATFORM_WINDOWS
			closesocket(handle);
		#endif
		handle = -1;
	}

	bool TCPSocket::IsOpen() const {
		return handle != -1;
	}

	bool TCPSocket::Send(const Address& dest, const void* data, int size) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(dest.GetAddress());
		addr.sin_port = htons(dest.GetPort());
		int sent_bytes = send(handle,
			static_cast<const char*>(data),
			size,
			0);

		if (sent_bytes != size) {
			std::cerr << "Failed to send packet" << std::endl;
			return false;
		}

		return true;
	}

	int TCPSocket::Receive(Address& sender, void* data, int size) {
		unsigned int max_packet_size = MAX_PACKET_SIZE;

		sockaddr_in addr;
		int addr_size = sizeof(sockaddr_in);

		int read_bytes = recvfrom(handle,
			static_cast<char*>(data),
			max_packet_size,
			0,
			(sockaddr*)&addr,
			&addr_size);

		sender = Address(ntohl(addr.sin_addr.s_addr), ntohs(addr.sin_port));

		if (read_bytes <= 0) {
			// If 0, connection was closed
			// If -1, error occurred
		}

		return read_bytes;
	}

	void TCPSocket::SetNonblock(const bool value) {
		#if PLATFORM == PLATFORM_WIN
			DWORD nonblock = value;
			if (ioctlsocket(handle, FIONBIO, &nonblock) != 0) {
				std::cerr << "Failed to set socket to non-blocking" << std::endl;
			}
		#elif (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNX)
			int nonBlock = _BMUD_NONBLOCK;
			if (fcntl(handle, F_SETFL, O_NONBLOCK, nonblock) == -1) {
				std::cerr << "Failed to set socket to non-blocking" << std::endl;
			}
		#endif
	}

}
