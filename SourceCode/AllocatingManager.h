
#include "Allocating.h"
#ifndef ALLOCATINGMANAGER_H
#define ALLOCATINGMANAGER_H
#include <string>
class AllocatingManager
{
public:
	int allocating(Allocating* allocating);
	int addTime(string computerID, int ihour, int imin);
	int stopPc(string pcID);
	void stopPcUpdate(string pcID);
	void checkTime();

	Allocating* getComputer(string pcID);


	



};

#endif