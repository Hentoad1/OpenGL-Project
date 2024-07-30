#include "pch.h"

#include "MemoryMapper.h"

void SourceToBuild(const std::string& read, const std::string& write) {

	std::cout << "readLoc: " << read << std::endl;
	std::cout << "writeLoc: " << write << std::endl;

	ModelData* model = ASSIMP_LOAD(read);

	const Buffer& buf = ModelToBuffer(model);

	FILE* out;
	fopen_s(&out, write.c_str(), "wb");
	fwrite(&buf.GetData()[0], buf.GetData().size(), 1, out);

	fclose(out);
}

ModelData* LoadBinaryFile(const std::string& path) {

	std::vector<uint8_t> data;

	FILE* f;
	fopen_s(&f, path.c_str(), "rb");
	
	if (f == nullptr) {
		throw;
	}

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	data.resize(size);
	fread(&data[0], 1, size, f);

	Buffer buf = Buffer(data);

	ModelData* d = BufferToModel(buf);

	return d;
}