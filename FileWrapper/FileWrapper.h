#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>

//ofstream already RAII, but for practice
class FileWrapper {
public:
	FileWrapper(const std::string& path);

	~FileWrapper();

	void Open(const std::string& path);

	std::ofstream& GetFile();

private:
	std::ofstream m_File;
};

void WriteToFile(const std::string& message);
