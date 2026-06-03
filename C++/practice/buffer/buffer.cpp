#include <iostream>
#include <cstring>
#include "buffer.h"

Buffer::Buffer(int size)
	: size_ (size)
	, data_ (new int[size])
{}

Buffer::Buffer(const Buffer& other)
	: size_ (other.size_)
	, data_ (new int[other.size_])
{
	std::memcpy(data_, other.data_, size_ * sizeof(int));
}

Buffer::Buffer(Buffer&& other) noexcept
	: size_ (other.size_)
	, data_ (other.data_)
{
	other.size_ = 0;
	other.data_ = nullptr;
}

Buffer& Buffer::operation=(Buffer&& other) noexcept {
	if(this == &other) return *this;

	delete[] data_;

	data_ = other.data_;
	size_ = other.size_;

	other.data_ = nullptr;
	other.size_ = 0;

	return *this;
}

Buffer::~Buffer() { delete[] data_; }
