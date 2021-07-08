#include "Logger.h"

#include <iostream>
#include <chrono>

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
