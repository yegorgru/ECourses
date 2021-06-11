#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <fstream>

class Logger {
public:
	Logger(int level);

	virtual ~Logger() = default;

	void Log(const std::string& message);

protected:
	int m_Level;

private:
	virtual void LogHeader() = 0;
	virtual void LogMessage(const std::string& message) = 0;
	virtual void LogFooter() = 0;
};

class ConsoleLogger : public Logger {
public:
	ConsoleLogger(int level);

	virtual ~ConsoleLogger() = default;

private:
	virtual void LogHeader() override;

	virtual void LogMessage(const std::string& message) override;

	virtual void LogFooter() override;
};

class FileLogger : public Logger {
public:
	FileLogger(int level);

	virtual ~FileLogger() = default;

private:
	virtual void LogHeader() override;

	virtual void LogMessage(const std::string& message) override;

	virtual void LogFooter() override;

	std::ofstream fout;
};