#include "ReadFile.h"

#include <fstream>
#include <string>


void read_file_exceptions() {
	
}

ErrorCode read_file_error_codes() {
	auto code = ErrorCode::SuccessfullyRead;
	std::ifstream fin("task.txt", std::ios::ate);
	if (!fin.is_open()) {
		code = ErrorCode::FileDidntOpen;
	}
	else {
		long size = fin.tellg();
		if (size <= 0) {
			code = ErrorCode::UnknownSize;
		}
		else {
			std::string fileData;
			fileData.reserve(size);
			if (fileData.capacity() != size) {
				code = ErrorCode::NotEnoughMemory;
			}
			else {
				try
				{
					fileData = std::string((std::istreambuf_iterator<char>(fin)),
						std::istreambuf_iterator<char>());
				}
				catch (const std::exception&)
				{
					code = ErrorCode::ReadFailed;
				}
				if (fileData.size() != size) {
					code = ErrorCode::ReadFailed;
				}
			}
		}
		fin.close();
		if (fin.is_open() && code == ErrorCode::SuccessfullyRead) {
			code = ErrorCode::FileDidntClose;
		}
	}
	return code;
}

const char* FileOpenFailed::what() const noexcept {
	return "Can't open file";
}

const char* SizeDeterminationFailed::what() const noexcept {
	return "Can't determine size of file";
}

const char* MemoryAllocationFailed::what() const noexcept {
	return "Can't allocate memory";
}

const char* ReadFailed::what() const noexcept {
	return "Can't read file";
}

const char* FileCloseFailed::what() const noexcept {
	return "Can't close file";
}