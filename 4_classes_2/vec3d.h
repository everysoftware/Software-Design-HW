#ifndef VEC3D_H
#define VEC3D_H

#include <iostream>
#include <algorithm>

/*
* a b
* c d
*/
class Matrix22 {
public:
	double a;
	double b;
	double c;
	double d;
	double det() const noexcept {
		return a * d - b * c;
	}
};

class Vec3D;
inline std::ostream& operator<<(std::ostream& os, Vec3D const& rhs) noexcept;

class Vec3D {
public:
	double x = 0;
	double y = 0;
	double z = 0;
	double dot_product(Vec3D const& rhs) const noexcept {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	void swap(Vec3D& rhs) noexcept {
		std::swap(x, rhs.x);
		std::swap(y, rhs.y);
		std::swap(z, rhs.z);
	}
	Vec3D& operator&=(Vec3D const& rhs) noexcept {
		using M = Matrix22;
		auto temp = Vec3D{ M{ y, z, rhs.y, rhs.z }.det(),
			-M{ x, z, rhs.x, rhs.z }.det(),
			M{ x, y, rhs.x, rhs.y }.det() };
		swap(temp);
		return *this;
	}
};
inline std::ostream& operator<<(std::ostream& os, Vec3D const& rhs) noexcept {
	os << "( " << rhs.x << " " << rhs.y << " " << rhs.z << " )";
	return os;
}
inline double operator*(Vec3D const& lhs, Vec3D const& rhs) noexcept {
	return lhs.dot_product(rhs);
}
inline Vec3D operator&(Vec3D lhs, Vec3D const& rhs) noexcept {
	return lhs &= rhs;
}

#endif
