#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// A Rock
// B Paper
// C Scissors
// 
// X Rock			1
// Y Paper			2
// Z Scissors		3

// LOSE 0
// DRAW 3
// WIN	6
unsigned int rpsCompare(const std::string& a, const std::string& b)
{
	unsigned int score{};
	if (b == "X")
	{
		score += 1;
		if (a == "A")
		{
			score += 3;
		}
		else if (a == "C")
		{
			score += 6;
		}
	}
	else if (b == "Y")
	{
		score += 2;
		if (a == "A")
		{
			score += 6;
		}
		else if (a == "B")
		{
			score += 3;
		}
	}
	else if(b == "Z")
	{
		score += 3;
		if (a == "B")
		{
			score += 6;
		}
		else if (a == "C")
		{
			score += 3;
		}
	}

	return score;
}

// A Rock
// B Paper
// C Scissors
// 
// X	need to lose
// Y	need to draw
// Z	need to win

// LOSE 0
// DRAW 3
// WIN	6
unsigned int part2(const std::string& a, const std::string& b)
{
	unsigned int score{};
	if (b == "X")
	{
		if (a == "A")
		{
			score += 3;
		}
		else if (a == "B")
		{
			score += 1;
		}
		else if (a == "C")
		{
			score += 2;
		}
	}
	else if (b == "Y")
	{
		score += 3;
		if (a == "A")
		{
			score += 1;
		}
		else if (a == "B")
		{
			score += 2;
		}
		else if (a == "C")
		{
			score += 3;
		}
	}
	else if(b == "Z")
	{
		score += 6;
		if (a == "A")
		{
			score += 2;
		}
		else if (a == "B")
		{
			score += 3;
		}
		else if (a == "C")
		{
			score += 1;
		}
	}

	return score;
}

int main()
{
	std::ifstream input("d2p1.txt");
	unsigned int score{};

	std::string line;
	while (std::getline(input, line))
	{
		std::string opponent;
		std::string me;
		std::stringstream stream(line);
		stream >> opponent;
		stream >> me;
		score += part2(opponent, me);
	}

	std::cout << score << std::endl;
	return 0;
}