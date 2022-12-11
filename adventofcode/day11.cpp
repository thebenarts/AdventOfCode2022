#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

unsigned long long MAGIC_MOD = 0;
struct Monkey;
static std::vector<Monkey*>monkeys;
typedef unsigned long long(*m_op) (unsigned long long, unsigned long long);

unsigned long long op_multiply(unsigned long long wLevel, unsigned long long mLevel)
{
	return wLevel * mLevel;
}

unsigned long long op_add(unsigned long long wLevel, unsigned long long  mLevel)
{
	return wLevel + mLevel;
}

struct Monkey
{
	Monkey(const std::vector<unsigned long long>& items, m_op op, int operationNum, int divisor, int t, int f) : m_inspections(0),
		m_operation(op), 
		m_operation_number(operationNum)
		, m_divisor(divisor)
		, m_true(t)
		, m_false(f)
	{
		m_items = items;
	}

	void ThrowObjects()
	{
		for (auto& item : m_items)
		{
			m_inspections++;
			unsigned long long worry_level = item;
			if (m_operation_number == -1)
			{
				worry_level = m_operation(worry_level, worry_level);
			}
			else
				worry_level = m_operation(worry_level,(unsigned long long) m_operation_number);
			
			worry_level /= 3;
			if (worry_level % m_divisor == 0)
				monkeys[m_true]->m_items.push_back(worry_level);
			else
				monkeys[m_false]->m_items.push_back(worry_level);
		}
		m_items.clear();
	}

	void ThrowObjects2()
	{
		for (auto& item : m_items)
		{
			m_inspections++;
			unsigned long long worry_level = item;
			if (m_operation_number == -1)
			{
				worry_level = m_operation(worry_level, worry_level);
			}
			else
				worry_level = m_operation(worry_level, (unsigned long long )m_operation_number);

			worry_level = worry_level % MAGIC_MOD;

			if (worry_level % (unsigned long long)m_divisor == 0)
				monkeys[m_true]->m_items.push_back(worry_level);
			else
				monkeys[m_false]->m_items.push_back(worry_level);
		}
		m_items.clear();
	}

	unsigned long long m_inspections;
	std::vector<unsigned long long> m_items;
	unsigned long long (*m_operation)(unsigned long long, unsigned long long); // fn pointer for operator
	const int m_operation_number;		// the number used for operation
	// if operation number is -1 that means it's supposed to pass in the item twice
	const int m_divisor;
	const int m_true;
	const int m_false;
};

int ReadNumber(const std::string& number)
{
	int result = 0;
	for (int i = 0; i != number.size(); i++)
	{
		if (number[i] == ',')
			break;

		result *= 10;
		result += number[i] & 0x0F;
	}

	return result;
}

void ReadItems(const std::string& line, std::stringstream& stream, std::vector<unsigned long long>& items)
{
	// ignore the first two items
	std::string word;
	stream.str(line);
	stream >> word >> word;		// just read the two unimportant words

	while (stream >> word)
	{
		items.push_back((unsigned long long )ReadNumber(word));
	}
	stream.clear();
}

int ReadOperation(const std::string& line, std::stringstream& stream, m_op& op)
{
	stream.str(line);
	std::string word;
	for (int i = 0; i != 4; i++) // all the useless information
	{
		stream >> word;
	}
	
	stream >> word;
	if (word == "+")
		op = op_add;
	else
		op = op_multiply;

	stream >> word;
	stream.clear();
	if (0x30 <= word[0] && word[0] <= 0x39)
		return ReadNumber(word);
	
	return -1;
}

int ReadOneNumber(const std::string& line, std::stringstream& stream)
{
	stream.str(line);
	std::string word;
	while (stream >> word)
	{
		if (0x30 <= word[0] && word[0] <= 0x39)
			break;
	}
	stream.clear();
	return ReadNumber(word);
}
unsigned long long gcd(unsigned long long a, unsigned long long b)
{
	unsigned long long c = 0;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}
void ReadInput()
{
	std::ifstream input("d11.txt");
	std::stringstream stream;
	std::string line;
	int lN = 0;
	std::vector<unsigned long long> items;
	m_op operation = nullptr;
	int opNum = 0;
	int divisor = 0;
	int t = 0;
	int f = 0;
	unsigned long long mod = 1;
	while (std::getline(input, line))
	{
		switch (lN)
		{
		case 0:
			break;
		case 1:
			ReadItems(line,stream, items);
			break;
		case 2:
			opNum = ReadOperation(line, stream, operation);
			break;
		case 3:
			divisor = ReadOneNumber(line, stream);
			mod = mod / gcd(mod, divisor) * divisor;
			break;
		case 4:
			t = ReadOneNumber(line, stream);
			break;
		case 5:
			f = ReadOneNumber(line, stream);
			monkeys.push_back(new Monkey(items, operation, opNum, divisor, t, f));
			break;
		default:
			lN = -1;
			items.clear();
			break;
		}
		lN++;
	}

	MAGIC_MOD = mod;
}

int part1()
{
	for (int round = 0; round != 20; round++)
	{
		for (Monkey* m : monkeys)
		{
			if (m)
			{
				m->ThrowObjects();
			}
		}
	}

	std::vector<int> inspections;
	for (Monkey* m : monkeys)
	{
		inspections.push_back(m->m_inspections);
	}

	std::sort(inspections.begin(), inspections.end(), [](const int& a, const int& b) {return a > b; });

	return inspections[0] * inspections[1];
}

unsigned long long part2()
{
	for (int round = 1; round <= 10000; round++)
	{
		for (Monkey* m : monkeys)
		{
			if (m)
			{
				m->ThrowObjects2();
			}
		}

		if (round == 1 || round == 20 || round == 1000)
		{
			for (auto m : monkeys)
			{
				std::cout << m->m_inspections << '\n';
			}
			std::cout << std::endl;
		}
	}

	std::vector<unsigned long long> inspections;
	for (Monkey* m : monkeys)
	{
		if (m)
		{
			inspections.push_back(m->m_inspections);
		}
	}

	for (auto& i : inspections)
	{
		std::cout << i << std::endl;
	}

	std::cout << std::endl;
	std::sort(inspections.begin(), inspections.end(), [](const unsigned long long & a, const unsigned long long & b) {return a > b; });

	return inspections[0] * inspections[1];
}

int main()
{
	ReadInput();
	std::cout << part2();
}