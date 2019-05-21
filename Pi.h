#pragma once
#include "Block.h"


class Pi
{
public:
	Pi();
	~Pi();

	virtual int getNextBit(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine)=0;
	int sendSeed(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine);
	virtual void generateTrans(int size);

};

