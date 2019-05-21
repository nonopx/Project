#include "PiRand.h"
#include <math.h>
#include <iostream>
using namespace std;

PiRand::PiRand(int size)
{
	piTR = new int[5 * ((size / 32) + 1)];
}


PiRand::~PiRand()
{
}

void PiRand::generateTrans(int size)
{
	int arr[31];
	int n = size;
	for (int i = 0; i < 5 * ((n / 32) + 1); i++)
	{
		piTR[i] = 0;
	}

	for (int j = 0; j < 5 * ((n / 32) + 1); j++)
	{
		for (int i = 0; i < 31; i++)
		{
			arr[i] = std::rand() % 2;
			piTR[j] += arr[i] * pow(2, i);
		}
	}
}

int PiRand::getNextBit(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine)
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
	int ret = piTR[specTR] / pow(2, specBit);
	return ret % 2;
}
