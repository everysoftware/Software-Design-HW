#ifndef SLAE_H
#define SLAE_H

#include <exception>
#include <string>
#include "vecnd.h"
#include "mat2d.h"

class SLAEException : public std::exception {
public:
	SLAEException(std::string const& s) {
		what_ = s;
	}
	const char* what() const noexcept {
		return what_.c_str();
	}
private:
	std::string what_;
};

class ZeroDeterminantException : public SLAEException {
public:
	ZeroDeterminantException() : SLAEException("Zero determinant") {}
};

// System of Linear Algebric Equations
class SLAE {
private:
	Mat2D matrix_;
	VecND free_coef_;
public:
	SLAE(Mat2D const& matrix, VecND const& free_coef) : matrix_(matrix), free_coef_(free_coef) {
		if (!matrix_.is_squared() || matrix_.cols() != free_coef_.size()) {
			throw SizeException();
		}
	}
	VecND solve() const {
		double det = matrix_.det();
		if (det == 0) {
			throw ZeroDeterminantException();
		}
		VecND sol(free_coef_.size());
		for (size_t i = 0; i < sol.size(); ++i) {
			sol[i] = matrix_.replace_col(i, free_coef_).det() / det;
		}
		return sol;
	}
};

#endif
