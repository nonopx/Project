#include <iostream>
using namespace std;
#include "PiAlice.h"

int* PiAlice::piTR = new int[5 * ((n / 32) + 1)];

PiAlice::PiAlice()
{
	
}

 int PiAlice::Pi(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine)
{
	 int test = 2;
	 //random Pi
	 if (test == 1)
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
	

	
	// all zero Pi
	 if (test==2)
		return 0;

	// all one Pi
	 if (test == 3)
		return 1; 
	
	 if (test == 4)
	 {
		 if (0 == tr[0] && 0 == temp_p_1S.getIndex() && 0 == temp_newS.getIndex())	// initial case
		 {
			 return 1;
		 }
		 else if (temp_newS.getBlock() == temp_p_1S.getBlock() && temp_newS.getIndex() == 1 && temp_p_1S.getIndex() == 1 && tr[0] == 0 && temp_newS.getBlock()[0] == 1)	// second round
		 {
			 return 1;
		 }
		 else if (temp_newS.getIndex() >= 2)	// we're processing temp_new block
		 {
			 if (temp_newS.getBlock()[temp_newS.getIndex() - 1] == 1 && temp_newS.getBlock()[temp_newS.getIndex() - 2] == 1)
			 {
				 return 0;
			 }
			 if (temp_newS.getBlock()[temp_newS.getIndex() - 1] == 1 && temp_newS.getBlock()[temp_newS.getIndex() - 2] == 0)
			 {
				 return 1;
			 }
			 if (temp_newS.getBlock()[temp_newS.getIndex() - 1] == 0 && temp_newS.getBlock()[temp_newS.getIndex() - 2] == 1)
			 {
				 return 1;
			 }
			 if (temp_newS.getBlock()[temp_newS.getIndex() - 1] == 0 && temp_newS.getBlock()[temp_newS.getIndex() - 2] == 0)
			 {
				 return 0;	// does not matter - arbitrary value
			 }
		 }
		 else if (temp_newS.getIndex() == 1)	// take one bit from temp_new and one from temp_p_1
		 {
			 if (temp_newS.getBlock() == temp_p_1S.getBlock())	// they are the same block
			 {
				 int bit = (tr[indexresultTS]) / (pow(2, indexTS - 1));
				 bit = bit % 2;
				 return bit^temp_newS.getBlock()[0];
			 }
			 else
			 {
				 return 1 - temp_p_1S.getBlock()[temp_p_1S.getIndex() - 1] * temp_newS.getBlock()[0];
			 }
		 }
		 else
		 {
			 if (temp_newS.getBlock() == temp_p_1S.getBlock())
			 {
				 int bit = (tr[indexresultTS]) / (pow(2, indexTS - 1));
				 bit = bit % 2;
				 int bit2 = (tr[indexresultTS]) / (pow(2, indexTS - 2));
				 bit2 = bit2 % 2;
				 return bit^bit2;
			 }
			 else
			 {
				 return  1 - (temp_p_1S.getBlock()[temp_p_1S.getIndex() - 1] * temp_p_1S.getBlock()[temp_p_1S.getIndex() - 2]);
			 }
		 }
		 return 0;
	 }



	
}

 int PiAlice::piRand(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine)
 {
	 int countBits = 0;
	 if (temp_newS.getBlock() != temp_p_1S.getBlock())	// they are not the same block
		 countBits = indexresultTS * 32 + indexTS + temp_p_1S.getIndex() + temp_newS.getIndex() - countones;
	 else
		 countBits = indexresultTS * 32 + indexTS + temp_p_1S.getIndex() - countones;
	 if (countBits < 0)
	 	int x = 1;
	 int specTR = countBits / 32;
	 int specBit = ( countBits) % 32;
	 unsigned int ret = randmine / pow(2, specBit);
	 ret = ret % 2;
	 return ret;
	 
 }


PiAlice::~PiAlice()
{
}


void PiAlice::generateTrans()
{
	int arr[31];

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
