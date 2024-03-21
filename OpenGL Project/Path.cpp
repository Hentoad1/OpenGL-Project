#include "pch.h"

#include "Path.h"

std::string CalculatePath(std::string basepath, std::string filepath) {
	std::string baseWithoutFile = basepath.substr(0, basepath.find_last_of("\\"));


	size_t lastSlashOfFile = filepath.find_last_of("\\");
	std::string fileNameWithExt = filepath.substr(lastSlashOfFile, filepath.size() - lastSlashOfFile);

	return baseWithoutFile + fileNameWithExt;
}