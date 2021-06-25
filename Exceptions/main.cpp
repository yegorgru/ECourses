#include <iostream>

#include "ReadFile.h"

int main() {
    read_file_exceptions("SomeText.txt");
    switch (read_file_error_codes("SomeText.txt")) {
	case ErrorCode::FileOpenFailed : {
		std::cout << "Can't open file" << std::endl;
		break;
	}
	case ErrorCode::SizeDeterminationFailed : {
		std::cout << "Can't determine size of file" << std::endl;
		break;
	}
	case ErrorCode::MemoryAllocationFailed : {
		std::cout << "Can't allocate memory" << std::endl;
		break;
	}
	case ErrorCode::ReadFailed : {
		std::cout << "Can't read file" << std::endl;
		break;
	}
	case ErrorCode::FileCloseFailed : {
		std::cout << "Can't close file" << std::endl;
		break;
	}
    }
}
