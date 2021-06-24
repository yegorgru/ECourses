#pragma once

#include <string>

class CObject {
public:
	virtual std::string foo() const;

	virtual ~CObject() = default;
};

class DerivedObject : public CObject {
	std::string foo() const override;
};