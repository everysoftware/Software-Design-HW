#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <iostream>
#include <algorithm> // std::swap
#include <cstddef> // size_t
#include <initializer_list>
#include <vector>

// shared_ptr
template <typename T>
class DynArray {
	using value_type = T;
private:
	std::vector<T> arr_;
public:
	explicit DynArray() {}
	DynArray(std::initializer_list<T> lst) : arr_(std::vector<T>(lst)) {}
	void resize(size_t new_capacity) {
		arr_.resize(new_capacity);
	}
	void append(T const& x) {
		arr_.push_back(x);
	}
	T const& get(size_t i) const {
		return arr_[i];
	}
	T const& operator[](size_t i) const {
		return arr_[i];
	}
	T& operator[](size_t i) {
		return arr_[i];
	}
	size_t size() const noexcept {
		return arr_.size();
	}
	size_t capacity() const noexcept {
		return arr_.capacity();
	}
	DynArray& operator+=(DynArray const& rhs) {
		for (size_t i = 0; i < rhs.size(); ++i) {
			append(rhs[i]);
		}
		return *this;
	}
	DynArray& operator<<=(int k) noexcept {
		if (k < 0) {
			return operator>>=(-k);
		}
		size_t n = (size_t)k % size();
		for (size_t i = 0; i < n; ++i) {
			for (size_t i = 0; i < size() - 1; ++i) {
				std::swap(arr_[i], arr_[(i + 1) % size()]);
			}
		}
		return *this;
	}
	DynArray& operator>>=(int k) noexcept {
		if (k < 0) {
			return operator<<=(-k);
		}
		size_t n = (size_t)k % size();
		for (size_t i = 0; i < n; ++i) {
			for (size_t i = size() - 1; i >= 1; --i) {
				std::swap(arr_[i], arr_[i - 1]);
			}
		}
		return *this;
	}
};
template <typename T>
DynArray<T> operator+(DynArray<T> lhs, DynArray<T> const& rhs) {
	return lhs += rhs;
}
template <typename T>
DynArray<T> operator<<(DynArray<T> lhs, int k) noexcept {
	return lhs <<= k;
}
template <typename T>
DynArray<T> operator>>(DynArray<T> lhs, int k) noexcept {
	return lhs >>= k;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, DynArray<T> const& rhs) noexcept {
	for (size_t i = 0; i < rhs.size(); ++i) {
		os << rhs[i] << " ";
	}
	return os;
}

#endif