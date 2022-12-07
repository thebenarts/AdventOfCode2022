#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
std::string part1()
{
	std::vector<std::stack<char>> crates;
	std::ifstream input("d5.txt");

	std::string line;
	int index;
	char letter;
	while (std::getline(input, line))
	{
		if (line.empty())
		{
			break;
		}
		std::stringstream stream(line);
		crates.push_back({});
		stream >> index;
		while (stream >> letter)
		{
			crates[index].push(letter);
		}
	}

	std::string commands;
	int cnt;
	int from;
	int to;
	while (std::getline(input, line))
	{
		std::stringstream stream(line);
		stream >> commands;
		stream >> cnt;
		stream >> commands;
		stream >> from;
		stream >> commands;
		stream >> to;
	
		from--;
		to--;
		for (int i = 0; i != cnt; i++)
		{
			if (crates[from].empty())
			{
				break;
			}
			letter = crates[from].top();
			crates[from].pop();
			crates[to].push(letter);
		}

	}

	std::string result;
	for (auto s : crates)
	{
		if (s.empty())
			continue;

		result += s.top();
	}

	return result;
}
int main()
{
	std::vector<std::stack<char>> crates;
	std::ifstream input("d5.txt");

	std::string line;
	int index;
	char letter;
	while (std::getline(input, line))
	{
		if (line.empty())
		{
			break;
		}
		std::stringstream stream(line);
		crates.push_back({});
		stream >> index;
		while (stream >> letter)
		{
			crates[index].push(letter);
		}
	}

	std::string commands;
	int cnt;
	int from;
	int to;
	while (std::getline(input, line))
	{
		std::stringstream stream(line);
		stream >> commands;
		stream >> cnt;
		stream >> commands;
		stream >> from;
		stream >> commands;
		stream >> to;
	
		from--;
		to--;
		std::stack<char> s;
		for (int i = 0; i != cnt; i++)
		{
			if (crates[from].empty())
			{
				break;
			}
			s.push(crates[from].top());
			crates[from].pop();
		}
		while (!s.empty())
		{
			crates[to].push(s.top());
			s.pop();
		}

	}

	std::string result;
	for (auto s : crates)
	{
		if (s.empty())
			continue;

		result += s.top();
	}

	std::cout << result;
	return 0;
}
