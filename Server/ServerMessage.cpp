#include "ServerMessage.h"

static std::vector<std::string> splitMessage(const std::string& buf);
static std::string ltrim(const std::string& str);
static std::string rtrim(const std::string& str);
static std::string trim(const std::string & str);

void ServerMessage::init() {
	msgVec = splitMessage(rawMsg);
	directive = ServerMessage::StrToDir(msgVec[0]);
	dobjID = std::stoull(msgVec[1]);
}

ServerMessage::Directive ServerMessage::StrToDir(const std::string& s) {
	if (s == "#CP") {
		return ServerMessage::Directive::ConnectPlayer;
	}
	if (s == "#R") {
		return ServerMessage::Directive::Room;
	}
	if (s == "#E") {
		return ServerMessage::Directive::Enter;
	}
	if (s == "#EP") {
		return ServerMessage::Directive::EnterPlayer;
	}
	if (s == "#L") {
		return ServerMessage::Directive::Leave;
	}
	if (s == "#LP") {
		return ServerMessage::Directive::LeavePlayer;
	}
	if (s == "#U") {
		return ServerMessage::Directive::Update;
	}
	if (s == "#S") {
		return ServerMessage::Directive::Say;
	}
	if (s == "#X") {
		return ServerMessage::Directive::Exit;
	}
	return ServerMessage::Directive::Unknown;
}

std::ostream& operator << (std::ostream& out, const ServerMessage& sm) {
	out << "ServerMessage[";
	size_t i;
	for (i = 0; i < sm.msgVec.size() - 1; i++) {
		out << sm.msgVec[i] << ", ";
	}
	out << sm.msgVec[i] << "]";
	return out;
}

static std::vector<std::string> splitMessage(const std::string& buf) {
	std::vector<std::string> strVec;
	std::istringstream ss = std::istringstream(buf);
	std::string token;
	while (std::getline(ss, token, ServerMessage::Separator)) {
		token = trim(token);
		if (!token.empty()) {
			strVec.push_back(trim(token));
		}
	}

	return strVec;
}

static std::string ltrim(const std::string& str) {
	size_t start = str.find_first_not_of(" \n\r\t\f\v");
	return (start == std::string::npos) ? "" : str.substr(start);
}

static std::string rtrim(const std::string& str) {
	size_t end = str.find_last_not_of(" \n\r\t\f\v");
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

static std::string trim(const std::string& str) {
	return rtrim(ltrim(str));
}
