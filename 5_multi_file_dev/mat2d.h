#ifndef MAT2D_H
#define MAT2D_H

#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <iostream>
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

class Mat2D {
private:
	size_t rows_ = 0;
	size_t cols_ = 0;
	VecND* data_ = nullptr;
public:
	Mat2D(size_t rows, size_t cols, double x = 0) : rows_(rows), cols_(cols), data_(new VecND[rows]) {
		for (size_t i = 0; i < rows_; ++i) {
			data_[i].resize(cols);
			data_[i].fill(x);
		}
	}
	Mat2D(Mat2D const& rhs) : rows_(rhs.rows_), cols_(rhs.cols_), data_(new VecND[rows_]) {
		for (size_t i = 0; i < rows_; ++i) {
			data_[i].resize(rhs.cols_);
			for (size_t j = 0; j < cols_; ++j) {
				data_[i][j] = rhs.data_[i][j];
			}
		}
	}
	Mat2D(VecND const& rhs) : rows_(rhs.size()), cols_(1), data_(new VecND[rows_]) {
		for (size_t i = 0; i < rows_; ++i) {
			data_[i].resize(1);
			data_[i][0] = rhs[i];
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
	Mat2D(std::initializer_list<std::initializer_list<double>> lst) {
		// мне лень
		auto it = lst.begin();
		rows_ = lst.size();
		cols_ = (*it).size();
		data_ = new VecND[rows_];
		// std::cout << *it << std::endl;
		for (size_t i = 0; i < rows_; ++i) {
			data_[i].resize(cols_);
			data_[i].fill(*it);
			++it;
		}
	}
	size_t rows() const noexcept {
		return rows_;
	}
	size_t cols() const noexcept {
		return cols_;
	}
	VecND const& operator[](size_t i) const noexcept {
		return data_[i];
	}
	VecND& operator[](size_t i) noexcept {
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
		auto temp = new VecND[new_rows];
		for (size_t i = 0; i < new_rows && i < rows_; ++i) {
			for (size_t j = 0; j < new_cols && j < cols_; ++j) {
				temp[i][j] = data_[i][j];
			}
		}
		delete[] data_;
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
	Mat2D replace_col(size_t col, VecND const& new_col) const {
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

inline Mat2D operator+(Mat2D lhs, Mat2D const& rhs) {
	return lhs += rhs;
}
inline Mat2D operator*(Mat2D const& lhs, Mat2D const& rhs) {
	return lhs.product(rhs);
}
inline std::ostream& operator<<(std::ostream& os, Mat2D const& m) noexcept {
	for (size_t i = 0; i < m.rows(); ++i) {
		for (size_t j = 0; j < m.cols(); ++j) {
			os << m[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}
inline std::istream& operator>>(std::istream& is, Mat2D& m) noexcept {
	for (size_t i = 0; i < m.rows(); ++i) {
		for (size_t j = 0; j < m.cols(); ++j) {
			is >> m[i][j];
		}
	}
	return is;
}

#endif
