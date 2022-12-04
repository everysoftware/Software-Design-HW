#ifndef MAT2D_H
#define MAT2D_H

#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <type_traits>
#include "vecnd.h"

class MatrixException : public std::exception {
public:
	MatrixException(std::string const& s) {
		what_ = s;
	}
	const char* what() const noexcept {
		return what_.c_str();
	}
private:
	std::string what_;
};

class SizeException : public MatrixException {
public:
	SizeException() : MatrixException("Wrong size") {}
};

template <typename T>
class Mat2D {
	static_assert(std::is_arithmetic_v<T>, "Template argument T must be arithmetic");
	using value_type = T;
private:
	size_t rows_ = 0;
	size_t cols_ = 0;
	std::vector<VecND<T>> data_;
	using value_type = T;
public:
	Mat2D(size_t rows, size_t cols, T const& x = 0) : rows_(rows), cols_(cols) {
		for (size_t i = 0; i < rows_; ++i) {
			data_.emplace_back(cols_, x);
		}
	}
	Mat2D(Mat2D const& rhs) : rows_(rhs.rows_), cols_(rhs.cols_), data_(rhs.data_) {}
	Mat2D(VecND<T> const& rhs) : rows_(rhs.size()), cols_(1) {
		for (size_t i = 0; i < rows_; ++i) {
			data_.emplace_back(1, rhs[i]);
		}
	}
	void swap(Mat2D& rhs) noexcept {
		std::swap(rhs.rows_, rows_);
		std::swap(rhs.cols_, cols_);
		std::swap(rhs.data_, data_);
	}
	Mat2D(Mat2D&& rhs) noexcept {
		swap(rhs);
	}
	Mat2D& operator=(Mat2D const& rhs) {
		if (this != &rhs) {
			Mat2D(rhs).swap(*this);
		}
		return *this;
	}
	Mat2D& operator=(Mat2D&& rhs) noexcept {
		swap(rhs);
		return *this;
	}
	//&
	Mat2D(std::initializer_list<std::initializer_list<T>> lst) {
		auto it = lst.begin();
		rows_ = lst.size();
		cols_ = (*it).size();
		for (size_t i = 0; i < rows_; ++i) {
			data_.emplace_back(*it);
			++it;
		}
	}
	size_t rows() const noexcept {
		return rows_;
	}
	size_t cols() const noexcept {
		return cols_;
	}
	VecND<T> const& operator[](size_t i) const noexcept {
		return data_[i];
	}
	VecND<T>& operator[](size_t i) noexcept {
		return data_[i];
	}
	Mat2D& operator+= (Mat2D const& rhs) {
		if (rhs.cols_ != cols_ || rhs.rows_ != rows_) {
			throw SizeException();
		}
		for (size_t i = 0; i < rows_; ++i) {
			for (size_t j = 0; j < cols_; ++j) {
				data_[i][j] += rhs.data_[i][j];
			}
		}
		return *this;
	}
	void resize(size_t new_rows, size_t new_cols) {
		std::vector<VecND<T>> temp(new_rows);
		for (size_t i = 0; i < new_rows && i < rows_; ++i) {
			for (size_t j = 0; j < new_cols && j < cols_; ++j) {
				temp[i][j] = data_[i][j];
			}
		}
		data_ = temp;
		rows_ = new_rows;
		cols_ = new_cols;
	}
	Mat2D transposed() const {
		Mat2D temp(cols_, rows_);
		for (size_t i = 0; i < cols_; ++i) {
			for (size_t j = 0; j < rows_; ++j) {
				temp[i][j] = data_[j][i];
			}
		}
		return temp;
	}
	Mat2D product(Mat2D const& rhs) const {
		// lhs = {rows x cols} = {n1 x m1}
		// rhs = {rows x cols} = {n2 x m2}
		// res = {n1 x m2}
		if (cols_ != rhs.rows_) {
			throw SizeException();
		}
		Mat2D temp(rows_, rhs.cols_);
		for (size_t i = 0; i < temp.rows(); ++i) {
			for (size_t j = 0; j < temp.cols(); ++j) {
				for (size_t k = 0; k < cols_; ++k) {
					temp[i][j] += data_[i][k] * rhs.data_[k][j];
				}
			}
		}
		return temp;
	}
	Mat2D replace_col(size_t col, VecND<T> const& new_col) const {
		Mat2D temp(*this);
		for (size_t i = 0; i < rows_; ++i) {
			temp[i][col] = new_col[i];
		}
		return temp;
	}
	// M_{i, j}
	Mat2D minor(size_t row, size_t col) const {
		Mat2D temp(rows_ - 1, cols_ - 1);
		size_t di = 0;
		size_t dj = 0;
		for (size_t i = 0; i < rows_ - 1; ++i) {
			if (i == row) {
				di = 1;
			}
			dj = 0;
			for (size_t j = 0; j < cols_ - 1; ++j) {
				if (j == col) {
					dj = 1;
				}
				temp[i][j] = data_[i + di][j + dj];
			}
		}
		return temp;
	}
	double det() const {
		if (!is_squared()) {
			throw SizeException();
		}
		size_t n = rows_;
		if (n == 1) {
			return data_[0][0];
		}
		else if (n == 2) {
			return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
		}
		double res = 0;
		int pow1 = 1;
		for (size_t i = 0; i < cols_; i++) {
			res += pow1 * data_[i][0] * minor(i, 0).det();
			pow1 = -pow1;
		}
		return res;
	}
	bool is_squared() const noexcept {
		return rows_ == cols_;
	}
};

template <typename T>
inline Mat2D<T> operator+(Mat2D<T> lhs, Mat2D<T> const& rhs) {
	return lhs += rhs;
}
template <typename T>
inline Mat2D<T> operator*(Mat2D<T> const& lhs, Mat2D<T> const& rhs) {
	return lhs.product(rhs);
}
template <typename T>
inline Mat2D<T> operator*(Mat2D<T> const& lhs, VecND<T> const& rhs) {
	return operator*(lhs, static_cast<Mat2D<T>>(rhs));
}
template <typename T>
inline std::ostream& operator<<(std::ostream& os, Mat2D<T> const& rhs) noexcept {
	for (size_t i = 0; i < rhs.rows(); ++i) {
		for (size_t j = 0; j < rhs.cols(); ++j) {
			os << rhs[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}
template <typename T>
inline std::ostream& operator<<(std::ostream& os, VecND<T> const& rhs) noexcept {
	return operator<<(os, static_cast<Mat2D<T>>(rhs));
}
template <typename T>
inline std::istream& operator>>(std::istream& is, Mat2D<T>& rhs) noexcept {
	for (size_t i = 0; i < rhs.rows(); ++i) {
		for (size_t j = 0; j < rhs.cols(); ++j) {
			is >> rhs[i][j];
		}
	}
	return is;
}
template <typename T>
inline std::istream& operator>>(std::istream& is, VecND<T>& rhs) noexcept {
	return operator>>(is, static_cast<Mat2D<T>>(rhs));
}
#endif
