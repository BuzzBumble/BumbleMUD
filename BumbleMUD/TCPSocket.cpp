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

	bool TCPSocket::Send(const void* data, int size) {
		int sent_bytes = send(handle,
			static_cast<const char*>(data),
			size,
			0);

		if (sent_bytes != size) {
			return false;
		}

		return true;
	}

	bool TCPSocket::Listen(const int& maxConn) {
		if (listen(handle, maxConn) < 0) {
			// Error occurred
			return false;
		}
		return true;
	}

	int TCPSocket::Accept(Address& peerAddr) {
		sockaddr_in addr;
		int addr_size = sizeof(sockaddr_in);

		int newfd = accept(handle, (sockaddr*)&addr, &addr_size);

		peerAddr = Address(ntohl(addr.sin_addr.s_addr), ntohs(addr.sin_port));

		return newfd;
	}

	int TCPSocket::Receive(int sockfd, void* data, int size) {
		unsigned int max_packet_size = MAX_PACKET_SIZE;

		int read_bytes = recv(sockfd,
			static_cast<char*>(data),
			max_packet_size,
			0);

		return read_bytes;
	}

	int TCPSocket::Receive(void* data, int size) {
		unsigned int max_packet_size = MAX_PACKET_SIZE;

		int read_bytes = recv(handle,
			static_cast<char*>(data),
			max_packet_size,
			0);

		return read_bytes;
	}

	bool TCPSocket::Connect(const Address& servAddr) {
		int addr_size = sizeof(sockaddr_in);
		if (connect(handle, (sockaddr*)&servAddr.GetSockAddr(), addr_size) < 0) {
			return false;
		}
		return true;
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
