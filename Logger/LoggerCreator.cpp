#include "LoggerCreator.h"

Logger* ConsoleLoggerCreator::FactoryMethod(int level) const {
	return new ConsoleLogger(level);
}

Logger* FileLoggerCreator::FactoryMethod(int level) const {
	return new FileLogger(level);
}