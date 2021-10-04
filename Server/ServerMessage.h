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
	ServerMessage(const std::string& rawMsg) :
		rawMsg(rawMsg),
		dobjID(0),
		directive(Directive::Unknown) {
	}
	~ServerMessage() = default;

	void init();
	friend std::ostream& operator <<(std::ostream& out, const ServerMessage& sm);

private:
	Directive directive;
	unsigned long long dobjID;
	std::string rawMsg;
	std::vector<std::string> msgVec;
};
