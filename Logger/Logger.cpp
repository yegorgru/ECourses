#include "Logger.h"

Logger::Logger(int level) : m_Level(level) {}

void Logger::Log(const std::string& message) {
	LogHeader();
	LogMessage(message);
	LogFooter();
}

ConsoleLogger::ConsoleLogger(int level) : Logger(level) {}

void ConsoleLogger::LogHeader() {
	auto timenow =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time(ctime(&timenow));
	time.pop_back();
	std::cout << "Level: " << m_Level << " Timestamp: " << time << " [";
}

void ConsoleLogger::LogMessage(const std::string& message) {
	std::cout << message;
}

void ConsoleLogger::LogFooter() {
	std::cout << "]" << std::endl;
}

FileLogger::FileLogger(int level) : Logger(level), fout("log.txt") {}

void FileLogger::LogHeader() {
	if (!fout.is_open()) return;
	auto timenow =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time(ctime(&timenow));
	time.pop_back();
	fout << "Level: " << m_Level << " Timestamp: " << time << " [";
}

void FileLogger::LogMessage(const std::string& message) {
	if (!fout.is_open()) return;
	fout << message;
}

void FileLogger::LogFooter() {
	if (!fout.is_open()) return;
	fout << "]" << std::endl;
}