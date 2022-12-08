#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


// I AM SO SORRY FOR THIS HUGE MESS.
// I was just trying some new stuff out and didn't have my morning coffee just yet.
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


std::vector<std::vector<int>> movement{ {-1,0},{1,0},{0,-1},{0,1} };
bool boundCheck(const int& direction, const int& row, const int& col, const int& rowEnd, const int& colEnd)
{
	if (direction == UP)
	{
		if (row >= 0)
			return true;
	}
	else if (direction == DOWN)
	{
		if (row < rowEnd)
			return true;
	}
	else if (direction == LEFT)
	{
		if (col >= 0)
			return true;
	}
	else
	{
		if (col < colEnd)
		{
			return true;
		}
	}

	return false;
}
bool helper(std::vector<std::vector<int>>& data, int row, int col, int direction)
{
	// if it's out of bounds
	if (row < 0 || row >= data.size() || col < 0 || col >= data[row].size())
		return 0;
	
	bool (*cBound)(const int& dir, const int& rowI, const int& colI, const int& rowE, const int& colE) = boundCheck;
	int val = data[row][col];

	int rowE = data.size();
	int colE = data[row].size();

	row += movement[direction][0];
	col += movement[direction][1];
	while (cBound(direction, row, col, rowE, colE))
	{
		if (data[row][col] >= val)
		{
			return true;
		}

		row += movement[direction][0];
		col += movement[direction][1];
	}
	
	return false;
}

// we are counting the number of trees that are NOT visible from the outside grid
bool check(std::vector<std::vector<int>>& data, int row, int col)
{
	// if it's on the edge we already know that it's going to be visible from outside the grid
	if (row == 0 || row == data.size() - 1 || col == 0 || col == data[row].size() - 1)
		return 0;
	
	return helper(data, row , col, UP) 
		&& helper(data, row , col, DOWN)
		&& helper(data, row, col, LEFT) 
		&& helper(data, row, col, RIGHT);

}

bool p2Bound(std::vector<std::vector<int>>& data, const int& row, const int& col, const int& direction)
{
	if (direction == UP)
	{
		if (row >= 0)
			return true;
	}
	else if (direction == DOWN)
	{
		if (row < data.size())
			return true;
	}
	else if (direction == LEFT)
	{
		if (col >= 0)
			return true;
	}
	else
	{
		if (col < data[row].size())
		{
			return true;
		}
	}

	return false;
}

int p2helper(std::vector<std::vector<int>>& data, int row, int col, int direction)
{
	int val = data[row][col];
	row += movement[direction][0];
	col += movement[direction][1];
	
	int result = 0;
	while (p2Bound(data, row, col, direction))
	{
		result++;
		if (val <= data[row][col])
		{
			break;
		}
		row += movement[direction][0];
		col += movement[direction][1];
	}

	return result;
}

int p2check(std::vector<std::vector<int>>& data, int row, int col)
{
	// the tree is on the edge the scenic score will be 0 since we would multiply anyways
	if (row == 0 || row == data.size() - 1 || col == 0 || col == data[row].size() - 1)
		return 0;

	return p2helper(data, row , col, UP) 
		 * p2helper(data, row , col, DOWN)
		 * p2helper(data, row, col, LEFT) 
		 * p2helper(data, row, col, RIGHT);
}

int main()
{
	std::ifstream input("d8.txt");
	std::vector<std::vector<int>> data;
	std::string line;
	int lineSize = 0;
	while (std::getline(input, line))
	{
		data.push_back({});
		lineSize = line.size();
		for (int i = 0; i < lineSize; i++)
		{
			data.back().push_back((int)line[i] & 0x0F);
		}
	}
	
	int invisTrees = 0;
	int highestScenicScore = 0;
	for (int row = 0; row < data.size(); row++)
	{
		for (int col = 0; col < data[row].size(); col++)
		{
			highestScenicScore = std::max(highestScenicScore, p2check(data, row, col));
			if (check(data, row, col))
			{
				invisTrees++;
			}
		}
	}
	
	int numOfTrees = data.size() * data[0].size();
	std::cout << numOfTrees - invisTrees << '\n';
	std::cout << highestScenicScore;
}
