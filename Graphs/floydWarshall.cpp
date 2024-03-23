#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

template<typename T>
class Mat2D
{
public:
	Mat2D() {}
	void resize(int sz) { m.resize((size_t)sz * sz); this->sz = sz; }
	void resize(int sz, const T& val) { m.resize((size_t)sz * sz, val); this->sz = sz; }
	T& at(int x, int y) { return m[(size_t)y * sz + x]; }
	int size() const { return sz; }
private:
	std::vector<T> m;
	int sz = 0;
};

Mat2D<int> mat;

void floydWarshall()
{
	for (int k = 0; k < mat.size(); k++)
	{
		for (int i = 0; i < mat.size(); i++)
		{
			for (int j = 0; j < mat.size(); j++)
			{
				mat.at(i, j) = std::min<int>(mat.at(i, j), std::min<int64_t>((int64_t)mat.at(i, k) + (int64_t)mat.at(k, j), std::numeric_limits<int>::max()));
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
	int n = 0, s = 0, t = 0;
	std::cin >> n >> s >> t;
	s--; t--;
	mat.resize(n, std::numeric_limits<int>::max());
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat.size(); j++)
		{
			int v = 0;
			std::cin >> v;
			if (v == -1) { continue; }
			mat.at(i, j) = v;
		}
	}

	floydWarshall();

	std::cout << (mat.at(s, t) == std::numeric_limits<int>::max() ? -1 : mat.at(s, t));
}
