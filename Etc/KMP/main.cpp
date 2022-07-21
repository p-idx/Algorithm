#include <iostream>
#include <string>
#include <vector>

/*
* kmp의 핵심
* 
* 1. 본문 문자열에서 후진하지 않는다
* 2. 실패함수는 패턴의 앞뒤로 동일순서 일치하는 부분이 존재하는지 찾는것
* 2-1. 앞뒤의 동일순서는 abcabca 와 같이 abc'a', 'a'bca로 '겹칠' 수 있다
* 
* * 직접 만든 failure2 함수는 플래그변수 사용하며, 매번 비교
* * 만들다보니 pi[i] 는 pi[i-1]을 알면 인덱스 타고 올라가며, 일일이 같은 비교를 할 필요 없다
* * 따라서 교재의 failure1 함수가 효율적
*/

std::vector<int> failure1(const std::string& pat)
{
	std::vector<int> pi(pat.size());
	pi[0] = -1;

	for (int j = 1; j < pat.size(); j++)
	{
		int i = pi[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) 
			i = pi[i];

		if (pat[j] == pat[i + 1])
			pi[j] = i + 1;
		else
			pi[j] = -1;
	}

	return pi;
}

std::vector<int> failure2(const std::string& pat)
{
	std::vector<int> pi(pat.size());
	for (auto& e : pi) e = -1;

	pi[0] = -1;
	bool flag = false;
	for (int j = 1; j < pat.size(); j++)
	{
		int k1 = 0;
		int k2 = 1;
		int cnt = -1;

		while (k2 <= j)
		{
			if (pat[k1] == pat[k2])
			{
				k1++;
				flag = true;
			}
			else
			{
				k1 = 0;
				if (flag)
					k2--;
				flag = false;
			}

			if (flag)
				cnt++;
			else
				cnt = -1;

			k2++;
		}
		pi[j] = cnt;
	}

	return pi;
}

int KMPfind(const std::string& s, const std::string& pat, int index = 0)
{
	auto pi = failure1(pat);

	int posS = 0, posP = 0;

	while ((posS < s.size()) && (posP < pat.size()))
	{
		if (s[posS] == pat[posP])
		{
			posS++;
			posP++;
		}
		else
		{
			if (posP == 0) // first word wrong
				posS++;
			else
				posP = pi[posP - 1] + 1;
		}
	}

	if (posP < pat.size()) 
		return -1;
	else
		return posS - pat.size();

}


int main()
{
	auto pat = std::string("abcabcacab");
	auto pi = failure1(pat);
	for (auto& e : pi)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;

	pi = failure2(pat);
	for (auto& e : pi)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;
	return 0;
}
