#include <iostream>
#include "mat2d.h"
#include "slae.h"

int main() {
	Mat2D m(3, 4, 1);
	std::cout << m << std::endl;
	//std::cin >> m;
	//std::cout << m << std::endl;
	Mat2D m2 = { {2, 2, 3, 4, 5}, {4, 5, 6, 9, 1}, {7, 8, 9, 5, 1}, {0, 1, 2, 3, -1000}, {9, 8, 2, 5, 1} };
	std::cout << m2 << std::endl;
	std::cout << m2.transposed() << std::endl;
	std::cout << m2.det() << std::endl;
	{
		Mat2D a = { {3, -1, 2}, {4, 2, 0}, {-5, 6, 1} };
		Mat2D b = { {8, 1}, {7, 2}, {2, -3} };
		Mat2D c = a * b;
		std::cout << c << std::endl;
	}
	{
		Mat2D a = { {1, 2, 3}, {4, 5, 6} };
		Mat2D b = { {-1, -2, -3}, {-4, -5, -6} };
		Mat2D c = a + b;
		std::cout << c << std::endl;
	}
	{
		Mat2D a = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
		VecND b = { 1, 2, 3};
		Mat2D c = a * b;
		std::cout << c << std::endl;
	}
	{
		Mat2D a = { {5, 1, -1}, {9, 3, 4}, {7, -7, 1} };
		VecND free_coef = { 1, 6, 9 };
		SLAE system(a, free_coef);
		VecND solutions = system.solve();
		std::cout << solutions << std::endl;
	}
	return 0;
}