#pragma once

#include <string>
#include <iostream>
#include <fstream>

template <typename T>
class Logger
{
public:
	Logger(int level);

	template <typename... Args>
	void Log(Args&&... args);

protected:
	int m_Level;
};

class ConsoleLogger : public Logger<ConsoleLogger> {
public:
	ConsoleLogger(int level);

	void LogHeader();
	void LogFooter();

	template <typename... Args>
	void LogMessage(Args&&... args);
};

class FileLogger : public Logger<FileLogger> {
public:
	FileLogger(int level);

	void LogHeader();
	void LogFooter();

	template <typename... Args>
	void LogMessage(Args&&... args);

private:
	std::ofstream fout;
};

template <typename T>
Logger<T>::Logger(int level) {
	m_Level = level;
}

template <typename T>
template <typename... Args>
void Logger<T>::Log(Args&&... args) {
	auto p = static_cast<T*>(this);
	p->LogHeader();
	p->LogMessage(std::forward<Args>(args)...);
	p->LogFooter();
}

template <typename... Args>
void ConsoleLogger::LogMessage(Args&&... args) {
	(std::cout << ... << args);
}

template <typename... Args>
void FileLogger::LogMessage(Args&&... args) {
	(fout << ... << args);
}