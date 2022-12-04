#ifndef VECND_H
#define VECND_H

#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <type_traits> // std::is_arithmetic
#include "mat2d.h"

template <typename T>
class VecND { 
	static_assert(std::is_arithmetic_v<T>, "Template argument T must be arithmetic");
	using value_type = T;
private:
	size_t size_ = 0;
	std::vector<T> data_;
public:
	VecND(size_t n, T const& x = 0) : size_(n), data_(std::vector<T>(n, x)) {}
	VecND(std::initializer_list<T> lst) : size_(lst.size()), data_(std::vector<T>(lst)) {}
	void resize(size_t new_size) {
		data_.resize(new_size);
		size_ = new_size;
	}
	size_t size() const noexcept {
		return size_;
	}
	T const& operator[] (size_t j) const noexcept {
		return data_[j];
	}
	T& operator[] (size_t j) noexcept {
		return data_[j];
	}
};
#endif