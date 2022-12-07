#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
int main()
{
	std::ifstream input("d1p1Input.txt");
	std::vector<std::vector<int>> data;
	data.push_back({});

	while (input.good())
	{
		std::string line;
		std::getline(input, line);
		if (line == "")
		{
		data.push_back({});
		continue;
		}
		int num = std::stoi(line);
		data.back().push_back(num);
	}

	int ElfID = 0;
	int calories = 0;
	std::priority_queue<int>pq;
	for (int i = 0; i != data.size(); i++)
	{
		int currentCal = 0;
		for (int j = 0; j != data[i].size(); j++)
		{
			currentCal += data[i][j];
		}
		
		pq.push(currentCal);
	}
	
	calories = 0;
	for (int i = 0; i != 3; i++)
	{
		calories += pq.top();
		pq.pop();
	}

	std::cout << calories;
	return 0;
}















































