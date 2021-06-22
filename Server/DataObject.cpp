#include "DataObject.h"

unsigned long long DataObject::DOBJIDCOUNTER = 1;

DataObject::DataObject(const std::string& name, const std::string& description)
	: name(name)
	, description(description) {
}

unsigned long long DataObject::NextID() {
	return DOBJIDCOUNTER++;
}

void DataObject::AssignDobjID() {
	dobjID = NextID();
}

unsigned long long DataObject::GetDobjID() const {
	return dobjID;
}

std::string DataObject::GetName() const {
	return name;
}

std::string DataObject::GetDescription() const {
	return description;
}
