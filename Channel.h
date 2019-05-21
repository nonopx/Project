#pragma once
#include <stdlib.h>     /* srand, rand */
#include <ctime>
//#include <iostream>
#include <cstdlib>





class Channel
{
private:
	unsigned int epsilon;		//	max bound of uniform dist.


public:

	int drawNum();
	Channel(unsigned int epsilon);
	~Channel();
	int sendabit(int sendbit);
	int getDigits();
	int calcUniDist();

};

