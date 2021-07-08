#pragma once

#include <string>

template <typename T>
class Logger
{
public:
	Logger(int level);

	void Log(const std::string& message);

protected:
	int m_Level;
};

class ConsoleLogger : public Logger<ConsoleLogger> {
public:
	ConsoleLogger(int level);

	void LogHeader();
	void LogFooter();
	void LogMessage(const std::string& message);
};

template <typename T>
Logger<T>::Logger(int level) {
	m_Level = level;
}

template <typename T>
void Logger<T>::Log(const std::string& message) {
	auto p = static_cast<T*>(this);
	p->LogHeader();
	p->LogMessage(message);
	p->LogFooter();
}