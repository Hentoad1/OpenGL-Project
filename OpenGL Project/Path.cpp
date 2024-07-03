#include "pch.h"

#include "Path.h"

std::string CalculatePath(std::string basepath, std::string filepath) {
	
	std::filesystem::path base = std::filesystem::path(basepath);
	std::filesystem::path file = std::filesystem::path(file);
	
	return base.replace_filename("").replace_extension("").generic_string() + file.filename().generic_string();
}