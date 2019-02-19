#pragma once
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <iostream>
#include <cstdlib>

class Channel
{
public:
	static int p;

	static void calcP()
	{

		p = std::rand() % 500 + 1;
	}
	Channel();
	~Channel();
};

