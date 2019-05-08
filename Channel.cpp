#include <iostream>
using namespace std;
#include "Channel.h"


Channel::Channel()
{
}


Channel::~Channel()
{
}
int Channel::sendabit(int sendbit)
{
	Channel::calcP();
	if (1 == Channel::p)
	{
		Channel::calcP();
		if (1 == Channel::p)
		{
			sendbit = 2;
		}
	}
	return sendbit;
}
int Channel::p = 0;
