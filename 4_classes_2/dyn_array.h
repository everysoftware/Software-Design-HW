#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <iostream>
#include <algorithm> // std::swap
#include <cstddef> // size_t
#include <initializer_list>

// shared_ptr

class DynArray {
private:
	size_t size_;
	size_t capacity_;
	double* arr_;
public:
	explicit DynArray(size_t capacity = 0) : size_(0), capacity_(capacity), arr_(new double[capacity_]) {}
	DynArray(std::initializer_list<double> lst) :
		size_(lst.size()), capacity_(lst.size()), arr_(new double[capacity_]) {
		auto it = lst.begin();
		for (size_t i = 0; i < capacity_; ++i) {
			arr_[i] = *it;
			++it;
		}
	}
	~DynArray() {
		delete[] arr_;
	}
	DynArray(DynArray const& rhs) : size_(rhs.size_), capacity_(rhs.capacity_), arr_(new double[capacity_]) {
		for (size_t i = 0; i < capacity_; ++i) {
			arr_[i] = rhs.arr_[i];
		}
	}
	void swap(DynArray& rhs) noexcept {
		std::swap(size_, rhs.size_);
		std::swap(capacity_, rhs.capacity_);
		std::swap(arr_, rhs.arr_);
	}
	DynArray& operator= (DynArray const& rhs) {
		if (this != &rhs) {
			DynArray(rhs).swap(*this);
		}
		return *this;
	}
	void resize(size_t new_capacity) {
		auto temp = new double[new_capacity];
		auto n = new_capacity > size_ ? size_ : new_capacity;
		for (size_t i = 0; i < n; ++i) {
			temp[i] = arr_[i];
		}
		delete[] arr_;
		arr_ = temp;
		capacity_ = new_capacity;
		size_ = n;
	}
	void append(double x) {
		if (size_ == capacity_) {
			resize(size_ * 2);
		}
		arr_[size_] = x;
		++size_;
	}
	double get(size_t i) const {
		return arr_[i];
	}
	double operator[](size_t i) const {
		return arr_[i];
	}
	double& operator[](size_t i) {
		return arr_[i];
	}
	size_t size() const noexcept {
		return size_;
	}
	DynArray& operator+=(DynArray const& rhs) {
		resize(size_ + rhs.size_);
		for (size_t i = 0; i < rhs.size(); ++i) {
			append(rhs[i]);
		}
		return *this;
	}
	DynArray& operator<<=(int k) noexcept {
		if (k < 0) {
			return operator>>=(-k);
		}
		size_t n = (size_t)k % size_;
		for (size_t i = 0; i < n; ++i) {
			for (size_t i = 0; i < size_ - 1; ++i) {
				std::swap(arr_[i], arr_[(i + 1) % size_]);
			}
		}
		return *this;
	}
	DynArray& operator>>=(int k) noexcept {
		if (k < 0) {
			return operator<<=(-k);
		}
		size_t n = (size_t)k % size_;
		for (size_t i = 0; i < n; ++i) {
			for (size_t i = size_ - 1; i >= 1; --i) {
				std::swap(arr_[i], arr_[i - 1]);
			}
		}
		return *this;
	}
};
DynArray operator+(DynArray lhs, DynArray const& rhs) {
	return lhs += rhs;
}
DynArray operator<<(DynArray lhs, int k) noexcept {
	return lhs <<= k;
}
DynArray operator>>(DynArray lhs, int k) noexcept {
	return lhs >>= k;
}
std::ostream& operator<<(std::ostream& os, DynArray const& rhs) noexcept {
	for (size_t i = 0; i < rhs.size(); ++i) {
		os << rhs[i] << " ";
	}
	return os;
}

#endif