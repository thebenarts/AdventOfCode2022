#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


static int RegisterX = 1;
static int cycle = 0;
static int result = 0;
int GetNumber(const std::string& word)
{
	int number = 0;
	int i = 0; 
	bool bNegative = false;
	if (word[0] == '-')
	{
		++i;
		bNegative = true;
	}

	while (i < word.size())
	{
		number *= 10;
		number += word[i] & 0x0F;
		++i;
	}

	if (bNegative)
	{
		number = ~number + 1;
	}

	return number;
}

bool checkCycle()
{
	if (cycle == 20)
	{
		return true;
	}

	int wanted = 60;
	while (wanted <= cycle)
	{
		if (cycle == wanted)
			return true;

		wanted += 40;
	}

	return false;
}
void DrawToScreen()
{
	int pos = cycle % 40;
	if (pos == 0)
		std::cout << std::endl;

	if (pos >= RegisterX - 1 && pos <= RegisterX + 1)
		std::cout << '#';
	else
		std::cout << '.';
}
void PerformInstruction(const std::string& line, std::stringstream& stream)
{
	std::string word;
	stream.str(line);
	int number = 0;
	stream >> word;

	if (word == "addx")
	{
		++cycle;
		DrawToScreen();
		if (checkCycle())
		{
			result += RegisterX * cycle;
		}
		++cycle;
		if (checkCycle())
		{
			result += RegisterX * cycle;
		}
		stream >> word;
		number = GetNumber(word);
		RegisterX += number;
		DrawToScreen();
	}
	else
	{
		++cycle;
		DrawToScreen();
		if (checkCycle())
		{
			result += RegisterX * cycle;
		}
	}
	
	stream.clear();
}

int main()
{
	std::ifstream input("d10.txt");
	std::stringstream stream;
	std::string line;
	int addToRegister = 0;
	DrawToScreen();
	while (std::getline(input, line))
	{
		PerformInstruction(line, stream);
	}

	std::cout << result << std::endl;
	return 0;
}