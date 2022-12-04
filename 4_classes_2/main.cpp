#include <iostream>
#include "vec3d.h"
#include "dyn_array.h"

#define TASK_2

#ifdef TASK_1
void solve() {
	Vec3D vec1{ 1.2, 2.4, 3.6 };
	Vec3D vec2{ -4.8, -5.0, -6.2 };
	std::cout << vec1 << std::endl << vec2 << std::endl;
	std::cout << vec1 * vec2 << std::endl;
	std::cout << (vec1 & vec2) << std::endl;
}
#endif
#ifdef TASK_2
void solve() {
	DynArray arr(10);
	arr.append(1.0);
	for (size_t i = 0; i < 15; i++) {
		arr.append(i + 0.0);
	}
	std::cout << arr << std::endl;
	DynArray arr2 = {1, 3, 5, 7, 11, 13};
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

int main() {
	solve();
	return 0;
}