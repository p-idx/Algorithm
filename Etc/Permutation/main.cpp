#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/*
* ���� �Լ� ����
* ���� ���Ϳ��� k ��° ��Ҹ� ��������
* m ��° ��ұ��� swap �ϸ� ��� ȣ��
* ��ġ�� �ٲٰ� ���� ��ҵ��� ������ ��������� ���ϴ� ����
* 
* �ߺ��Ǵ� ���Ұ� �ִ� ������ ������ map, set ���� Ȱ����
* �̸� ������ ���յ� ���� �� ����
* (t, t, f, f) �� ������ ���ѵ�, t �� �ε����� ���ҵ��� ������ ������ ���յ��� ��
* 
* * bool Ÿ���� swap�� ǥ�ؿ� ����. 
*/

template <typename T>
void Permutations(std::set<std::vector<T>>& ret, std::vector<T>& vec, const int start_k, const int k, const int m)
{
	if (k == m)
	{
		std::vector<T> v(m - start_k + 1);
		std::copy(vec.begin() + start_k, vec.end(), v.begin()); // std::back_inserter(v) �� ����
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
	// ��ƿ �Լ�, ���� ���� ���ͷ� �ޱ� ����
	std::vector<std::vector<T>> ret;

	// �����Լ��� set�� �������� �㵵�� �� �ߺ� ����
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

	// Permutations �Լ� ����
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

	//// STL prev_permutation ����
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