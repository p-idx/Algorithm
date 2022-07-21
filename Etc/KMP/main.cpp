#include <iostream>
#include <string>
#include <vector>

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