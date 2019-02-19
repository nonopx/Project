#pragma once
#define BLOCK_SIZE 9


class Block
{
public:
	const int k;
	int* block;
	bool flag;
	int index;
	int isFull();
	void fillBlock(int msg);
	void resetFlag();
	bool checkIfAllZero();
	bool checkIfError();
	void addBlock(Block& block);
	void resetBlock();
	void fillZeroBlock();

	Block();
	~Block();
};

