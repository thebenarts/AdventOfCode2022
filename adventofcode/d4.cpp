#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
int part1()
{
	std::ifstream input("d4.txt");
	
	int result = 0;
	std::string line;
	int section[4];
	memset(section, 0, sizeof(int) * 4);
	while (std::getline(input, line))
	{
		std::stringstream stream(line);
		int i = 0;
		int j = 0;
		while (i < line.length())
		{
			if (line[i] == '-' || line[i] == ',')
			{
				++j;
				++i;
				continue;
			}
			// when we add a new digit to an already existing number, we have to make space for the digit
			if (section[j] != 0)
			{
				section[j] *= 10;
			}
			section[j] += (int)(line[i] & 0x0F);		// convert character to int
			++i;
		}

		if ((section[0] <= section[2] && section[1] >= section[3]) || (section[2] <= section[0] && section[3] >= section[1]))
		{
			result++;
		}

		memset(section, 0, sizeof(int) * 4);
	}

	return result;
}

int main()
{
	std::ifstream input("d4.txt");
	
	int result = 0;
	std::string line;
	int section[4];
	memset(section, 0, sizeof(int) * 4);
	while (std::getline(input, line))
	{
		std::stringstream stream(line);
		int i = 0;
		int j = 0;
		while (i < line.length())
		{
			if (line[i] == '-' || line[i] == ',')
			{
				++j;
				++i;
				continue;
			}
			// when we add a new digit to an already existing number, we have to make space for the digit
			if (section[j] != 0)
			{
				section[j] *= 10;
			}
			section[j] += (int)(line[i] & 0x0F);		// convert character to int
			++i;
		}

		if ((section[0] <= section[2] && (section[1]>=section[2] || section[0] == section [2])) || (section[2]<=section[0] && (section[3] >= section[0] || section[2] == section[0])))
		{
			result++;
		}

		memset(section, 0, sizeof(int) * 4);
	}

	std::cout << result << std::endl;
	return 0;
}