#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class ServerMessage {
public:
	enum class Directive {
		ConnectPlayer, // CP
		Room, // R
		Enter, // E
		EnterPlayer, // EP
		Leave, // L
		LeavePlayer, // LP
		Update, // U
		Say, // S
		Exit, // X
		Unknown // Unknown Directive
	};

	static ServerMessage::Directive StrToDir(const std::string& s);
	static const char Separator = '|';
	static const char DirectivePrefix = '#';

	ServerMessage() = default;
	~ServerMessage() = default;

	void parse(const std::string& rawMsg);
	friend std::ostream& operator <<(std::ostream& out, const ServerMessage& sm);

private:
	Directive directive = Directive::Unknown;
	unsigned long long dobjID = 0;
	std::string rawMsg;
	std::vector<std::string> msgVec;
};
