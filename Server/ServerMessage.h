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

	ServerMessage() = default;
	ServerMessage(const std::string& rawMsg) :
		rawMsg(rawMsg),
		dobjID(0),
		directive(Directive::Unknown) {
	}
	~ServerMessage() = default;

	static const char Separator = '|';
	static const char DirectivePrefix = '#';

	void init();

private:
	Directive directive;
	unsigned long long dobjID;
	std::string rawMsg;
};
