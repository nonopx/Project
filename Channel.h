#pragma once
#include <stdlib.h>     /* srand, rand */
#include <ctime>
//#include <iostream>
#include <cstdlib>
#include "Party.h"




class Channel
{
private:
	static int p;


public:

	static void calcP()
	{

		p = std::rand() % 316 + 1; //only until 32767!!!
	}
	Channel();
	~Channel();
	static int sendabit(int sendbit);
};

