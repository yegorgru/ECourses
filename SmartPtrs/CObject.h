#pragma once

#include <string>

class CObject {
public:
	virtual std::string foo() const;

	virtual ~CObject() = default;
};

class DerivedObject : public CObject {
public:
	DerivedObject() = default;

	DerivedObject(const std::string& s, int n);

	std::string foo() const override;
};