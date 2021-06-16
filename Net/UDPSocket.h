#pragma once

#include "Socket.h"

namespace net {
	class Address;
	class UDPSocket : Socket {
	public:
		UDPSocket() = default;

		~UDPSocket();

		bool Open();

		bool Bind(unsigned short port);

		void Close();

		bool IsOpen() const;

		bool Send(const Address& dest, const void* data, int size);

		int Receive(Address& sender, void* data, int size);

		void SetNonblock(const bool value);

	private:
		int handle = -1;
	};
}
