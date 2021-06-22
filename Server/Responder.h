#pragma once

#include "DataObject.h"

class Responder {
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
		Exit // X
	};

	static const std::string Separator;
	static const std::string Prefix;

	static std::string DirToStr(const Directive& dir);

	Responder() = default;
	Responder(Directive directive);
	Responder(Directive directive, const DataObject& dataObject);
	
	void SetDobj(const DataObject& dobj);

	const std::string GetResponse() const;

private:
	Directive directive;
	DataObject dataObject;
};
