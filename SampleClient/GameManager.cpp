#include "GameManager.h"

#include <string>
#include <fstream>
#include <sstream>


const std::string GameManager::FileName = "game_messages.json";

bool GameManager::init() {
	if (!readMessagesFile()) { return false; }
	return true;
}

const GameMessage& GameManager::getMessage(const std::string& messageID) {
	return *Messages[messageID];
}

bool GameManager::readMessagesFile() {
	std::ifstream msgFile(FileName);
	std::ostringstream oss;

	if (!msgFile) {
		std::cout << "[GameManager/ReadMessageFile] Message File could not be opened" << std::endl;
		return false;
	}

	oss << msgFile.rdbuf();

	nlohmann::json jsonArr = nlohmann::json::parse(oss.str());
	for (const auto& msg : jsonArr) {
		GameMessage* newMessage = new GameMessage(msg["id"].get<std::string>());
		for (const auto& textLine : msg["text"]) {
			newMessage->addText(textLine.get<std::string>());
		}
		newMessage->setPrompt(msg["prompt"].get<std::string>());
		newMessage->setNewline(msg["newline"].get<bool>());
		Messages[newMessage->getID()] = std::move(newMessage);
	}

	return true;
}
