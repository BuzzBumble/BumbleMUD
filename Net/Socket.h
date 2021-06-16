#pragma once

#include "net_common.h"

namespace net {
	class Address;
	class Socket {
	public:

		static constexpr int MAX_PACKET_SIZE = 256;

		virtual bool Open() = 0;

		virtual bool Bind(unsigned short port) = 0;

		virtual void Close() = 0;

		virtual bool IsOpen() const = 0;

	private:
		int handle = -1;
	};
}
