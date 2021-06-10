#include "Room.h"
#include "Character.h"

#include <iostream>
#include <string>
#include <sstream>

void displayMessage(const std::string& message);
void receiveMessage(std::ostringstream& buf);

int main() {
	std::ostringstream inbuf;

	std::string intro_message = "Welcome to BumbleMUD\nWhat is your character's name? ";

	displayMessage(intro_message);

	receiveMessage(inbuf);
	Character player(inbuf.str(), 100);
	player.init();

	displayMessage("Hello " + player.getName() + ". Let's get started", true);

	Room room(std::pair<int, int>(0, 0));
	room.init();

	displayMessage("You are in room " + std::to_string(room.getID()), true);

	if (inbuf.str() == "room") {
		displayMessage("Nice", true);
	}

	return 0;
}

void handleMessage(const Room& room, const std::string& message) {
	switch (message) {
	}
}

void displayMessage(const std::string& message, bool newline) {
	std::cout <<
		std::endl <<
		"------------------------------------" <<
		std::endl <<
		"[SERVER]" <<
		std::endl <<
		message;
	if (newline) {
		std::cout << std::endl;
	}
}

void receiveMessage(std::ostringstream& buf) {
	buf.clear();
	std::string str;
	std::cin >> str;
	buf << str;
}