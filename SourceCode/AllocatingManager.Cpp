#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "AllocatingManager.h"
#include "Allocating.h"
#include "Computer.h"
#include "ComputerManager.h"
#include "PaymentManager.h"



int AllocatingManager::allocating(Allocating* allocating)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO allocatingComputers VALUES ( ?, ?, ?,?, ?)");


	ps->setString(1, allocating->userID);
	ps->setString(2, allocating->computerID);
	ps->setString(3, allocating->endTime);
	ps->setString(4, allocating->totalTime);
	ps->setString(5, allocating->startTime);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AllocatingManager::addTime(string pcID, int ihour , int imin)
{
	Allocating* allocating = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM allocatingcomputers WHERE computerID = ?");

	ps->setString(1, pcID);
	
	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		allocating = new Allocating();
		allocating->userID = rs->getString(1);
		allocating->computerID = rs->getString(2);
		allocating->endTime = rs->getString(3);
		allocating->totalTime = rs->getString(4);
		string hour = "", min = "" , sec = "";

		int k = 0;
		for (int j = 0; j < allocating->totalTime.size(); j++) {
			if (allocating->endTime[j] != ':' && k == 0) {
				hour += allocating->endTime[j];
			}
			if (allocating->endTime[j] != ':' && k == 1) {
				min += allocating->endTime[j];
			}
			if (allocating->endTime[j] != ':' && k == 2) {
				sec += allocating->endTime[j];
			}
			if (allocating->endTime[j] == ':') {
				k++;
			}
		}


		int tmin = imin +stoi(min);
		int thour = ihour + stoi(hour);

		if (tmin > 59) {
			tmin = tmin - 60;
			thour++;
		}
		string totalTime = to_string(thour) + ":" + to_string(tmin) + ":" + sec;
		ps = dbConn.prepareStatement("UPDATE allocatingComputers SET totalTime = (?) WHERE computerID = (?) ");

		ps->setString(1, totalTime);
		ps->setString(2, pcID);
		ps->executeUpdate();

		hour = "", min = "", sec = "";
		 k = 0;
		for (int j = 0; j < allocating->endTime.size(); j++) {
			if (allocating->endTime[j] != ':' && k == 0) {
				hour += allocating->endTime[j];
			}
			if (allocating->endTime[j] != ':' && k == 1) {
				min += allocating->endTime[j];
			}
			if (allocating->endTime[j] != ':' && k == 2) {
				sec += allocating->endTime[j];
			}
			if (allocating->endTime[j] == ':') {
				k++;
			}
		}

		
		 imin += stoi(min);
		 ihour += stoi(hour);

		 if (imin > 59) {
			 imin = imin - 60;
			 ihour++;
		 }
		 string endTime = to_string(ihour) + ":" + to_string(imin) + ":" + sec;
		 ps = dbConn.prepareStatement("UPDATE allocatingComputers SET endTime = (?) WHERE computerID = (?) ");

		 ps->setString(1, endTime);
		 ps->setString(2, pcID);
		int status =  ps->executeUpdate();
		delete rs;
		delete ps;
		return status;
	}
	return 0;


}

int AllocatingManager::stopPc(string pcID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM allocatingComputers WHERE computerID = ?");

	ps->setString(1, pcID);

	int status = ps->executeUpdate();

	

	return status;
}

void AllocatingManager::stopPcUpdate(string pcID) {

	PaymentManager paymentManager;
	ComputerManager computerManager;
	Allocating* allocating = new Allocating;


	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM allocatingcomputers WHERE computerID = ?");
	ps->setString(1, pcID);
	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		time_t current = time(0);
		string hour, min, sec;
		allocating->startTime = rs->getString(5);
		int k = 0;
		for (int j = 0; j < allocating->startTime.size(); j++) {
			if (allocating->startTime[j] != ':' && k == 0) {
				hour += allocating->startTime[j];
			}
			if (allocating->startTime[j] != ':' && k == 1) {
				min += allocating->startTime[j];
			}
			if (allocating->startTime[j] != ':' && k == 2) {
				sec += allocating->startTime[j];
			}
			if (allocating->startTime[j] == ':') {
				k++;
			}
		}
		int isec = stoi(sec);
		int imin = stoi(min);
		int ihour = stoi(hour);
		int csec = ltm->tm_sec;
		int cmin = ltm->tm_min;
		int chour = ltm->tm_hour;


		if (csec < isec) {
			cmin--;
			csec += 60;
		}

		if (cmin < imin) {
			chour--;
			cmin += 60;
		}
		
		int rsec = csec - isec;
		int rmin = cmin - imin;
		int rhour = chour - ihour;
		allocating->userID = rs->getString(1);
		allocating->computerID = rs->getString(2);
		allocating->endTime = rs->getString(3);
		allocating->totalTime = to_string(rhour) + ":" + to_string(rmin) + ":" + to_string(rsec);

		paymentManager.addIntoList(allocating);
	
	}
}

void AllocatingManager::checkTime()
{
	PaymentManager paymentManager;
	ComputerManager computerManager;
	Allocating* allocating = new Allocating;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM allocatingcomputers ");

	ResultSet* rs = ps->executeQuery();

	while (rs->next()) {

		time_t now = time(0);
		tm* ltm = localtime(&now);
		time_t current = time(0);
		string hour, min, sec;
		allocating->endTime = rs->getString(3);
		int k = 0;
		for (int j = 0; j < allocating->endTime.size(); j++) {
			if (allocating->endTime[j] != ':' && k == 0) {
				hour += allocating->endTime[j];
			}
			if (allocating->endTime[j] != ':' && k == 1) {
				min += allocating->endTime[j];
			}
			if (allocating->endTime[j] != ':' && k == 2) {
				sec += allocating->endTime[j];
			}
			if (allocating->endTime[j] == ':') {
				k++;
			}
		}
		int isec = stoi(sec);
		int imin = stoi(min);
		int ihour = stoi(hour);


		if (isec < ltm->tm_sec) {
			imin--;
			isec += 60;
		}

		if (imin < ltm->tm_min) {
			ihour--;
			imin += 60;
		}

		int rsec = isec - ltm->tm_sec;
		int rmin = imin - ltm->tm_min;
		int rhour = ihour - ltm->tm_hour;


		if (rsec < 0 || rmin < 0 || rhour < 0) {

			allocating->userID = rs->getString(1);
			allocating->computerID = rs->getString(2);
			allocating->endTime = rs->getString(3);
			allocating->totalTime = rs->getString(4);
			ps = dbConn.prepareStatement("DELETE FROM allocatingComputers WHERE computerID = ? ");

			ps->setString(1, rs->getString(2));
			 ps->executeUpdate();
			
			computerManager.updateComputerA(allocating->computerID);
			
			paymentManager.addIntoList(allocating);
			

		}
	}
}

Allocating* AllocatingManager::getComputer(string pcID)
{
	Allocating* allocating = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM allocatingcomputers WHERE computerID = ?");

	ps->setString(1, pcID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		allocating = new Allocating();

		allocating->userID = rs->getString(1);
		allocating->computerID = rs->getString(2);
		allocating->endTime = rs->getString(3);

		delete rs;
		delete ps;
		return allocating;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}

}



