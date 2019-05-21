#include "Pi.h"
#include <math.h>
#include <iostream>
using namespace std;


Pi::Pi()
{
}


Pi::~Pi()
{
}

int Pi::sendSeed(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine)
{
	int countBits = 0;
	if (temp_newS.getBlock() != temp_p_1S.getBlock())	// they are not the same block
		countBits = indexresultTS * 32 + indexTS + temp_p_1S.getIndex() + temp_newS.getIndex() - countones;
	else
		countBits = indexresultTS * 32 + indexTS + temp_p_1S.getIndex() - countones;
	if (countBits < 0)
		int x = 1;
	int specTR = countBits / 32;
	int specBit = (countBits) % 32;
	unsigned int ret = randmine / pow(2, specBit);
	ret = ret % 2;
	return ret;

}
void Pi::generateTrans(int size)
{
}
