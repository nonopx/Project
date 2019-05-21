#pragma once
#define n 500000
#include "block.h"
#include "Channel.h"
#include "Pi.h"
#include "PiOne.h"
#include "PiRand.h"
#include "PiZero.h"

#ifdef UNSIGNEDINT_IS_32BITS
typedef unsigned int int32;
#else
#ifdef INT_IS_32BITS
typedef int int32;
#endif
#endif
class Party
{
private:
	int count;
	int indexTR;	// point to inside int
	int indexresultTR;	// which int we are taliking
	int indexTS;
	int indexresultTS;
	int countones;
	bool sendZero;
	int sendBit;
	int parity;
	int newIndex;
	int Tindex;	// |T/2k|
	Block* tempR;
	Block* tempS;
	unsigned int randAlice;
	unsigned int randBob;
	unsigned int* pumpSeed;
	unsigned int* TR;
	unsigned int *TS;
	int phase;
	Pi* pi;


public:

	Party(int pi);
	unsigned int getBitXor(int x, unsigned int* tr, unsigned int* ts, Block& temp_p_1S, Block& temp_p_1R, Block& temp_newS, Block& temp_newR, int indexresultTS, int indexTS, int countones, unsigned int randmine);
	static bool checkreal(unsigned int* b1, unsigned int* b2);
	static bool checkAllTrans(Party& alice, Party& bob);
	void nextPhase();
	void addBlockTR(Block& blocktoadd);
	void addBlockTS(Block& blocktoadd);
	static void noErrorsOnBothSides(Party& Alice, Party& Bob, Channel& channelAliceToBob, Channel& channelBobToAlice);
	static void bothSidesSeeErrors(Party& Alice, Party& Bob, Channel& channelAliceToBob, Channel& channelBobToAlice);
	static void AliceSeesErrorBobNot(Party& Alice, Party& Bob, Channel& channelAliceToBob, Channel& channelBobToAlice);
	static void BobSeesErrorAliceNot(Party& Alice, Party& Bob, Channel& channelAliceToBob, Channel& channelBobToAlice);
	static void print(Party& Alice, Party& Bob);
	static void checkAllCasesInProtocol(Party& good);
	static void printbits(unsigned int * b1);
	static void getRandom(Party& alice, Party& bob);
	void pumpRandom();


	// get's & set's
	int getCount();
	int getCountOnes();
	bool getSendZero();
	int getParity();
	void setParity(int par);
	void setNewIndex(int nt);
	int getTindex();
	Block* getTempR();
	Block* getTempS();
	Pi * getPi();
	void setRandAlice(unsigned int rand);
	void setRandBob(unsigned int rand);
	unsigned int* getTR();

	~Party();
};

