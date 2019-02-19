#include "Block.h"

#include <iostream>
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
	if (index == k)
		cout << "error in Block::fillBlock" << endl;
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
void Block::fillZeroBlock()
{
	for (int i = 0; i < k; i++)
	{
		this->block[i] = 5;
	}
}
void Block::resetFlag()
{
	this->flag = false;
}
bool Block::checkIfAllZero()
{
	for (int i = 0; i < k-2  ; i++)
	{
		if (0 != this->block[i] && 5 != this->block[i] && 6 != this->block[i])
		{
			return false;
		}
	}
	return true;
}
void Block::addBlock(Block& blockToAdd)
{
	this->flag = blockToAdd.flag;
	this->index = blockToAdd.index;
	for (int i = 0; i < blockToAdd.k; i++)
	{
		this->block[i] = blockToAdd.block[i];
	}

}
void Block::resetBlock()
{
	for (int i = 0; i < k; i++)
	{
		this->block[i] = 6;
	}
	this->index = 0;
}