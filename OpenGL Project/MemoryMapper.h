#pragma once

#include "pch.h"

#include "Model.h"

#include "Buffer.h"

void SourceToBuild(const std::string& read, const std::string& write);

Model* LoadBinaryFile(const std::string&);