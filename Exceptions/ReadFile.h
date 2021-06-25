#pragma once

#include <exception>

class FileOpenFailed : public std::exception {
public:
	const char* what() const noexcept override;
};

class SizeDeterminationFailed : public std::exception {
public:
	const char* what() const noexcept override;
};

class MemoryAllocationFailed : public std::exception {
public:
	const char* what() const noexcept override;
};

class ReadFailed : public std::exception {
public:
	const char* what() const noexcept override;
};

class FileCloseFailed : public std::exception {
public:
	const char* what() const noexcept override;
};


void read_file_exceptions();

enum class ErrorCode {
	FileOpenFailed = -5,
	FileCloseFailed,
	SizeDeterminationFailed,
	MemoryAllocationFailed,
	ReadFailed,
	SuccessfullyRead
};

ErrorCode read_file_error_codes();