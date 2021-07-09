#include <iostream>

#include "Logger.h"

int main()
{
    ConsoleLogger logger(5);
    logger.Log("Hello", " from ", "console", "!");
    FileLogger fileLogger(3);
    fileLogger.Log("Hello", " from ", "file", "!");
}