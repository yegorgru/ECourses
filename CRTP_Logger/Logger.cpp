#include "Logger.h"

#include <iostream>
#include <chrono>
#include <stdexcept>

ConsoleLogger::ConsoleLogger(int level) :
	Logger<ConsoleLogger>(level) {}

void ConsoleLogger::LogHeader() {
	auto timenow =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time(ctime(&timenow));
	time.pop_back();
	std::cout << "Level: " << m_Level << " Timestamp: " << time << " [";
}

void ConsoleLogger::LogFooter() {
	std::cout << "]" << std::endl;
}

FileLogger::FileLogger(int level) :
	Logger<FileLogger>(level),
	fout("log.txt") {
	if (!fout.is_open()) {
		throw std::runtime_error("Could not open file in a FileLogger");
	}
}

void FileLogger::LogHeader() {
	auto timenow =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time(ctime(&timenow));
	time.pop_back();
	fout << "Level: " << m_Level << " Timestamp: " << time << " [";
}

void FileLogger::LogFooter() {
	fout << "]" << std::endl;
}
