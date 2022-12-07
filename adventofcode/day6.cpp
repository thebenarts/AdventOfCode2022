#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int part1()
{
	std::ifstream input("d6.txt");
	std::string line;
	std::getline(input, line);
	int map[26];
	memset(map, 0, 26 * sizeof(int));
	for (int i = 0, j = 3; j < line.size(); i++, j++)
	{
		map[line[i] - 'a']++;
		map[line[i + 1] - 'a']++;
		map[line[j - 1] - 'a']++;
		map[line[j] - 'a']++;

		if (map[line[i] - 'a'] <= 1 && map[line[i + 1] - 'a'] <= 1 && map[line[j - 1] - 'a'] <= 1 && map[line[j] - 'a'] <= 1)
		{
			std::cout << line[i] << line[i + 1] << line[j - 1] << line[j] << '\n';
			std::cout << j + 1 << std::endl;
			return j + 1;
		}
		memset(map, 0, 26 * sizeof(int));
	}
	return -1;
}
int main()
{
	std::ifstream input("d6.txt");
	std::string line;
	std::getline(input, line);
	int map[26];
	memset(map, 0, 26 * sizeof(int));
	for (int i = 13; i < line.size(); i++)
	{
		int j = i - 13;
		while (j < i)
		{
			map[line[j] - 'a']++;
			j++;
		}
		map[line[i] - 'a']++;

		bool bReset = false;
		for (int k = 0; k != 26; k++)
		{
			if (map[k] > 1)
			{ 
				bReset = true;
				break;
			}
		}

		if (bReset)
		{
		memset(map, 0, 26 * sizeof(int));
		}
		else
		{
			std::cout << i + 1 << std::endl;
			break;
		}
	}

	return 0;
}