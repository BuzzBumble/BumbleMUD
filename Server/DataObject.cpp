#include "DataObject.h"

unsigned long long DataObject::DOBJIDCOUNTER = 1;

unsigned long long DataObject::NextID() {
	return DOBJIDCOUNTER++;
}

void DataObject::AssignDobjID() {
	dobjID = NextID();
}

const unsigned long long& DataObject::GetDobjID() {
	return dobjID;
}
