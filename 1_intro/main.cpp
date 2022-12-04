#include <iostream>
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <algorithm>

#define TASK_6

#ifdef TASK_1
int fact(int x) {
	if (x == 0) {
		return 1;
	}
	return x * fact(x - 1);
}
void solve() {
	int x;
	std::cin >> x;
	std::cout << fact(x);
}
#endif
#ifdef TASK_2
void solve() {
	double a, b, c;
	std::cin >> a >> b >> c;
	double det = b * b - 4 * a * c;
	double x1 = (-b + sqrt(det)) / (2 * a);
	double x2 = (-b - sqrt(det)) / (2 * a);
	if (det > 0) {
		std::cout << "Two real solutions:" << std::endl << x1 << std::endl << x2 << std::endl;
	}
	else if (det == 0) {
		std::cout << "One real solution:" << std::endl << x1 << std::endl;
	}
	else {
		std::cout << "No real solutions";
	}
}
#endif
#ifdef TASK_3
bool isPrime(int x) {
	if (x < 2) {
		return false;
	}
	for (int d = 2; d < int(sqrt(x)) + 1; ++d) {
		if (x % d == 0) {
			return false;
		}
	}
	return true;
}
// Решето Эратосфена
void getPrimes2(int startNumber, int endNumber, std::set <int>& buffer) {
	std::map <int, bool> numbers;
	numbers[1] = false;
	for (int i = 2; i <= endNumber; ++i) {
		numbers[i] = true;
	}
	int x = 2;
	int checked = 1; // 1
	while (checked < endNumber) {
		if (numbers[x]) {
			for (int i = 2 * x; i <= endNumber; i += x) {
				if (numbers[i]) {
					numbers[i] = false;
					checked += 1;
				}
			}
		}
		checked += 1;
		x += 1;
	}
	for (int i = startNumber; i <= endNumber; ++i) {
		if (numbers[i]) {
			buffer.insert(i);
		}
	}
}
// Оптимизированная версия
void getPrimes(int startNumber, int endNumber, std::set <int>& buffer) {
	if (startNumber < 0 or endNumber < 2 or endNumber - startNumber <= 0) {
		return;
	}
	std::map <int, bool> numbers;
	// Делаем границы нечётными
	startNumber -= startNumber % 2 == 0;
	endNumber -= endNumber % 2 == 0;
	// Поскольку все простые числа, кроме 2, нечётные, то размер словаря можно сократить вдвое
	numbers[2] = true;
	buffer.insert(2);
	for (int i = 3; i <= endNumber; i += 2) {
		numbers[i] = true;
	}
	int x = 3;
	while (x * x <= endNumber) {
		if (numbers[x]) {
			/*
			На самом деле можем начинать вычёркивать с x ** 2, а не с 2 * x,
			так как числа меньшие x * x обязательно имеют простой делитель, меньший x
			(они уже были вычеркнуты)
			По этой же причине останавливать алгоритм можно когда x ** 2 станет больше кон. границы
			*/
			for (int i = x * x; i <= endNumber; i += 2 * x) {
				if (numbers[i]) {
					numbers[i] = false;
				}
			}
		}
		x += 2;
	}
	for (int i = startNumber; i <= endNumber; i += 2) {
		if (numbers[i]) {
			buffer.insert(i);
		}
	}
}
void solve() {
	int a, b;
	std::cout << "Enter start and end boundaries: ";
	std::cin >> a >> b;
	std::set <int> primes;
	getPrimes(a, b, primes);
	std::cout << "Prime numbers (" << primes.size() << "): " << std::endl;
	for (auto x : primes) {
		std::cout << x << " ";
	}
}
#endif
#ifdef TASK_4
std::string switchBase(int x, int newBase) {
	std::string ans = "";
	while (x != 0) {
		ans += '0' + x % newBase;
		x /= newBase;
	}
	std::reverse(ans.begin(), ans.end());
	return ans;
}
void solve()
{
	int x, n;
	std::cin >> x >> n;
	std::cout << switchBase(x, n) << std::endl;
}
#endif
#ifdef TASK_5
void solve() {
	double a, q;
	int e;
	std::cin >> a >> q >> e;
	double s = 0;
	int p = 0;
	while (p <= e) {
		s += pow(q, p);
		p += 2;
	}
	std::cout << a * s;
}
#endif
#ifdef TASK_6
void solve() {
	char c;
	std::cin >> c;
	std::cout << ((c >= 'A' && c <= 'z') ? "Yes" : "No");
}
#endif

int main() {
	solve();
	return 0;
}