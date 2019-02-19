#include "Party.h"

Party::Party()
{
	received = new int[MAX_SIZE];
	sent = new int[MAX_SIZE];
	tempR = new Block[4];
	tempS = new Block[4];
	TR = new Block[10*MAX_SIZE]; 
	TS = new Block[10*MAX_SIZE];
	sendZero = false;
	Tindex = 0;
	for (int i = 0; i < 4; i++)
	{
		tempR[i].fillZeroBlock();
		tempS[i].fillZeroBlock();
	}
	for (int i = 0; i < 10*MAX_SIZE; i++)
	{
		TR[i].fillZeroBlock();
		TS[i].fillZeroBlock();
	}
} 
Party::~Party()
{
}
int Party::Pi()
{
	counter++;
	if (counter == 1)
		return 1;
	if (counter == 2)
		return 0;
	if (counter == 3)
	{
		counter = 0;
		return 1;
	}
	return 700;
}

void Party::incrementCounter()
{
	counter = (counter + 1) % 3;	// mod 3 according to Pi
}
int Party::counter = 0;
