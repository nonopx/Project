#include <iostream>
using namespace std;
#include "Party.h"
#include "Channel.h"
#include  "Block.h"
int check = 0;


void allGood(Party& Alice, Party& Bob)
{
	Bob.tempR[Bob.newT].index = 0;
	Bob.tempS[Bob.newT].index = 0;
	Alice.tempS[Alice.newT].index = 0;
	Alice.tempR[Alice.newT].index = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		// Alice sends, Bob receives
		Alice.sendBit = Party::Pi();
		Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);

		Channel::calcP();
		if (1 == Channel::p)
		{
			Alice.sendBit = 2; cout<<"BOB SEES ERROR - round of error : "<<check<<endl;
		}
		Bob.tempR[Bob.newT].fillBlock(Alice.sendBit);


		// Bob sends, Alice receives
		Bob.sendBit = Party::Pi();
		Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);

		Channel::calcP();
		if (1 == Channel::p)
		{
			Bob.sendBit = 2; cout << "ALICE SEES ERROR - round of error : " << check << endl;
		}
		Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);
	}

}

void fillParityOneBit(Party& send, Party& rec, int index)
{
	Party::incrementCounter();

	if (0 == send.parity)
	{
		if (0 == index)
		{
			send.sendBit = 0;
			//send.tempS[send.newT].fillBlock(send.sendBit);
			Channel::calcP();
			if (1 == Channel::p)
			{
				send.sendBit = 2;
			}
			Party::incrementCounter();
			rec.tempR[rec.newT].fillBlock(send.sendBit);
		}
		else // index == 1		
		{
			send.sendBit = 1;
			//send.tempS[send.newT].fillBlock(send.sendBit);
			Channel::calcP();
			if (1 == Channel::p)
			{
				send.sendBit = 2;
			}
			Party::incrementCounter();
			rec.tempR[rec.newT].fillBlock(send.sendBit);
		}
	}


	if (1 == send.parity)
	{
		if (0 == index)
		{
			send.sendBit = 1;
			//send.tempS[send.newT].fillBlock(send.sendBit);
			Channel::calcP();
			if (1 == Channel::p)
			{
				send.sendBit = 2;
			}
			Party::incrementCounter();
			rec.tempR[rec.newT].fillBlock(send.sendBit);
		}
		else // index == 1		
		{
			send.sendBit = 0;
			//send.tempS[send.newT].fillBlock(send.sendBit);
			Channel::calcP();
			if (1 == Channel::p)
			{
				send.sendBit = 2;
			}
			Party::incrementCounter();
			rec.tempR[rec.newT].fillBlock(send.sendBit);
		}
	}


	if (2 == send.parity)
	{
			send.sendBit = 1;
			//send.tempS[send.newT].fillBlock(send.sendBit);
			Channel::calcP();
			if (1 == Channel::p)
			{
				send.sendBit = 2;
			}
			Party::incrementCounter();
			rec.tempR[rec.newT].fillBlock(send.sendBit);
	}

	if (3 == send.parity)
	{
			send.sendBit = 0;
			//send.tempS[send.newT].fillBlock(send.sendBit);
			Channel::calcP();
			if (1 == Channel::p)
			{
				send.sendBit = 2;
			}
			Party::incrementCounter();
			rec.tempR[rec.newT].fillBlock(send.sendBit);
	}

}

void allBad(Party& Alice, Party& Bob)
{
	for (int i = 0; i < BLOCK_SIZE ; i++)
	{
		// Alice sends, Bob receives
		Alice.sendBit = 0;
		//Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Alice.sendBit = 2; cout << "BOB SEES ERROR - round of error : " << check << endl;
		}
		Party::incrementCounter();
		//Bob.tempR[Bob.newT].fillBlock(Alice.sendBit);

		// Bob sends, Alice receives
		Bob.sendBit = 0;
		//Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Bob.sendBit = 2; cout << "ALICE SEES ERROR - round of error : " << check << endl;
		}
		Party::incrementCounter();
		//Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);
	}

	Alice.sendZero = false;
	Bob.sendZero = false;
	Party::counter = (Party::counter + BLOCK_SIZE) % 3;

}

void AliceBadBobGood(Party& Alice, Party& Bob)
{
	Bob.tempR[Bob.newT].index = 0;
	Bob.tempS[Bob.newT].index = 0;
	for (int i = 0; i < BLOCK_SIZE - 2; i++)
	{
		// Alice sends, Bob receives
		Alice.sendBit = 0;
		//Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Alice.sendBit = 2; cout << "BOB SEES ERROR - round of error : " << check << endl;
		}
		Party::incrementCounter();
		Bob.tempR[Bob.newT].fillBlock(Alice.sendBit);

		// Bob sends, Alice receives
		Bob.sendBit = Party::Pi();
		Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);

		Channel::calcP();
		if (1 == Channel::p)
		{
			Bob.sendBit = 2; cout << "ALICE SEES ERROR - round of error : " << check << endl;
		}
		//Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);
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
		//Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Alice.sendBit = 2; cout << "BOB SEES ERROR - round of error : " << check << endl;
		}
		Party::incrementCounter();
		Bob.tempR[Bob.newT].fillBlock(Alice.sendBit);

		// Bob sends, Alice receives
		Bob.sendBit = Party::Pi();
		Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);

		Channel::calcP();
		if (1 == Channel::p)
		{
			Bob.sendBit = 2; cout << "ALICE SEES ERROR - round of error : " << check << endl;
		}
		//Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);
	}

	Alice.sendZero = false;
}

void AliceGoodBobBad(Party& Alice, Party& Bob)
{
	Alice.tempS[Alice.newT].index = 0;
	Alice.tempR[Alice.newT].index = 0;
	for (int i = 0; i < BLOCK_SIZE - 2; i++)
	{
		Alice.sendBit = Party::Pi();
		Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Alice.sendBit = 2; cout << "BOB SEES ERROR - round of error : " << check << endl;
		}
		//Bob.tempR[Bob.newT].fillBlock(Alice.sendBit);



		// Alice sends, Bob receives
		Bob.sendBit = 0;
		//Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Bob.sendBit = 2; cout << "ALICE SEES ERROR - round of error : " << check << endl;
		}
		Party::incrementCounter();
		Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);

		// Bob sends, Alice receives
		
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
		Alice.sendBit = Party::Pi();
		Alice.tempS[Alice.newT].fillBlock(Alice.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Alice.sendBit = 2; cout << "BOB SEES ERROR - round of error : " << check << endl;
		}
		//Bob.tempR[Bob.newT].fillBlock(Alice.sendBit);



		// Alice sends, Bob receives
		Bob.sendBit = paritybit[i];
		//Bob.tempS[Bob.newT].fillBlock(Bob.sendBit);
		Channel::calcP();
		if (1 == Channel::p)
		{
			Bob.sendBit = 2; cout << "ALICE SEES ERROR - round of error : " << check << endl;
		}
		Party::incrementCounter();
		Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);
		//Alice.tempR[Alice.newT].fillBlock(Bob.sendBit);
	}
	
	Bob.sendZero = false;
}

void oneGood(Party& good)
{
	int checker = (good.parity + 2) % 4;
	int bit0;
	int bit1;
	int parity;
	int flag=0;
	bit0 = good.tempR[good.newT].block[BLOCK_SIZE - 2];
	bit1 = good.tempR[good.newT].block[BLOCK_SIZE - 1];
	parity = bit1 + 2 * bit0;	// convert to decimal
	if (bit1 == 2 || bit0 == 2)
		flag = 1;
	// lines 11-14
	if (good.tempR[good.newT].checkIfAllZero() && flag==0)
	{
		//cout << "nod" << endl;
		// catch parity bits
		
		
		
		
		//zero temp blocks - line 12
		//good.tempR[good.newT].index = 0;
		//good.tempS[good.newT].index = 0;
		good.tempR[(parity) % 4].resetBlock();
		good.tempR[(parity+1) % 4].resetBlock();
		good.tempS[(parity) % 4].resetBlock();
		good.tempS[(parity+1) % 4].resetBlock();


		Party::counter = (Party::counter + 2 * BLOCK_SIZE) % 3;	// return counter to its correct value

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
		good.TR[good.Tindex].addBlock(good.tempR[(good.parity + 1)%4]);
		good.TS[good.Tindex].addBlock(good.tempS[(good.parity + 1)%4]);
		//good.tempR[(good.parity + 1) % 4].index = 0;
		//good.tempS[(good.parity + 1) % 4].index = 0;
		cout << "BLOCK " << good.Tindex << " ADDED TO " << good.name <<" IN ROUND "<<check<<endl;
		good.Tindex++;
	}
}

int main()
{


	Party Alice;
	Alice.name = 0;
	Party Bob;
	Bob.name = 1;
	int round = 0;
	std::srand(std::time(0));
	while (round!=70)	// round = 2k bits (k bits each party)
	{
		check = round;
		//calculate parity for each party - line 3
		Alice.parity = Alice.Tindex % 4;	
		Bob.parity = Bob.Tindex % 4;

		//calculate new for each party - line 4
		Alice.newT = (Alice.Tindex + Alice.tempS[(Alice.parity + 1)%4].isFull() + 1) % 4;
		Bob.newT = (Bob.Tindex + Bob.tempS[(Bob.parity + 1)%4].isFull() + 1) % 4;

		
		if (Alice.sendZero == false && Bob.sendZero == false)
		{
			allGood(Alice, Bob);	// send block of k bits, each
		
			// lines 11-19 - check all scenarios
			oneGood(Alice);			
			oneGood(Bob);
		}
		else if (Alice.sendZero == true && Bob.sendZero == true)
		{
			allBad(Alice, Bob);
		}
		else if (Alice.sendZero == true && Bob.sendZero == false)
		{
			AliceBadBobGood(Alice, Bob);
			oneGood(Bob);
		}
		else if (Alice.sendZero == false && Bob.sendZero == true)
		{
			AliceGoodBobBad(Alice, Bob);
			oneGood(Alice);
		}


		round++;

	}
	/*std::cout << "Alice sent : " << endl;
	for (int i = 0; i < MAX_SIZE; i++)
		std::cout << Alice.sent[i] << " ";
	std::cout << endl << endl;
	std::cout << "Bob rec : " << endl;
	for (int j = 0; j < 4; j++)
	for (int i = 0; i < 5; i++)
		std::cout << recBobBlocks[j].block[i] << " ";
	std::cout << endl << endl;
	std::cout << "Bob sent : " << endl;
	for (int i = 0; i < MAX_SIZE; i++)
		std::cout << Bob.sent[i] << " ";
	std::cout << endl << endl;
	std::cout << "Alice rec : " << endl;
	for (int j = 0; j < 4; j++)
	for (int i = 0; i < 5; i++)
		std::cout << recAliceBlocks[j].block[i] << " ";
	std::cout << endl << endl;
	cout << "Bob flags : " << endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << recBobBlocks[i].flag << " ";
	}
	std::cout << endl << endl;
	std::cout << "Alice sent : " << endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << recAliceBlocks[i].flag << " ";
	}*/
	/*std::cout << "Alice sent : " << endl;
	for (int j = 1; j < 4; j++)
		for (int i = 0; i < 5; i++)
			std::cout << Alice.tempS[j].block[i]<<" ";
		cout << endl;
	std::cout << "Bob rec : " << endl;
	for (int j = 1; j < 4; j++)
		for (int i = 0; i < 5; i++)
			std::cout << Bob.tempR[j].block[i]<< " ";
		cout << endl;
	std::cout << "Bob sent : " << endl;
	for (int j = 1; j < 4; j++)
		for (int i = 0; i < 5; i++)
			std::cout << Bob.tempS[j].block[i] << " ";
		cout << endl;
	std::cout << "Alice rec : " << endl;
	for (int j = 1; j < 4; j++)
		for (int i = 0; i < 5; i++)
			std::cout << Alice.tempR[j].block[i] << " ";
		cout << endl;*/

	for (int i = 0; i < 55;i++)
		for (int j = 0; j < BLOCK_SIZE;j++)
		if (Alice.TR[i].block[j] == 5 || Alice.TS[i].block[j] == 5 || Bob.TS[i].block[j] == 5 || Bob.TR[i].block[j] == 5)
			cout << " didnt finish "<<i<<endl;
	/*	std::cout << "Alice.TR " << endl;
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[0].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[1].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[2].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[3].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[4].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[5].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[6].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[7].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[8].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TR[9].block[i];
		cout << endl;
		std::cout << "Alice.TS " << endl;
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[0].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[1].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[2].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[3].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[4].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[5].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[6].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[7].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[8].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Alice.TS[9].block[i];
		cout << endl;
		std::cout << "Bob.TR " << endl;
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[0].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[1].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[2].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[3].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[4].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[5].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[6].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[7].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[8].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TR[9].block[i];
		cout << endl;
		std::cout << "Bob.TS " << endl;
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[0].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[1].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[2].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[3].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[4].block[i];
		for (int i = 0; i < BLOCK_SIZE i++)
			cout << Bob.TS[5].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[6].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[7].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[8].block[i];
		for (int i = 0; i < BLOCK_SIZE; i++)
			cout << Bob.TS[9].block[i];
		
		*/
	int y;
	std::cin >> y;
	return 0;





























////////////////
////////////////
////////////////
////////////////
////////////////
////////////////
////////////////
////////////////	Party Alice;
////////////////	Party Bob;
////////////////	int round = 0;
////////////////	int blockNumber = 0;
////////////////	int x;
////////////////	Block* recAliceBlocks = new Block[MAX_SIZE];
////////////////	Block* recBobBlocks = new Block[MAX_SIZE];
////////////////	std::srand(std::time(0));
////////////////	while (1 == 1)
////////////////	{
////////////////		if (round != MAX_SIZE)
////////////////		{
////////////////
////////////////			/***** Alice sends, bob receives*******/
////////////////			if (0 != blockNumber && recAliceBlocks[blockNumber - 1].flag == true)
////////////////			{
////////////////				Alice.sendBit = 0;
////////////////				Party::incrementCounter();
////////////////			}
////////////////			else
////////////////				Alice.sendBit = Party::Pi();
////////////////
////////////////			Alice.sent[round] = Alice.sendBit;
////////////////			Channel::calcP();
////////////////			if (1 == Channel::p)
////////////////			{
////////////////				Alice.sendBit = 2; cout<<"***2***"<<endl;
////////////////			}
////////////////			recBobBlocks[blockNumber].fillBlock(Alice.sendBit);
////////////////
////////////////			Bob.received[round] = Alice.sendBit;
////////////////
////////////////
////////////////
////////////////
////////////////			/******* Bob sends, Alice receives*****/
////////////////			if (0 != blockNumber && recBobBlocks[blockNumber - 1].flag == true)
////////////////			{
////////////////				Bob.sendBit = 0;
////////////////				Party::incrementCounter();
////////////////			}
////////////////			else
////////////////				Bob.sendBit = Party::Pi();
////////////////
////////////////			Bob.sent[round] = Bob.sendBit;
////////////////			Channel::calcP();
////////////////			if (1 == Channel::p)
////////////////			{
////////////////				Bob.sendBit = 2; cout<<"***2***"<<endl;
////////////////			}
////////////////			recAliceBlocks[blockNumber].fillBlock(Bob.sendBit);
////////////////
////////////////			if (recAliceBlocks[blockNumber].isFull())
////////////////			{
////////////////				recBobBlocks[blockNumber].checkIfError();
////////////////				recAliceBlocks[blockNumber].checkIfError();
////////////////				if (blockNumber > 0)
////////////////				{
////////////////					recBobBlocks[blockNumber - 1].resetFlag();
////////////////					recAliceBlocks[blockNumber - 1].resetFlag();   ///reset flags of the next round
////////////////				}
////////////////				blockNumber++;
////////////////
////////////////			}
////////////////			Alice.received[round] = Bob.sendBit;
////////////////			round++;
////////////////		}
////////////////		else
////////////////			break;
////////////////	}
////////////////
	/*std::cout << "Alice sent : " << endl;
	for (int i = 0; i < MAX_SIZE; i++)
	std::cout << Alice.sent[i] << " ";
	std::cout << endl << endl;

	std::cout << "Bob received : " << endl;
	for (int i = 0; i < MAX_SIZE / BLOCK_SIZE; i++)
	std::cout << recBobBlocks[i].block << " ";
	std::cout << endl << endl;
	std::cout << "Bob sent : " << endl;
	for (int i = 0; i < MAX_SIZE; i++)
	std::cout << Bob.sent[i] << " ";
	std::cout << endl << endl;
	std::cout << "Alice received : " << endl;
	for (int i = 0; i < MAX_SIZE; i++)
	std::cout << recAliceBlocks[i].block << " ";*/

	
}