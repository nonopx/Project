#pragma once
extern int BLOCK_SIZE;


class Block
{
private:
	const int k;
	int* block;
	bool flag;
	int index;

public:
	int isFull();
	void fillBlock(int msg);
	bool checkIfAllZero();
	bool checkIfError();
	bool checkIfk3Zero();
	void resetBlock();
	Block();
	~Block();


	// set's & set's
	int* getBlock();
	int getIndex();
	void setIndex(int i);
};

