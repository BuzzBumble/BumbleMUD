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

		const char reuse = 1;
		setsockopt(handle, SOL_SOCKET, SO_REUSEADDR | SO_BROADCAST, &reuse, sizeof(reuse));

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

	int TCPSocket::Send(const void* data, int size) {
		return send(handle,
			static_cast<const char*>(data),
			size,
			0);
	}

	int TCPSocket::Receive(char* buf, int size) {
		int bytes = recv(handle, buf, size, 0);
		return bytes;
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

	bool TCPSocket::Connect(const Address& servAddr) {
		int addr_size = sizeof(sockaddr_in);
		int xsize = sizeof(servAddr.GetSockAddr());
		if (connect(handle, (sockaddr*)&servAddr.GetSockAddr(), addr_size) < 0) {
			return false;
		}

		return true;
	}

}
