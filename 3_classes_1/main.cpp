#include <iostream>

#define TASK_2

#ifdef TASK_1
class DynArray {
public:
	double* arr;
	int size_;
	int maxSize;
	DynArray(int n) {
		this->arr = new double[n];
		this->size_ = 0;
		this->maxSize = n;
	}
	~DynArray() {
		delete[] this->arr;
	}
	void append(double x) {
		if (this->size_ < this->maxSize) {
			this->arr[this->size_++] = x;
			return;
		}
		auto arr = new double[this->maxSize * 2];
		for (int i = 0; i < this->maxSize; ++i) {
			arr[i] = this->arr[i];
		}
		delete[] this->arr;
		this->arr = arr;
		this->maxSize *= 2;
		this->append(x);
	}
	double get(int i) {
		return this->arr[i];
	}
	int size() {
		return this->size_;
	}
};
void solve() {
	DynArray arr(10);
	arr.append(1.0);
	for (size_t i = 0; i < 15; i++) {
		arr.append(i + 0.0);
	}
	for (size_t j = 0; j < arr.size(); j++) {
		std::cout << arr.get(j) << ' ';
	}
	std::cout << std::endl;
}
#endif

#ifdef TASK_2
class MyStack {
public: 
	int size;
	int maxSize;
	int* arr;
	MyStack(int n) {
		this->arr = new int[n];
		this->size = 0;
		this->maxSize = n;
	}
	~MyStack() {
		delete[] this->arr;
	}
	void append(double x) {
		if (this->size < this->maxSize) {
			this->arr[this->size++] = x;
			return;
		}
		auto arr = new int[this->maxSize * 2];
		for (int i = 0; i < this->maxSize; ++i) {
			arr[i] = this->arr[i];
		}
		delete[] this->arr;
		this->arr = arr;
		this->maxSize *= 2;
		this->append(x);
	}
	void pop(int index = -1) {
		if ((index >= 0 && index >= this->size) || (index < 0 && index > this->size)) {
			std::cout << "Index out of range" << std::endl;
			return;
		}
		index = (this->size + index) % this->size;
		for (int i = index + 1; i < this->size; ++i) {
			std::swap(this->arr[i], this->arr[i - 1]);
		}
		--this->size;
	}
	int get(int index) {
		return this->arr[(this->size + index) % this->size];
	}
	int find(int x) {
		for (int i = 0; i < this->size; ++i) {
			if (this->arr[i] == x) {
				return i;
			}
		}
		return -1;
	}
	void print() {
		for (int i = 0; i < this->size; ++i) {
			std::cout << this->arr[i] << " ";
		}
		std::cout << std::endl;
	}
	void clear() {
		this->size = 0;
	}
	void reverse() {
		for (int i = 0; i < this->size / 2; ++i) {
			std::swap(this->arr[i], this->arr[this->size - 1 - i]);
		}
	}
	void sort() {
		for (int i = 0; i < this->size; ++i) {
			for (int j = 1; j < this->size; ++j) {
				if (this->arr[j] < this->arr[j - 1]) {
					std::swap(this->arr[j], this->arr[j - 1]);
				}
			}
		}
	}
};
void solve() {
	MyStack arr(10);
	arr.append(1);
	for (int i = 0; i < 15; ++i) {
		arr.append(i);
	}
	arr.print();
	arr.pop();
	arr.print();
	int tests[3] = {0, 1, -2};
	for (auto i : tests) {
		arr.pop(i);
		arr.print();
	}
	std::cout << arr.find(3) << std::endl;
	arr.reverse();
	arr.print();
	arr.sort();
	arr.print();
}
#endif

int main() {
	solve();
	return 0;
}