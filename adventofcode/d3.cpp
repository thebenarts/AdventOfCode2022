#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define SIZE_OF_MAP 52

int part1()
{
	int map[SIZE_OF_MAP];
	memset(map, 0, sizeof(int) * SIZE_OF_MAP);

	std::ifstream input("d3.txt");
	int score{};
	std::string line;
	while (std::getline(input, line))
	{
		int length = line.length();
		int i = 0;
		while (i < length / 2)
		{
			// handle uppercase
			if (line[i] < 0x61)
			{
				map[line[i] - 'A' + 26]++;
			}
			else
			{
				// handle lowercase
				map[line[i] - 'a']++;
				
			}
			i++;
		}

		while (i < length)
		{
			if (line[i] < 0x61)
			{
				if (map[line[i] - 'A' + 26] >= 1)
				{
					score += (line[i] - 'A') + 26 + 1;
					break;
				}
			}
			else
			{
				// handle lowercase
				if (map[line[i] - 'a'] >= 1)
				{
					score += line[i] - 'a' + 1;
					break;
				}
			}
			i++;
		}


		memset(map, 0, sizeof(int) * SIZE_OF_MAP);
	}

	return score;
}

int main()
{
	int map[SIZE_OF_MAP];
	memset(map, 0, sizeof(int) * SIZE_OF_MAP);

	std::ifstream input("d3.txt");
	int score{};
	std::string line;
	int member = 1;
	while (std::getline(input, line))
	{
		int length = line.length();
		int i = 0;
		while (i < length)
		{
			if (line[i] < 0x61)
			{
				if (map[line[i] - 'A' + 26] == member-1)
				{
					map[line[i] - 'A' + 26]++;
				}
			}
			else
			{
				// handle lowercase
				if (map[line[i] - 'a'] == member-1)
				{
					map[line[i] - 'a']++;
				}
			}
			i++;
		}

		if (member == 3)
		{
			member = 0;
			for (int j = 0; j != SIZE_OF_MAP; j++)
			{
				if (map[j] == 3)
				{
					score += j + 1;
					break;
				}
			}
			memset(map, 0, sizeof(int) * SIZE_OF_MAP);
		}
		member++;
	}

	std::cout << score << std::endl;
	return 0;
}