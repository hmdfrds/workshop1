#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Computer.h"
#include "ComputerManager.h"

int ComputerManager::insertComputer(Computer* computer)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO computer VALUES (?, ?, ?)");

	ps->setInt(1, computer->NO);
	ps->setString(2, computer->computerID);
	ps->setString(3, computer->status);



	int status = ps->executeUpdate();


	delete ps;

	return (status );
}


Computer* ComputerManager::selectComputer(string computerID)
{
	
	Computer* computer = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM computer WHERE computerID = ?");

	ps->setString(1, computerID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		computer = new Computer();

		computer->computerID = rs->getString(2);
		computer->status = rs->getString(3);

		delete rs;
		delete ps;
		return computer;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}

}

Computer* ComputerManager::selectComputerNo(int NO)
{
	
	Computer* computer = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM computer WHERE NO = ?");

	ps->setInt(1, NO);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		computer = new Computer();

		computer->computerID = rs->getString(2);
		computer->status = rs->getString(3);

		delete rs;
		delete ps;
		return computer;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}

}



int ComputerManager::updateComputerU(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE computer SET status = (?) WHERE computerID = (?) ");

	ps->setString(1, "unavailable");
	ps->setString(2, ID);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int ComputerManager::updateComputerA(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE computer SET status = (?) WHERE computerID = (?) ");

	ps->setString(1, "available");
	ps->setString(2, ID);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int ComputerManager::deleteComputer(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM computer WHERE computerID = ? ");


	ps->setString(1, ID);

	int status = ps->executeUpdate();



	delete ps;

	return (status );
}

void ComputerManager::showAllComputer()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM computer");

	ResultSet* rs = ps->executeQuery();
	cout << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID"<<setw(15) <<"Status  |" <<endl;
	cout << "\t\t\t\t|=========================|" << endl ;
	while (rs->next())
	{
		
		cout  <<"\t\t\t\t|"<< rs->getString(2) <<setw(16)<< rs->getString(3) <<"|"<< endl;
	
	}
	cout << "\t\t\t\t+-------------------------+" << endl;
}

