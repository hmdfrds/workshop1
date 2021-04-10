#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Member.h"
#include "MemberManager.h"
#include <conio.h>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

time_t now = time(0);
tm* ltm = localtime(&now);
time_t current = time(0);


int MemberManager::insertMember(Member* member)
{
	
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO member VALUES (?, ?, ?,?, ?, ?,?,?)");

	ps->setInt(1, member->NO);
	ps->setString(2, member->memberID);
	ps->setString(3, member->password);
	ps->setString(4, member->name);
	ps->setString(5, member->icNumber);
	ps->setString(6, member->noTel);
	ps->setString(7, member->membershipTime);
	ps->setString(8, to_string(ltm->tm_yday + stoi(member->membershipTime)));


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

bool MemberManager::login(Member* member)
{

	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM member WHERE memberID = ?");

	ps->setString(1, member->memberID);

	ResultSet* rs = ps->executeQuery();

	if (!(rs->next()))
	{
		cout << "\n\n\t\t\tID IS WRONG" << endl;
		system("pause");
		return false;

	}
	else
	{
		delete rs;
		delete ps;

		ps = dbConn.prepareStatement("SELECT * FROM member WHERE memberID = ? AND password = ?");

		ps->setString(1, member->memberID);
		ps->setString(2, member->password);

		rs = ps->executeQuery();

		if (!(rs->next()))
		{
			cout << "\n\n\t\t\t PASSWORD IS WRONG " << endl;
			system("pause");
			return false;
		}
		delete rs;
		delete ps;

	}

	return true;
}

Member* MemberManager::selectMember(string memberID)
{
	Member* member = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM member WHERE memberID = ?");

	ps->setString(1, memberID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		member = new Member();

		member->NO = rs->getInt(1);
		member->memberID = rs->getString(2);
		member->password = rs->getString(3);
		member->name = rs->getString(4);
		member->icNumber = rs->getString(5);
		member->noTel = rs->getString(6);
		member->membershipTime = rs->getString(7);
		member->day = rs->getInt(8);
		delete rs;
		delete ps;
		return member;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

Member* MemberManager::selectMemberNo(int NO)
{

	Member* member = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM member WHERE NO = ?");

	ps->setInt(1, NO);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		member = new Member();

		member->NO = rs->getInt(1);
		member->memberID = rs->getString(2);
		member->password = rs->getString(3);
		member->name = rs->getString(4); 
		member->icNumber = rs->getString(5);
		member->noTel = rs->getString(6);
		member->membershipTime = rs->getString(7);
		member->day = rs->getInt(8);

		delete rs;
		delete ps;
		
	}
	else
	{
		delete rs;
		delete ps;
		member = 0;
	}
	return member;
}

int MemberManager::updateMember(string ID , string att , string data)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE member SET name = (?) WHERE memberID = (?) ");

	if (att == "0")
	{
		ps = dbConn.prepareStatement("UPDATE member SET name = (?) WHERE memberID = (?) ");
	}
	else if (att == "1")
	{
		ps = dbConn.prepareStatement("UPDATE member SET password = (?) WHERE memberID = (?) ");
	}
	else if (att == "2")
	{
		ps = dbConn.prepareStatement("UPDATE member SET noTel = (?) WHERE memberID = (?) ");
	}
	else if (att == "3")
	{
		ps = dbConn.prepareStatement("UPDATE member SET membershipTime = (?) WHERE memberID = (?) ");
	}

	else
	{
		cout << "the attribute is not exist." << endl;
		system("pause");
		return 0;
	}
	
	ps->setString(1, data);
	ps->setString(2, ID);


	int status = ps->executeUpdate();

	if (att == "3") {
		ps = dbConn.prepareStatement("UPDATE member SET day = (?) WHERE memberID = (?) ");
		ps->setString(1, to_string(ltm->tm_yday));
		ps->setString(2, ID);
		int status = ps->executeUpdate();
	}
	delete ps;

	return status;
}

int MemberManager::deleteMember(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM member WHERE memberID = ? ");

	ps->setString(1, ID);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

void MemberManager::showAllMember()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM member");

	ResultSet* rs = ps->executeQuery();
	cout << "\n\n"<<setw(8)<<"Member ID"<< setw(40) <<"Member Name" << setw(20) <<"IC Number " <<setw(20) <<"Telephone Number"<< setw(25) << "Membership Time(day)" << endl;
	cout << "==================================================================================================================" << endl << endl;
	while (rs->next())
	{
		cout <<""<< rs->getString(2) << setw(40) << rs->getString(4) << setw(20) <<rs->getString(5)<< setw(20) << rs->getString(6) << setw(15) << rs->getString(7) << endl;
		
	}
	cout << "\n==================================================================================================================" << endl << endl;
}

int MemberManager::updateMembershipTime()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	time_t current = time(0);

	

	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM member");

	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		if (stoi(rs->getString(7)) > 0 ) {

			ps = dbConn.prepareStatement("UPDATE member SET membershipTime = (?) WHERE memberID = (?) ");

			int newDay = stoi(rs->getString(8)) - ltm->tm_yday  ;
			if (newDay < 0) {
				newDay = 0;
			}
			ps->setString(1, to_string(newDay));
			ps->setString(2, rs->getString(2));
			ps->executeUpdate();
		}

	}

}

int MemberManager::checkMemberTime(string ID) {

	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT membershipTime FROM member WHERE memberID = ?");
	ps->setString(1, ID);
	ResultSet* rs = ps->executeQuery();
	if (rs->next())
	{

		if (stoi(rs->getString(1)) > 0) {
			delete ps;
			return 1;
		}
		else 
			delete ps;
			return 0;
		
	}
}

int MemberManager::searchMember(int lastMemberID) {



	Member* member = new Member();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;
	
	bool check = true;
	int y = 1;
	int c = 0;
	int NO = 0;
	string name = "";
	vector <string> arrow;
	for (int i = 0; i <= lastMemberID; i++) {
		arrow.push_back("  ");
	}
	if (lastMemberID != 0) {
		arrow[1] = "-> ";
	}


	
	system("cls");
	cout << "\t\t\t\t\t\tType Name to Search" << endl;
	cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
	cout << setw(11) << "Member ID" << setw(40) << "Member Name" << setw(20) << "IC Number " << setw(20) << "Telephone Number" << setw(25) << "Membership Time(day)" << endl;
	cout << "  ==================================================================================================================" << endl << endl;

	for (int i = 1; i <= lastMemberID; i++) {
		ps = dbConn.prepareStatement("SELECT NO FROM member WHERE name LIKE ? AND NO = ?");
		ps->setString(1, "%" + name + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{
			member = selectMemberNo(rs->getInt(1));
			cout << arrow[i] << member->memberID << setw(40) << member->name << setw(20) << member->icNumber << setw(20) << member->noTel << setw(15) << member->membershipTime << endl;
		}


	}
	cout << "\n  ==================================================================================================================" << endl << endl;
	

	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
			return y;
		}
		if (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z' || c == ' ' || c == '.' || c == '/')) {
			name += c;

			ps = dbConn.prepareStatement("SELECT MIN(NO) FROM member WHERE name LIKE ?");
			ps->setString(1, "%" + name + "%");

			rs = ps->executeQuery();
			if (rs->next()) {
				arrow[y] = "  ";
				y = rs->getInt(1);
				arrow[y] = "-> ";
			}

		}
		if (c == '\b') {
			if (name.size() >= 1) {
				name.pop_back();
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM member WHERE name LIKE ?");
				ps->setString(1, "%" + name + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}
			}
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				if (y > 1) {
					arrow[y] = "  ";
					int j = y;
					j--;
					bool c = true;
					while (c) {
						ps = dbConn.prepareStatement("SELECT NO FROM member WHERE name LIKE ? AND NO = ?");
						ps->setString(1, "%" + name + "%");
						ps->setInt(2, j);
						rs = ps->executeQuery();
						if (rs->next()) {
							y = j;
							c = false;
						}
						if (j == 1) {
							c = false;
						}
						else {
							j--;
						}



					}
					arrow[y] = "-> ";
				}
				break;
			case KEY_DOWN:
				if (y < lastMemberID) {
					arrow[y] = "  ";
					int j = y;
					j++;
					bool c = true;
					while (c) {
						ps = dbConn.prepareStatement("SELECT NO FROM member WHERE name LIKE ? AND NO = ?");
						ps->setString(1, "%" + name + "%");
						ps->setInt(2, j);
						rs = ps->executeQuery();
						if (rs->next()) {
							y = j;
							c = false;
						}
						if (j == lastMemberID) {
							c = false;
						}
						else {
							j++;
						}



					}
					arrow[y] = "-> ";
				}
				break;
			default:

				break;
			}
		}
		if (c == '0') { return 0; }

		if (check) {

			


			system("cls");
			cout << "\t\t\t\t\t\tType Name to Search" << endl;
			cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
			cout << setw(11) << "Member ID" << setw(40) << "Member Name" << setw(20) << "IC Number " << setw(20) << "Telephone Number" << setw(25) << "Membership Time(day)" << endl;
			cout << "  ==================================================================================================================" << endl << endl;

			for (int i = 1; i <= lastMemberID; i++) {
				ps = dbConn.prepareStatement("SELECT NO FROM member WHERE name LIKE ? AND NO = ?");
				ps->setString(1, "%" + name + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{
					member = selectMemberNo(rs->getInt(1));
					cout << arrow[i] << member->memberID << setw(40) << member->name << setw(20) << member->icNumber << setw(20) << member->noTel << setw(15) << member->membershipTime << endl;
				}


			}
			cout << "\n  ==================================================================================================================" << endl << endl;
		}
		
	}

	return 1;
}

int MemberManager::addMembershipTime(string memberID , int day) {

	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE member SET day = (?) WHERE memberID = (?) ");

	ps->setInt(1, day);
	ps->setString(2, memberID);


	int status = ps->executeUpdate();
	return status;
}



