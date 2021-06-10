#include <iostream>
#include <string>


void displayMessage(std::string message);
void receiveMessage(std::string& buf);

int main() {
	std::string inbuf;
	std::string outbuf = "Hello. Type 'sup' to continue";

	displayMessage(outbuf);

	receiveMessage(inbuf);

	if (inbuf == "sup") {
		displayMessage("Nice");
	}
	return 0;
}

void displayMessage(std::string message) {
	std::cout <<
		std::endl <<
		"------------------------------------" <<
		std::endl <<
		"[SERVER]" <<
		std::endl <<
		message <<
		std::endl;
}

void receiveMessage(std::string& buf) {
	buf.clear();
	std::cin >> buf;
}