#pragma once

class Address {
public:
	Address() = default;

	Address(unsigned char ip1,
		unsigned char ip2,
		unsigned char ip3,
		unsigned char ip4,
		unsigned short port);

	Address(unsigned int addr, unsigned short port);

	unsigned int GetAddress() const;

	unsigned char GetIP1() const;
	unsigned char GetIP2() const;
	unsigned char GetIP3() const;
	unsigned char GetIP4() const;

	unsigned short GetPort() const;

private:
	unsigned int address;
	unsigned short port;
};
