#pragma once

class DataObject {
public:
	static unsigned long long NextID();

	const unsigned long long& GetDobjID();
protected:
	void AssignDobjID();
	static unsigned long long DOBJIDCOUNTER;
	unsigned long long dobjID = 0;
};
