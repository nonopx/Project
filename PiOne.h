#pragma once
#include "Pi.h"
using namespace std;

class PiOne : public Pi
{
public:
	PiOne();
	~PiOne();

	virtual int getNextBit(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine);

};

