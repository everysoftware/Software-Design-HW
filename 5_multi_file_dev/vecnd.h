#ifndef VECND_H
#define VECND_H

#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "mat2d.h"

class VecND {
private:
	size_t size_ = 0;
	double* data_ = nullptr;
public:
	VecND() = default;
	VecND(size_t n) : size_(n), data_(new double[n]) {}
	VecND(std::initializer_list<double> lst) {
		auto it = lst.begin();
		size_ = lst.size();
		data_ = new double[size_];
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = *it;
			++it;
		}
	}
	~VecND() {
		delete[] data_;
	}
	VecND(VecND const& rhs) : size_(rhs.size_), data_(new double[rhs.size_]) {
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	void swap(VecND& rhs) noexcept {
		std::swap(rhs.data_, data_);
		std::swap(rhs.size_, size_);
	}
	VecND(VecND&& rhs) noexcept {
		swap(rhs);
	}
	VecND& operator=(VecND const& rhs) noexcept {
		if (this != &rhs) {
			VecND(rhs).swap(*this);
		}
		return *this;
	}
	VecND& operator=(VecND&& rhs) noexcept {
		swap(rhs);
		return *this;
	}
	void resize(size_t new_size) {
		auto temp = new double[new_size];
		size_t n = size_ > new_size ? new_size : size_;
		for (size_t i = 0; i < n; ++i) {
			temp[i] = data_[i];
		}
		delete[] data_;
		data_ = temp;
		size_ = new_size;
	}
	void fill(double x) noexcept {
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = x;
		}
	}
	void fill(std::initializer_list<double> lst) noexcept {
		auto it = lst.begin();
		for (size_t i = 0; i < lst.size(); ++i) {
			data_[i] = *it;
			++it;
		}
	}
	size_t size() const noexcept {
		return size_;
	}
	double operator[] (size_t j) const noexcept {
		return data_[j];
	}
	double& operator[] (size_t j) noexcept {
		return data_[j];
	}
};
#endif