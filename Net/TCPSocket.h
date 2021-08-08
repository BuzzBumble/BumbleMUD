#pragma once

#include "Socket.h"

namespace net {
	class Address;
	class TCPSocket : public Socket {
	public:
		TCPSocket() = default;

		~TCPSocket();

		bool Open();

		bool Bind(unsigned short port);

		void Close();

		bool IsOpen() const;

		int Send(const void* data, int size);

		int Receive(char* buf, int size);

		bool Listen(const int& maxConn);

		int Accept(Address& peerAddr);

		bool Connect(const Address& servAddr);
	};
}
