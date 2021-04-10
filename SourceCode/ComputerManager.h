#ifndef COMPUTERMANAGER_H
#define COMPUTERMANAGER_H

class ComputerManager
{
public:
	int insertComputer(Computer* computer);
	Computer* selectComputer(string computerID);
	Computer* selectComputerNo(int NO);

	int updateComputerU(string ID);
	int updateComputerA(string ID);
	int deleteComputer(string ID);
	void showAllComputer();
};

#endif