#include "Block.h"

#include <iostream>
int BLOCK_SIZE = 10;
using namespace std;
Block::Block() :k(BLOCK_SIZE)
{
	index = 0;
	block = new int[BLOCK_SIZE];
	flag = false;

}


Block::~Block()
{
	delete block;
}
int Block::isFull()
{
	if (k == index)
		return 1;
	return 0;
}
void Block::fillBlock(int msg)
{
	this->block[index] = msg;
	index++;
}
bool Block::checkIfError()
{
	for (int i = 0; i < this->k; i++)
	{
		if (2 == this->block[i])
		{

			return true;
		}
	}
	return false;
}
bool Block::checkIfAllZero()
{
	for (int i = 0; i < k - 2; i++)
	{
		if (0 != this->block[i] && 5 != this->block[i])
		{
			return false;
		}
	}
	return true;
}
bool Block::checkIfk3Zero()
{
	for (int i = 0; i < k - 3; i++)
	{
		if (0 != this->block[i] && 5 != this->block[i])
		{
			return false;
		}
	}
	return true;
}

void Block::resetBlock()
{
	for (int i = 0; i < k; i++)
	{
		this->block[i] = 5;
	}
	this->index = 0;
}



int* Block::getBlock()
{
	return this->block;
}

int Block::getIndex()
{
	return this->index;
}

void Block::setIndex(int i)
{
	this->index = i;
}
