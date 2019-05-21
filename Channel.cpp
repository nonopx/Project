#include <iostream>
using namespace std;
#include "Channel.h"
#include <random>
#include <stdlib.h>     /* srand, rand */
#include <ctime>
//#include <iostream>
#include <cstdlib>
#include <math.h>



Channel::Channel(unsigned int epsilon)
{
	this->epsilon = epsilon;

}


Channel::~Channel()
{
}


int Channel::drawNum()
{
	int p = 0;
	p = calcUniDist();
	while (p>=epsilon)
	{
		p = calcUniDist();
	}
	return p;

	//int p = std::rand() % 9;


	//int p= std::rand() % 316 + 1;
	//return p;

	//int p1 = std::rand() % 32768 ; //only until 32767!!! so we use p^2
	//int p2 = std::rand() % 32768 ;
	
	//std::random_device rd;  //Will be used to obtain a seed for the random number engine
	//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	//std::uniform_int_distribution<unsigned int> dis(1, epsilon);
	//return dis(gen);
	//return p;
}

int Channel::sendabit(int sendbit)
{
	if (1 == this->drawNum())
			sendbit = 2;

	return sendbit;
}

int Channel::getDigits()
{
	int digits = 0;
	int temp = epsilon;
	while (0 != temp)
	{
		digits++;
		temp = temp / 10;
	}
	return digits;
}

int Channel::calcUniDist()
{
	int digits = this->getDigits();
	int dist = 0;
	for (int i = digits-1; i >= 0; i--)
	{
		dist += (std::rand() % 10)*pow(10, i);
		if (dist >= epsilon) return dist;	//	out of bounds, return invalid value
	}

	return dist;
}
