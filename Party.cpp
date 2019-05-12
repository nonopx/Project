#include <iostream>
using namespace std;
#include "Party.h"
#include "PiAlice.h"
#include "PiBob.h"
#include <math.h>  
#include <stdlib.h>
// const's for prg
#define c 2531011
#define a 214013
#define m 4294967296

#define ALICE_INPUT 0, Alice.TS, Alice.TR, Alice.tempS[(Alice.parity + 1) % 4], Alice.tempR[(Alice.parity + 1) % 4], Alice.tempS[Alice.newT], Alice.tempR[Alice.newT], Alice.indexresultTS, Alice.indexTS, Alice.countones, Alice.randAlice
#define BOB_INPUT 0, Bob.TS, Bob.TR, Bob.tempS[(Bob.parity + 1)%4], Bob.tempR[(Bob.parity + 1)%4], Bob.tempS[Bob.newT], Bob.tempR[Bob.newT], Bob.indexresultTS, Bob.indexTS,Bob.countones, Bob.randBob


Party::Party()
{
	countones = 0;
	count = 0;
	indexTR = 0;
	randAlice = 0;
	randBob = 0;
	indexTS = 0;
	indexresultTR = 0;
	indexresultTS = 0;
	phase = 0;
	tempR = new Block[4];
	tempS = new Block[4];//300 * ((n / 32) + 1)
	TR = new unsigned int[5 * ((n / 32) + 1)];
	TS = new unsigned int[5 * ((n / 32) + 1)];
	pumpSeed = new unsigned int[5 * ((n / 32) + 1)];
	sendZero = false;
	Tindex = 0;
	for (int i = 0; i < 4; i++)
	{
		tempR[i].resetBlock();
		tempS[i].resetBlock();
	}
	for (int i = 0; i <= (5 * (n / 32)); i++)
	{
		TR[i] = 0;
		TS[i] = 0;
	}
	for (int i = 0; i <= (5 * (n / 32)); i++)
	{
		pumpSeed[i] = 0;
	}

}
Party::~Party()
{
	delete TR;
	delete TS;
}


// initialize var's between 2 phases - sending prg bits and rest of protocol
void Party::nextPhase()
{
	countones = 0;
	count = 0;
	indexTR = 0;
	randAlice = 0;
	randBob = 0;
	indexTS = 0;
	indexresultTR = 0;
	indexresultTS = 0;
	phase = 1;
	Tindex = 0;
	for (int i = 0; i < 4; i++)
	{
		tempR[i].resetBlock();
		tempS[i].resetBlock();
	}
	for (int i = 0; i <= (5 * (n / 32)); i++)
	{
		TR[i] = 0;
		TS[i] = 0;
	}

}

// check if trans are equal
bool Party::checkreal(unsigned int* b1,unsigned int* b2)
{
	int index = n / 32;
	for (int i = 0; i < index; i++)
	{
		if (b1[i] != b2[i])
			return false;
	}
	if (n % 32 != 0)
	{
		int mod = n % 32;
		int po = pow(2, mod);
		if ((b1[index] % po) != (b2[index] % po))
			return false;
	}
	return true;

}
bool Party::checkAllTrans(Party& alice, Party& bob)
{

	if (alice.count*BLOCK_SIZE - alice.countones < n || bob.count*BLOCK_SIZE - bob.countones< n)
		return false;
	return (checkreal(alice.TR, bob.TS) && checkreal(alice.TS, bob.TR));
}

// get appropriate bit from prg string
unsigned int Party::getBitXor(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine)
{
	int countBits = 0;
	if (temp_newS.getBlock() != temp_p_1S.getBlock())	// they are not the same block
		countBits = indexresultTS * 32 + indexTS + temp_p_1S.getIndex() + temp_newS.getIndex() - countones;
	else
		countBits = indexresultTS * 32 + indexTS + temp_p_1S.getIndex() - countones;
	int specTR = countBits / 32;
	int specBit = ( countBits) % 32;
	unsigned int ret = this->pumpSeed[specTR] / pow(2, specBit);
	ret = ret % 2;
	return ret;
}

void Party::noErrorsOnBothSides(Party& Alice, Party& Bob)
{
	Bob.tempR[Bob.newT].resetBlock();
	Bob.tempS[Bob.newT].resetBlock();
	Alice.tempS[Alice.newT].resetBlock();
	Alice.tempR[Alice.newT].resetBlock();
	for (int i = 0; i < BLOCK_SIZE; i++)
	{

		// Alice sends, Bob receives
		if (i >= BLOCK_SIZE - 3 && Alice.tempS[Alice.newT].checkIfk3Zero())	// pad 1 in case of need
		{
			Alice.sendBit = 1;
		}
		else  // no need to pad 1
		{
			if (0==Alice.phase)	// send prg bits
			{
				Alice.sendBit = PiAlice::piRand(ALICE_INPUT);
			}
			else				// run protocol
			{
				Alice.sendBit = PiAlice::Pi(ALICE_INPUT) ^ Alice.getBitXor(ALICE_INPUT);
			}
		}
		// save bits
		Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Bob.tempR[Bob.newT].fillBlock(Channel::sendabit(Alice.sendBit));

		
		// Bob sends, Alice receives
		if (i >= BLOCK_SIZE - 3 && Bob.tempS[Bob.newT].checkIfk3Zero())	// pad 1 in case of need
		{
			Bob.sendBit = 1;
		}
		else  // no need to pad 1
		{
			if (0 == Bob.phase)	// send prg bits
			{
				Bob.sendBit = PiBob::piRand(BOB_INPUT);
			}
			else				// run protocol
			{
				Bob.sendBit = PiBob::Pi(BOB_INPUT)^Bob.getBitXor(BOB_INPUT);
			}
				
		}
		// save bits
		Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);
		Alice.tempR[Alice.newT].fillBlock(Channel::sendabit(Bob.sendBit));

	}

}
void Party::bothSidesSeeErrors(Party& Alice, Party& Bob)
{
	// both sides send a zeros block
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		// Alice sends, Bob receives
		Alice.sendBit = 0;
		Channel::sendabit(Alice.sendBit);
		
		// Bob sends, Alice receives
		Bob.sendBit = 0;
		Channel::sendabit(Bob.sendBit);
	}

	Alice.sendZero = false;
	Bob.sendZero = false;

}
void Party::AliceSeesErrorBobNot(Party& Alice, Party& Bob)
{
	Bob.tempR[Bob.newT].setIndex(0);
	Bob.tempS[Bob.newT].setIndex(0);
	for (int i = 0; i < BLOCK_SIZE - 2; i++)
	{
		// Alice sends, Bob receives
		Alice.sendBit = 0;

		Bob.tempR[Bob.newT].fillBlock(Channel::sendabit(Alice.sendBit));

		// Bob sends, Alice receives
		if (0 == Bob.phase)		// send prg bits
		{
			Bob.sendBit = PiBob::piRand(BOB_INPUT);
		}
		else                    // run protocol
		{
			Bob.sendBit = PiBob::Pi(BOB_INPUT) ^ Bob.getBitXor(BOB_INPUT);
		}

		Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);

		Channel::sendabit(Bob.sendBit);
	}

	// calculate parity
	int paritybit[2];
	int p = (Alice.parity + 1) % 4;
	if (p % 2 == 0)
		paritybit[1] = 0;
	else
		paritybit[1] = 1;
	p = p / 2;
	paritybit[0] = p;


	for (int i = 0; i < 2; i++)
	{
		// Alice sends, Bob receives
		Alice.sendBit = paritybit[i];
		Bob.tempR[Bob.newT].fillBlock(Channel::sendabit(Alice.sendBit));

		// Bob sends, Alice receives
		if (Bob.phase==0)	// send prg bits
		{
			Bob.sendBit = PiBob::piRand(BOB_INPUT);

		}
		else                 // run protocol
		{
			Bob.sendBit = PiBob::Pi(BOB_INPUT) ^ Bob.getBitXor(BOB_INPUT);
		}
		Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);
		Channel::sendabit(Bob.sendBit);
	}

	Alice.sendZero = false;
}
void Party::BobSeesErrorAliceNot(Party& Alice, Party& Bob)
{
	Alice.tempS[Alice.newT].setIndex(0);
	Alice.tempR[Alice.newT].setIndex(0);
	for (int i = 0; i < BLOCK_SIZE - 2; i++)
	{
		// Alice sends, Bob receives
		if (Alice.phase==0)		// send prg bits
		{
			Alice.sendBit = PiAlice::piRand(ALICE_INPUT);
		}
		else                   // run protocol
		{
			Alice.sendBit = PiAlice::Pi(ALICE_INPUT) ^ Alice.getBitXor(ALICE_INPUT);
		}
		Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::sendabit(Alice.sendBit);



		// Alice sends, Bob receives
		Bob.sendBit = 0;
		Alice.tempR[Alice.newT].fillBlock(Channel::sendabit(Bob.sendBit));
	}

	// calculate parity
	int paritybit[2];
	int p = (Bob.parity + 1) % 4;
	if (p % 2 == 0)
		paritybit[1] = 0;
	else
		paritybit[1] = 1;
	p = p / 2;
	paritybit[0] = p;


	for (int i = 0; i < 2; i++)
	{
		// Alice sends, Bob receives
		if (Alice.phase==0)			// send prg bits
		{
			Alice.sendBit = PiAlice::piRand(ALICE_INPUT);
		}
		else                        // run protocol
		{
			Alice.sendBit = PiAlice::Pi(ALICE_INPUT) ^ Alice.getBitXor(ALICE_INPUT);
		}

		Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::calcP();
		Channel::sendabit(Alice.sendBit);

		// Alice sends, Bob receives
		Bob.sendBit = paritybit[i];
		Alice.tempR[Alice.newT].fillBlock(Channel::sendabit(Bob.sendBit));
	}

	Bob.sendZero = false;
}
void Party::checkAllCasesInProtocol(Party& good)
{
	int checker = (good.parity + 2) % 4;
	int bit0;
	int bit1;
	int parity;
	int flag = 0;
	bit0 = good.tempR[good.newT].getBlock()[BLOCK_SIZE - 2];
	bit1 = good.tempR[good.newT].getBlock()[BLOCK_SIZE - 1];
	parity = bit1 + 2 * bit0;	// convert to decimal
	if (bit1 == 2 || bit0 == 2)
		flag = 1;
	// lines 11-14
	if (good.tempR[good.newT].checkIfAllZero() && flag == 0)
	{
		//zero temp blocks - line 12
		good.tempR[(parity) % 4].resetBlock();
		good.tempR[(parity + 1) % 4].resetBlock();
		good.tempS[(parity) % 4].resetBlock();
		good.tempS[(parity + 1) % 4].resetBlock();


		// line 13
		if ((parity % 4) == (good.newT % 4))
		{
			good.sendZero = true;
		}
	}

	// lines 15-16 - we got erasures in the last block filled
	else if (good.tempR[good.newT].checkIfError())
	{
		// line 16
		good.tempR[good.newT].resetBlock();
		good.tempS[good.newT].resetBlock();

		good.sendZero = true;	// line 17
	}

	// line 18-19 - concatenation to transcript

	else if (good.newT == checker)
	{
		good.addBlockTR(good.tempR[(good.parity + 1) % 4]);
		good.addBlockTS(good.tempS[(good.parity + 1) % 4]);
		if (good.tempS[good.newT].checkIfk3Zero())
		{
			good.countones = good.countones + 3;
		}
		good.Tindex++;
	}
}
void Party::addBlockTR(Block& blocktoadd) // this function takes a block and put it in the transcript of recieved
{
	int count3 = 1;
		int checker = 0;
		for (int i = indexTR; i < indexTR + BLOCK_SIZE; i++)
		{
			if (i < 32)
			{
				TR[indexresultTR] += pow(2, i)*blocktoadd.getBlock()[i - indexTR];
			}
			else
			{
				TR[indexresultTR + 1] += pow(2, i - 32 * count3)*blocktoadd.getBlock()[i - indexTR];
				checker = 1;
				if (i - count3 * 32 == 31)
				{
					count3++;
					indexresultTR++;
				}
			}
		}
		count3 = 1;
		if (checker == 1)
			indexresultTR++;
		indexTR += BLOCK_SIZE;
		if (indexTR == 32)
		{
			indexTR = 0;
			indexresultTR++;
		}
		if (indexTR > 32)
			indexTR = indexTR % 32;
		count++;
	
}
void Party::addBlockTS(Block& blocktoadd) // // this function takes a block and put it in the transcript of sent
{
	int count3 = 1;
	{
		int checker = 0;
		for (int i = indexTS; i < indexTS + BLOCK_SIZE; i++)
		{
			if (i < 32)
			{
				TS[indexresultTS] += pow(2, i)*blocktoadd.getBlock()[i - indexTS];
			}
			else
			{
				TS[indexresultTS + 1] += pow(2, i - 32 * count3)*blocktoadd.getBlock()[i - indexTS];
				checker = 1;
				if (i - count3 * 32 == 31)
				{
					count3++;
					indexresultTS++;
				}
			}
		}
		count3 = 1;
		if (checker == 1)
			indexresultTS++;
		indexTS += BLOCK_SIZE;
		if (indexTS == 32)
		{
			indexTS = 0;
			indexresultTS++;
		}
		if (indexTS > 32)
			indexTS = indexTS % 32;
	}
}
void Party::print(Party&Alice,Party&Bob)
{
	std::cout << "Alice TS" << endl;
	Party::printbits(Alice.TS);
	std::cout << "Bob TR" << endl;
	Party::printbits(Bob.TR);
	std::cout << "Bob TS" << endl;
	Party::printbits(Bob.TS);
	std::cout << "Alice TR" << endl;
	Party::printbits(Alice.TR);
}
void Party::printbits(unsigned int * b1) //this function prints all the bits of a given int of bits . 
{

	for (int i = 0; i < n/32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			cout << b1[i] % 2;
			b1[i] /= 2;
		}
	}
	if (n % 32 != 0)
	{
		int mod = n % 32;
		int po = pow(2, mod);
		int num = b1[(n / 32)] % po;
		for (int i = 0; i < mod; i++)
		{
			cout << num % 2;
			num /= 2;
		}
	}
	cout << endl;
}
void Party::getRandom(Party& Alice, Party& Bob) //get 32 bit seed for both sides .
{
	for (int i = 0; i < 32; i++)
	{
		Alice.randAlice += pow(2, i)*(std::rand() % 2);
	}
	for (int i = 0; i < 32; i++)
	{
		Bob.randBob += pow(2, i)*(std::rand() % 2);
	}
}
unsigned int Party::gen32PRGbit(unsigned int seed) //a strong prg with good parameters for our useage.
{
	return (seed*a + c) % m;
}
void Party::pumpRandom()
{
	this->pumpHalfRandom(this->randAlice, this->randBob);
	
}
void Party::pumpHalfRandom(unsigned int seed,unsigned int seed2) //pump a pseudo random string for one side.
{
	int size = n / 64 + 1;
	this->pumpSeed[0] = seed;
	unsigned int temp = seed;
	int i;
	for (i=1 ; i < size; i++)
	{
		temp = gen32PRGbit(temp);
		this->pumpSeed[i] = temp;	
	}
	int j = 0;
	this->pumpSeed[i + j] = seed2;
	temp = seed2;
	for (j = 1; j < size; j++)
	{
		temp = gen32PRGbit(temp);
		this->pumpSeed[i+j] = temp;
	}
}


int Party::getCount()
{
	return this->count;
}

int Party::getCountOnes()
{
	return this->countones;
}

bool Party::getSendZero()
{
	return this->sendZero;
}


int Party::getParity()
{
	return this->parity;
}

void Party::setParity(int par)
{
	this -> parity = par;
}

void Party::setNewT(int nt)
{
	this->newT = nt;
}

int Party::getTindex()
{
	return this->Tindex;
}

Block* Party::getTempR()
{
	return this->tempR;
}
Block* Party::getTempS()
{
	return this->tempS;
}

void Party::setRandAlice(unsigned int rand)
{
	this->randAlice = rand;
}

void Party::setRandBob(unsigned int rand)
{
	this->randBob = rand;
}

unsigned int* Party::getTR()
{
	return this->TR;
}
