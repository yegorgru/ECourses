#include "LoggerCreator.h"
#include "Logger.h"

int main() {
	ConsoleLoggerCreator consoleLoggerCreator;
	FileLoggerCreator fileLoggerCreator;
	Logger* log1 = consoleLoggerCreator.FactoryMethod(3);
	Logger* log2 = fileLoggerCreator.FactoryMethod(5);
	log1->Log("abc");
	log2->Log("cba");
	delete log1;
	delete log2;
	return 0;
}