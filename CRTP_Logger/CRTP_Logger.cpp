#include <iostream>

#include "Logger.h"

int main()
{
    ConsoleLogger logger(5);
    logger.Log("Hello", " from ", "console", "!");
}