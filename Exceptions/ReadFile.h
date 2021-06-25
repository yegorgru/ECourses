#pragma once

void read_file_exceptions();

enum class ErrorCode {
	FileDidntOpen = -5,
	FileDidntClose,
	UnknownSize,
	NotEnoughMemory,
	ReadFailed,
	SuccessfullyRead
};

ErrorCode read_file_error_codes();