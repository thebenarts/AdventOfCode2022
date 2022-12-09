#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
// have positions on t and h and store the pos pair in a set which will indicate visited tiles
#define N_TAILS 10
//struct pair_hash
//{
//	template <class T1, class T2>
//	std::size_t operator() (std::pair<T1, T2> const& pair)const
//	{
//		std::size_t h1 = std::hash<T1>()(pair.first);
//		std::size_t h2 = std::hash<T2>()(pair.second);
//
//		return h1 ^ h2;		// this hash function worked for me, but there may be some collisions
//							// should think of a new one
//	}
//};

namespace std
{
	template<typename X, typename Y>
	struct hash<std::pair<X, Y>>
	{
		std::size_t operator()(const std::pair<X, Y>& pair) const
		{
			uintmax_t hash = std::hash<X>()(pair.first);
			hash <<= sizeof(uintmax_t) * 4;
			hash ^= std::hash<Y>()(pair.second);
			return std::hash<uintmax_t>()(hash);
		}
	};
}
static std::unordered_set<std::pair<int, int>> visited;
static std::vector<std::vector<int>> movement{ {1,0},{-1,0},{0,-1},{0,1} };
int GetDirection(const char& dir)
{
	switch (dir)
	{
	case 'U': 
		return 0;
		break;
	case 'D':
		return 1;
		break;
	case 'L':
		return 2;
		break;
	case 'R':
		return 3;
		break;
	default:
		break;
	}
	return 0;
}
int GetAmount(const std::string& num)
{
	int result = 0;
	for (int i = 0; i != num.size(); i++)
	{
		result *= 10;
		result += num[i] & 0x0F;
	}

	return result;
}

struct object
{
	object() : x(0), y(0) {}
	void RegisterLocation() { visited.insert({ y,x }); };
	void move(int dir) { y += movement[dir][0]; x += movement[dir][1]; }
	int x;		// horizontal movement L,R
	int y;		// vertical movement U,D
};

struct tail : public object
{
	bool check(object* h);
	void moveTail(object* h);
};

bool tail::check(object* h)
{
	int dY = std::abs(h->y - y);
	int dX = std::abs(h->x - x); 

	if (dX > 1 || dY > 1)
		return true;

	return false;
}

void tail::moveTail(object* h)
{
	if (check(h))
	{
		int yMove = h->y - y;
		int xMove = h->x - x;

		if (yMove != 0)
		{
			if (yMove > 0)
				y += 1;
			else
				y -= 1;
		}
		if (xMove != 0)
		{
			if (xMove > 0)
				x += 1;
			else
				x -= 1;
		}
	}
}

int main()
{
	std::ifstream input("d9.txt");
	std::string line;
	std::stringstream stream;
	char cDirection = ' ';
	std::string digits;
	int direction = 0;
	int amount = 0;
	std::vector<tail*> tails;
	for (int i = 0; i != N_TAILS; i++)
	{
		tails.push_back(new tail());
	}
	tails.back()->RegisterLocation();
	while (std::getline(input, line))
	{
		stream.str(line);
		stream >> cDirection;	// read direction into word
		// decypher direction
		direction = GetDirection(cDirection);
		
		//get the amount we need to move
		stream >> digits;
		amount = GetAmount(digits);

		for (int i = 0; i < amount; i++)
		{
			// move the head
			tails[0]->move(direction);
			// check if we need to move tail
			for (int j = 1; j != N_TAILS; j++)
			{
				tails[j]->moveTail(tails[(int)j - 1]);
			}
			tails.back()->RegisterLocation();
		}
		stream.clear();
	}

	std::cout << visited.size();

	return 0;
}

int part1()
{
	std::ifstream input("d9.txt");
	std::string line;
	std::stringstream stream;
	char cDirection = ' ';
	std::string digits;
	int direction = 0;
	int amount = 0;
	tail* t = new tail();
	object* h = new object();
	t->RegisterLocation();
	while (std::getline(input, line))
	{
		stream.str(line);
		stream >> cDirection;	// read direction into word
		// decypher direction
		direction = GetDirection(cDirection);
		
		//get the amount we need to move
		stream >> digits;
		amount = GetAmount(digits);

		for (int i = 0; i < amount; i++)
		{
			h->move(direction);
			// check if we need to move tail
			if (t->check(h))
			{
				int yMove = h->y - t->y;
				int xMove = h->x - t->x;

				if (yMove != 0)
				{
					if (yMove > 0)
						t->y += 1;
					else
						t->y -= 1;
				}
				if (xMove != 0)
				{
					if (xMove > 0)
						t->x += 1;
					else
						t->x -= 1;
				}
			}
			t->RegisterLocation();
		}
		stream.clear();
	}

	std::cout << visited.size();
	return (int)visited.size();
}