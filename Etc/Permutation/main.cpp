#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/*
* 순열 함수 원리
* 들어온 벡터에서 k 번째 요소를 기준으로
* m 번째 요소까지 swap 하며 재귀 호출
* 위치를 바꾸고 남은 요소들의 순열을 재귀적으로 구하는 형태
* 
* 중복되는 원소가 있는 집합의 순열은 map, set 등을 활용함
* 이를 응용해 조합도 구할 수 있음
* (t, t, f, f) 를 순열을 구한뒤, t 인 인덱스의 원소들의 집합이 조합의 집합들이 됨
* 
* * bool 타입은 swap이 표준에 없음. 
*/

template <typename T>
void Permutations(std::set<std::vector<T>>& ret, std::vector<T>& vec, const int start_k, const int k, const int m)
{
	if (k == m)
	{
		std::vector<T> v(m - start_k + 1);
		std::copy(vec.begin() + start_k, vec.end(), v.begin()); // std::back_inserter(v) 도 가능
		ret.insert(v);
	}
	else
	{
		for (int i = k; i <= m; i++)
		{
			std::swap(vec[i], vec[k]);
			Permutations(ret, vec, start_k, k + 1, m);
			std::swap(vec[i], vec[k]);
		}
	}
}

template <typename T>
std::vector<std::vector<T>> Permutations(std::vector<T>& vec, const int k, const int m)
{
	// 유틸 함수, 순열 값을 벡터로 받기 위함
	std::vector<std::vector<T>> ret;

	// 순열함수가 set에 순열들을 담도록 해 중복 방지
	std::set<std::vector<T>> s_ret;
	Permutations(s_ret, vec, k, k, m);

	std::copy(s_ret.rbegin(), s_ret.rend(), std::back_inserter(ret));
	return ret;
}

template<typename T>
std::vector<std::vector<T>> Combinations(std::vector<T>& vec, const int r)
{

	std::vector<std::vector<T>> ret;

	std::vector<int> b_vec(vec.size());
	std::fill(b_vec.begin(), b_vec.end(), false);
	for (int i = 0; i < r; i++)
		b_vec[i] = true;

	// Permutations 함수 응용
	auto b_permus = Permutations(b_vec, 0, b_vec.size() - 1);

	for (auto const& b_permu : b_permus)
	{
		std::vector<T> comb;
		for (int i = 0; i < b_permu.size(); i++)
		{
			if (b_permu[i] == true)
				comb.push_back(vec[i]);
		}
		ret.push_back(std::move(comb));
	}

	//// STL prev_permutation 응용
	//do
	//{
	//	std::vector<T> comb;
	//	for (int i = 0; i < b_vec.size(); i++)
	//	{
	//		if (b_vec[i] == true)
	//			comb.push_back(vec[i]);
	//	}
	//	ret.push_back(std::move(comb));
	//} while (std::prev_permutation(b_vec.begin(), b_vec.end()));

	return ret;
}

int main()
{
	std::vector<int> vec = { 1,2,3,4,5 };
	//auto vecs = Permutations(vec, 0, vec.size() - 1);
	auto vecs = Combinations(vec, 3);

	for (auto const& vec : vecs)
	{
		for (auto const& e : vec)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	}

	// swap test

	/*std::vector<bool> vec = { true, true };
	vec.swap(vec[0], vec[1]);*/


	return 0;
}