#pragma once

#include "pch.h"

#include "ModelData.h"

class CustomImporter {

public:
	CustomImporter(const CustomImporter& ref) {
		throw;
	}

	CustomImporter() {}

	~CustomImporter();
	
	//Creates ModelData Object and returns a pointer to it.
	ModelData* Import(const std::string& path);

	//Takes a ModelData Object, Attaches it to OpenGL and returns subsequent buffer object.
	ModelBuffers* Attach(ModelData*);

	//Creates a ModelData Object, Attaches it, returns buffer object, and deletes unnecessary ModelData.
	ModelBuffers* ImportAndAttach(const std::string& path);

private:
	std::vector<ModelData*> mData;
	std::vector<ModelBuffers*> mBuffers;
};