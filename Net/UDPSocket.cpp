#include <iostream>

#include "UDPSocket.h"
#include "Address.h"

namespace net {
	UDPSocket::~UDPSocket() {
		Close();
	}

	bool UDPSocket::Open() {
		handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (handle <= 0) {
			std::cerr << "Failed to create socket" << std::endl;
			return false;
		}

		return handle > 0;
	}

	bool UDPSocket::Bind(unsigned short port) {
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

	void UDPSocket::Close() {
		#if (PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX)
			close(handle);
		#elif PLATFORM == PLATFORM_WINDOWS
			closesocket(handle);
		#endif
		handle = -1;
	}

	bool UDPSocket::IsOpen() const {
		return handle != -1;
	}

	bool UDPSocket::Send(const Address& dest, const void* data, int size) {
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

	int UDPSocket::Receive(Address& sender, void* data, int size) {
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
			//std::cerr << "NO BYTE" << std::endl;
		}

		return read_bytes;
	}

	void UDPSocket::SetNonblock(const bool value) {
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
