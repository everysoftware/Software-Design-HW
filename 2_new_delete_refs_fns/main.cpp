#include <iostream>

#define TASK_3

#ifdef TASK_1
void solve() {
	int n;
	std::cin >> n;
	auto a = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (a[j] > a[j + 1]) {
				std::swap(a[j], a[j + 1]);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << " ";
	}
	delete[] a;
}
#endif
#ifdef TASK_2
template <typename T> void bubbleSort(T& a, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (a[j] > a[j + 1]) {
				std::swap(a[j], a[j + 1]);
			}
		}
	}
}
template <typename T> void solveT(int n) {
	auto a = new T[n];
	std::cout << "Enter sequence: ";
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	bubbleSort(a, n);
	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << " ";
	}
	delete[] a;
}
void solve() {
	int n, type;
	std::cout << "Enter number of elements: ";
	std::cin >> n;
	std::cout << "Select sequence type 1) int 2) short 3) double: ";
	std::cin >> type;
	switch (type) {
	case 1:
		solveT<int>(n);
		break;
	case 2:
		solveT<short>(n);
		break;
	case 3:
		solveT<double>(n);
		break;
	}
}
#endif
#ifdef TASK_3
template <typename T> void bubbleSort(T &a, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (a[j] > a[j + 1]) {
				std::swap(a[j], a[j + 1]);
			}
		}
	}
}
void bubbleSort(char* a, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			// Не-буквы должны быть больше любой буквы, чтобы их поставить в конец
			if (!std::isalpha((unsigned char)a[j])) {
				a[j] = ' ';
				std::swap(a[j], a[j + 1]);
			} else if (std::isalpha((unsigned char)a[j + 1]) && tolower(a[j]) > tolower(a[j + 1])) {
				std::swap(a[j], a[j + 1]);
			}
		}
	}
}
template <typename T> void solveT(int n) {
	auto a = new T[n];
	std::cout << "Enter sequence: ";
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	bubbleSort(a, n);
	std::cout << "Result: ";
	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << " ";
	}
	delete[] a;
}
template<> void solveT<char>(int n) {
	auto a = new char[n];
	std::cout << "Enter sequence: ";
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	bubbleSort(a, n);
	std::cout << "Result: '";
	for (int i = 0; i < n; ++i) {
		std::cout << a[i];
	}
	std::cout << "'";
	delete[] a;
}
void solve() {
	int n, type;
	std::cout << "Enter number of elements: ";
	std::cin >> n;
	std::cout << "[1. int\n2. short\n3. double\n4. char]\nSelect sequence type: ";
	std::cin >> type;
	switch (type) {
	case 1:
		solveT<int>(n);
		break;
	case 2:
		solveT<short>(n);
		break;
	case 3:
		solveT<double>(n);
		break;
	case 4:
		solveT<char>(n);
		break;
	}
}
#endif

int main() {
	solve();
	return 0;
}