#pragma once

#include <unordered_map>

#include "json.hpp"
#include "GameMessage.h"


class GameManager {
public:
	static const std::string FileName;

	GameManager() = default;

	bool init();
	bool readMessagesFile();

	int readInput();

	const GameMessage& getMessage(const std::string& messageID);
	std::string getLastInput();

private:
	std::unordered_map<std::string, GameMessage*> Messages;

	std::string lastInput;
};
