#include "FileWrapper.h"

FileWrapper::FileWrapper(const std::string& path) : m_File(path) {}

FileWrapper::~FileWrapper() {
	m_File.close();
}

void FileWrapper::Open(const std::string& path) {
	m_File.open(path);
}

std::ofstream& FileWrapper::GetFile() {
	if (!m_File.is_open()) {
		throw std::runtime_error("unable to open file");
	}
	return m_File;
}

void WriteToFile(const std::string& message) {
	static std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);
	FileWrapper fileWrapper("examle.txt");
	if (!fileWrapper.GetFile().is_open()) {
		throw std::runtime_error("unable to open file");
	}
	fileWrapper.GetFile() << message << std::endl;
}