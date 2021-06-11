#pragma once

#include "Logger.h"

class Creator {
public:
	virtual ~Creator() = default;
	virtual Logger* FactoryMethod(int level) const = 0;
};

class ConsoleLoggerCreator : public Creator {
public:
	Logger* FactoryMethod(int level) const override;
};

class FileLoggerCreator : public Creator {
public:
	Logger* FactoryMethod(int level) const override;
};