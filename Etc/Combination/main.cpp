#include <iostream>
#include <vector>

// 순열 함수로도 구현가능하나 보다 효율적인 조합 함수를 따로 구현해봄

template <typename T>
void _comb(std::vector<std::vector<T>>& ret, std::vector<T>& elem, const std::vector<T>& list, int i, int r)
{
	if (r == 0)
		ret.push_back(elem);
	else
	{
		for (int j = i; j < list.size() - r + 1; j++)
		{
			elem.push_back(list[j]);
			_comb(ret, elem, list, j + 1, r - 1);
			elem.pop_back();
		}
	}
}

template <typename T>
std::vector<std::vector<T>> Combination(const std::vector<T>& list, int r)
{
	std::vector<std::vector<T>> ret;
	std::vector<T> elem(r);
	_comb(ret, elem, list, 0, r);
	return ret;
}

int main()
{
	std::vector<char> arr{ 'a', 'b', 'c', 'd', 'e'};
	auto ret = Combination(arr, 4);

	for (auto& r : ret)
	{
		for (auto& c : r)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	
	return 0;
}