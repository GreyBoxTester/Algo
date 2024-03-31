#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

template<typename T>
class Mat2D
{
public:
	Mat2D() = default;
	Mat2D(size_t n) { resize(n); }
	Mat2D(size_t n, const T& val) { resize(n, val); }
	void resize(size_t sz) { m.resize(sz * sz); this->sz = sz; }
	void resize(size_t sz, const T& val) { m.resize(sz * sz, val); this->sz = sz; }
	T& at(size_t x, size_t y) { return m[y * sz + x]; }
	size_t size() const { return sz; }
private:
	std::vector<T> m;
	size_t sz = 0;
};

void floydWarshall(Mat2D<i64>& mat)
{
	for (i64 k = 0; k < mat.size(); k++)
	{
		for (i64 i = 0; i < mat.size(); i++)
		{
			for (i64 j = 0; j < mat.size(); j++)
			{
				mat.at(i, j) = std::min(mat.at(i, j), mat.at(i, k) + mat.at(k, j));
			}
		}
	}
}
