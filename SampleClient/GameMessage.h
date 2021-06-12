#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class GameMessage {
public:
	GameMessage(const std::string& id)
		: id(id) {}

	const std::string& getID();
	const std::vector<std::string>& getText();
	const std::string& getPrompt();

	void setID(const std::string& newID);
	void setPrompt(const std::string& newPrompt);
	void addText(const std::string& newText);
	void setNewline(bool value);

	void display() const;
private:
	std::string id;
	std::vector<std::string> text;
	std::string prompt;
	bool newline = false;
};
