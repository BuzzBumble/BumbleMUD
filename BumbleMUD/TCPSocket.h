#pragma once

#include "Socket.h"

namespace net {
	class Address;
	class TCPSocket : Socket {
	public:
		TCPSocket() = default;

		TCPSocket(int handle)
			: handle(handle) {}

		~TCPSocket();

		bool Open();

		bool Bind(unsigned short port);

		void Close();

		bool IsOpen() const;

		bool Send(const void* data, int size);

		bool Listen(const int& maxConn);

		int Accept(Address& peerAddr);

		int Receive(int sockfd, void* data, int size);
		int Receive(void* data, int size);

		bool Connect(const Address& servAddr);

		void SetNonblock(const bool value);

	private:
		int handle = -1;
	};
}
