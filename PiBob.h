#pragma once
#include "Block.h"
#include "Party.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <cstdlib>

class PiBob
{
public:
	PiBob();
	static int* piTR;
	static void generateTrans();
	static int piRand(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine);
	static int Pi(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block &temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine);
	~PiBob();
};

