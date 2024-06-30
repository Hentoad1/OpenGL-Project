#pragma once

#include "pch.h"

#include "ModelData.h"

struct Buffer {
public:
	template <typename T>
	void Append(std::vector<T> vec) {

		size_t vector_size = vec.size();
		size_t vector_size_bytes = sizeof(vector_size);
		uint8_t* vector_size_buffer = static_cast<uint8_t*>(static_cast<void*>(&vector_size));

		Append(vector_size_buffer, vector_size_bytes);

		size_t vector_content_size_bytes = sizeof(T) * vec.size();
		uint8_t* vector_content = static_cast<uint8_t*>(static_cast<void*>(&vec[0]));
		
		Append(vector_content, vector_content_size_bytes);
	}

	void Append(uint8_t* bytes, size_t count) {
		data.insert(data.end(), bytes, bytes + count);

	}

	void Append(uint8_t byte) {
		data.push_back(byte);
	}

	void Append(const Buffer& other) {
		for (int i = 0; i < other.GetData().size(); ++i) {
			data.push_back(other.GetData()[i]);
		}
	}

	void Read(void* dest, size_t length, int offset) {
		memcpy(dest, (&data[0] + offset), length);
	}

	std::vector<uint8_t> GetData() const {
		return data;
	}

private:
	std::vector<uint8_t> data;
};

Buffer ModelToBuffer(ModelData*);

ModelData* BufferToModel(Buffer);