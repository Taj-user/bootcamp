#pragma once

class Buffer {
	private:
		int size_;
		int* data;

	Buffer(int size);
	Buffer(const Buffer& other);
	Buffer(Buffer&& other) noexcept;
	Buffer& operator=(Buffer&& other) noexcept;
	~Buffer();
};
