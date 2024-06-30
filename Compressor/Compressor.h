#pragma once

#include "pch.h"

namespace Compressor {

	void __declspec(dllexport) PackFile();

	void __declspec(dllexport) UnpackFile();

	void __declspec(dllexport) ImportFile(const std::string& path);
}
