#include <iostream>
using namespace std;
#include "Party.h"
#include "Channel.h"
#include  "Block.h"
#include <fstream>
#include "Pi.h"
#include "PiOne.h"
#include "PiRand.h"
#include "PiZero.h"
#include <math.h>  

int runProtocol(Party & Alice, Party & Bob, int limit, Channel& channelAliceToBob, Channel& channelBobToAlice)
{
	int round = 0;
	while (round != 7000000000)	// round = 2k bits (k bits each party), run protocol "on the fly"
	{
		// protocol finished
		if (Alice.getCount()*BLOCK_SIZE - Alice.getCountOnes() >= limit && Bob.getCount()*BLOCK_SIZE - Bob.getCountOnes() >= limit)
			break;
		//calculate parity for each party - line 3
		Alice.setParity(Alice.getTindex() % 4);
		Bob.setParity(Bob.getTindex() % 4);

		//calculate new for each party - line 4
		Alice.setNewIndex((Alice.getTindex() + Alice.getTempS()[(Alice.getParity() + 1) % 4].isFull() + 1) % 4);
		Bob.setNewIndex((Bob.getTindex() + Bob.getTempS()[(Bob.getParity() + 1) % 4].isFull() + 1) % 4);


		if (Alice.getSendZero() == false && Bob.getSendZero() == false)	// no errors
		{
			Party::noErrorsOnBothSides(Alice, Bob, channelAliceToBob, channelBobToAlice);	// send block of k bits, each

			// lines 11-19 - check all scenarios
			Party::checkAllCasesInProtocol(Alice);
			Party::checkAllCasesInProtocol(Bob);
		}
		else if (Alice.getSendZero() == true && Bob.getSendZero() == true)	// both parties saw error last round
		{
			Party::bothSidesSeeErrors(Alice, Bob, channelAliceToBob, channelBobToAlice);
		}
		else if (Alice.getSendZero() == true && Bob.getSendZero() == false)	// Alice saw error last round
		{
			Party::AliceSeesErrorBobNot(Alice, Bob, channelAliceToBob, channelBobToAlice);
			Party::checkAllCasesInProtocol(Bob);
		}
		else if (Alice.getSendZero() == false && Bob.getSendZero() == true)	// Bob saw error last round
		{
			Party::BobSeesErrorAliceNot(Alice, Bob, channelAliceToBob, channelBobToAlice);
			Party::checkAllCasesInProtocol(Alice);
		}


		round++;

	}
	return round;
}


int mainExe(Party &Alice,Party &Bob)
{
	Channel channelAliceToBob(100000);
	Channel channelBobToAlice(100000);
	Party::getRandom(Alice, Bob);
	int round1 = runProtocol(Alice, Bob, 32, channelAliceToBob, channelBobToAlice);
	Alice.setRandBob(Alice.getTR()[0]);
	Bob.setRandAlice(Bob.getTR()[0]);
	Alice.pumpRandom();
	Bob.pumpRandom();
	Alice.nextPhase();
	Bob.nextPhase();
	int round2 = runProtocol(Alice, Bob, n, channelAliceToBob, channelBobToAlice);
	return (round1 + round2)*BLOCK_SIZE;
}


void main()
{
	
	std::srand(std::time(0));
	int test = 2;
	if (test == 1)
	{
		double count[10000];
		for (int i = 0; i <= 10000; i++)
		{
			count[i] = 0;
		}
		for (int j = 4; j <= 1000; j++)
		{
			BLOCK_SIZE = j;
			for (int i = 0; i < 2; i++)
			{
				//PiAlice::generateTrans();
				//PiBob::generateTrans();
			//	count[j] += mainExe(Alice,Bob);
			}
		}



		for (int i = 0; i < 2; i++)
		{
			char d = (char)(7);
			printf("%c\n", d);
		}
		ofstream myfile;
		myfile.open("pi1_4-1000.txt");
		for (int j = 4; j <= 1000; j++)
		{
			count[j] = count[j] / 2;
			myfile << count[j] << endl;
		}

		myfile.close();
	}
	else if (test == 0)
	{

	//	PiAlice::generateTrans();
	//	PiBob::generateTrans();
		//mainExe(Alice,Bob);
	}
	else if (test == 2)
	{
		int rate = 0;
		BLOCK_SIZE = 16;
		for (int i = 0; i < 10; i++)
		{
			Party Alice(2);
			Party Bob(2);

			rate += mainExe(Alice,Bob);
		}
		std::cout << ((rate / 10));
	}

	int y;
	cin >> y;
}
