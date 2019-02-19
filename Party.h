#pragma once
#define MAX_SIZE 150
#include "block.h"
class Party
{

public:
	int name;
	static int counter;
	bool sendZero;
	int sendBit;
	int * received;
	int * sent;
	int parity;
	int newT;
	int Tindex;	// |T/2k|
	Block* tempR;
	Block* tempS;
	Block* TR;
	Block* TS;
	Party();
	static void incrementCounter();

	static int Pi();
	~Party();
};

