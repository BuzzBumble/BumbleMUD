#pragma once

#include <string>

class DataObject {
public:
	static unsigned long long NextID();

	DataObject() = default;
	DataObject(const std::string& name, const std::string& description);

	unsigned long long GetDobjID() const;
	std::string GetName() const;
	std::string GetDescription() const;
protected:
	void AssignDobjID();
	static unsigned long long DOBJIDCOUNTER;
	unsigned long long dobjID;

	std::string name;
	std::string description;
};
