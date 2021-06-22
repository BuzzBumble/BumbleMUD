#include "Responder.h"
#include <sstream>

const std::string Responder::Separator = "|";
const std::string Responder::Prefix = "#";

std::string Responder::DirToStr(const Directive& dir) {
	std::string str = "CP";
	switch (dir) {
	case Directive::ConnectPlayer:
		return Prefix + "CP";
	case Directive::Room:
		return Prefix + "R";
	case Directive::Enter:
		return Prefix + "E";
	case Directive::EnterPlayer:
		return Prefix + "EP";
	case Directive::Leave:
		return Prefix + "L";
	case Directive::LeavePlayer:
		return Prefix + "LP";
	case Directive::Update:
		return Prefix + "U";
	case Directive::Say:
		return Prefix + "S";
	case Directive::Exit:
		return Prefix + "X";
	default:
		return "";
	}
}

Responder::Responder(Directive directive)
	: directive(directive) {
}

Responder::Responder(Directive directive, const DataObject& dataObject)
	: directive(directive)
	, dataObject(dataObject) {
}

void Responder::SetDobj(const DataObject& dobj) {
	dataObject = dobj;
}

static std::string buildCP(const DataObject& dataObject);

const std::string Responder::GetResponse() const {

	std::string response;

	switch (directive) {
	case Directive::ConnectPlayer:
		response = buildCP(dataObject);
		return response.c_str();
	default:
		return "";
	}
}

static std::string buildCP(const DataObject& dataObject) {
	std::ostringstream oss;
	oss << Responder::DirToStr(Responder::Directive::ConnectPlayer) << Responder::Separator <<
		dataObject.GetDobjID() << Responder::Separator <<
		dataObject.GetName() << Responder::Separator <<
		dataObject.GetDescription() << Responder::Separator;

	return oss.str();
}
