#include <iostream>
#include "mat2d.h"
#include "slae.h"
#include "dyn_array.h"

#define TASK_1

#ifdef TASK_1
void solve() {
	DynArray<double> arr;
	arr.append(1.0);
	for (size_t i = 0; i < 15; i++) {
		arr.append(i + 0.0);
	}
	std::cout << arr << std::endl;
	DynArray<double> arr2 = { 1, 3, 5, 7, 11, 13 };
	arr += arr2;
	std::cout << arr << std::endl;
	std::cout << arr + arr2 << std::endl;
	arr = arr2;
	std::cout << arr << std::endl;
	std::cout << (arr <<= 2) << std::endl;
	std::cout << (arr >>= 2) << std::endl;
	std::cout << (arr << 3) << std::endl << (arr >> 3) << std::endl;
	std::cout << (arr <<= -2) << std::endl;
	std::cout << (arr >>= -2) << std::endl;
	std::cout << (arr << -4) << std::endl << (arr >> -4) << std::endl;
}
#endif
#ifdef TASK_2
void solve() {
	Mat2D<double> m(3, 4, 1);
	std::cout << m << std::endl;
	//std::cin >> m;
	//std::cout << m << std::endl;
	Mat2D<double> m2 = { {2, 2, 3, 4, 5}, {4, 5, 6, 9, 1}, {7, 8, 9, 5, 1}, {0, 1, 2, 3, -1000}, {9, 8, 2, 5, 1} };
	std::cout << m2 << std::endl;
	std::cout << m2.transposed() << std::endl;
	std::cout << m2.det() << std::endl;
	{
		Mat2D<double> a = { {3, -1, 2}, {4, 2, 0}, {-5, 6, 1} };
		Mat2D<double> b = { {8, 1}, {7, 2}, {2, -3} };
		Mat2D<double> c = a * b;
		std::cout << c << std::endl;
	}
	{
		Mat2D<double> a = { {1, 2, 3}, {4, 5, 6} };
		Mat2D<double> b = { {-1, -2, -3}, {-4, -5, -6} };
		Mat2D<double> c = a + b;
		std::cout << c << std::endl;
	}
	{
		Mat2D<double> a = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
		VecND<double> b = { 1, 2, 3};
		Mat2D<double> c = a * b;
		std::cout << c << std::endl;
	}
	{
		Mat2D<double> a = { {5, 1, -1}, {9, 3, 4}, {7, -7, 1} };
		VecND<double> free_coef = { 1, 6, 9 };
		SLAE<double> system(a, free_coef);
		VecND<double> solutions = system.solve();
		std::cout << solutions << std::endl;
	}
}
#endif

int main() {
	solve();
	return 0;
}
