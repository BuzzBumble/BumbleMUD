#include "GameMessage.h"

const std::string& GameMessage::getID() {
	return id;
}

const std::vector<std::string>& GameMessage::getText() {
	return text;
}

const std::string& GameMessage::getPrompt() {
	return prompt;
}

void GameMessage::setID(const std::string& newID) {
	id = newID;
}

void GameMessage::setPrompt(const std::string& newPrompt) {
	prompt = newPrompt;
}

void GameMessage::addText(const std::string& newText) {
	text.push_back(newText);
}

void GameMessage::setNewline(bool value) {
	newline = value;
}

void GameMessage::display() const {
	for (const auto& msg : text) {
		std::cout << msg << std::endl;
	}
	
	std::cout << std::endl << prompt;
	if (newline) { std::cout << std::endl; }
}