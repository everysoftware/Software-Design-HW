#ifndef SLAE_H
#define SLAE_H

#include <exception>
#include <string>
#include <type_traits>
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
template <typename T>
class SLAE {
	static_assert(std::is_arithmetic_v<T>, "Template argument T must be arithmetic");
	using value_type = T;
private:
	Mat2D<T> matrix_;
	VecND<T> free_coef_;
public:
	SLAE(Mat2D<T> const& matrix, VecND<T> const& free_coef) : matrix_(matrix), free_coef_(free_coef) {
		if (!matrix_.is_squared() || matrix_.cols() != free_coef_.size()) {
			throw SizeException();
		}
	}
	VecND<T> solve() const {
		double det = matrix_.det();
		if (det == 0) {
			throw ZeroDeterminantException();
		}
		VecND<T> sol(free_coef_.size());
		for (size_t i = 0; i < sol.size(); ++i) {
			sol[i] = matrix_.replace_col(i, free_coef_).det() / det;
		}
		return sol;
	}
};

#endif
