#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Admin.h"
#include "AdminManager.h"
#include <conio.h>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;


int AdminManager::insertAdmin(Admin* admin)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO admin VALUES (?, ?, ?, ?, ?)");

	ps->setInt(1, admin->NO);
	ps->setString(2, admin->adminID);
	ps->setString(3, admin->password);
	ps->setString(4, admin->name);
	ps->setString(5, admin->noTel);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

bool AdminManager::login(Admin* admin)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM admin WHERE adminID = ?");
	ps->setString(1, admin->adminID);
	ResultSet* rs = ps->executeQuery();
	if (!(rs->next()))
	{
		system("CLS");
		cout << "id is wrong, pls insert again"<<endl;
		system("pause");
		return false;
	}
	else
	{
		delete rs;
		delete ps;
		ps = dbConn.prepareStatement("SELECT * FROM admin WHERE adminID = ? AND password = ?");
		ps->setString(1, admin->adminID);
		ps->setString(2, admin->password);
		rs = ps->executeQuery();
		if (!(rs->next())){
			system("CLS");
			cout << "pass is wrong, pls insert again " << endl;
			system("pause");
			return false;
		}
		delete rs;
		delete ps;
	}
	return true;
}

Admin* AdminManager::selectAdmin(string adminID)
{
	Admin* admin = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM admin WHERE adminID = ?");

	ps->setString(1, adminID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		admin = new Admin();

		admin->adminID = rs->getString(2);
		admin->name = rs->getString(4);
		admin->password = rs->getString(3);
		admin->noTel = rs->getString(5);
		delete rs;
		delete ps;
		return admin;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

Admin* AdminManager::selectAdminNO(int no) {
	Admin* admin = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM admin WHERE NO = ?");

	ps->setInt(1, no);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		admin = new Admin();

		admin->adminID = rs->getString(2);
		admin->name = rs->getString(4);
		admin->password = rs->getString(3);
		admin->noTel = rs->getString(5);
		delete rs;
		delete ps;
		return admin;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

int AdminManager::updateAdmin(string ID, string att, string data)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE admin SET name = (?) WHERE adminID = (?) ");

	if (att == "0")
	{
		ps = dbConn.prepareStatement("UPDATE admin SET name = (?) WHERE adminID = (?) ");
	}
	else if (att == "1")
	{
		ps = dbConn.prepareStatement("UPDATE admin SET Password = (?) WHERE adminID = (?) ");
	}
	else if (att == "2")
	{
		ps = dbConn.prepareStatement("UPDATE admin SET noTel = (?) WHERE adminID = (?) ");
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

	delete ps;

	return status;
}

int AdminManager::deleteAdmin(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM admin WHERE adminID = ? ");

	ps->setString(1, ID);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

void AdminManager::showAllAdmin()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM admin");



	ResultSet* rs = ps->executeQuery();
	cout << "\t\t\t\t ADMIN LIST" << endl;
	cout << "\n\n" << setw(8) << "Admin ID" << setw(40) << "Admin Name" << setw(20) << "Telephone Number " << endl;
	cout << "===================================================================" << endl << endl;
	while (rs->next())
	{
		cout << "" << rs->getString(2) << setw(40) << rs->getString(4) << setw(19) << rs->getString(5)  << endl;

	}
	cout << "\n===================================================================" << endl << endl;
}

int AdminManager::searchAdmin(int lastAdminID) {



	Admin* admin = new Admin();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;

	bool check = true;
	int y = 1;
	int c = 0;
	int NO = 0;
	string name = "";
	vector <string> arrow;
	for (int i = 0; i <= lastAdminID; i++) {
		arrow.push_back("  ");
	}
	if (lastAdminID != 0) {
		arrow[1] = "-> ";
	}



	system("cls");
	cout << "\t\t\t\t\t\tType Name to Search" << endl;
	cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
	cout << "\n\n" << setw(8) << "Admin ID" << setw(40) << "Admin Name" << setw(20) << "Telephone Number " << endl;
	cout << "===================================================================" << endl << endl;

	for (int i = 1; i <= lastAdminID; i++) {
		ps = dbConn.prepareStatement("SELECT NO FROM admin WHERE name LIKE ? AND NO = ?");
		ps->setString(1, "%" + name + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{
			admin = selectAdminNO(rs->getInt(1));
			cout << arrow[i] << admin->adminID << setw(40) << admin->name << setw(19) << admin->noTel << endl;
		}
		

	}
	cout << "===================================================================" << endl << endl;


	while (check)
	{

		c = 0;



		switch ((c = _getch())) {
		case KEY_UP:
			if (y > 1) {
				arrow[y] = "  ";
				int j = y;
				j--;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM admin WHERE name LIKE ? AND NO = ?");
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
			if (y < lastAdminID) {
				arrow[y] = "  ";
				int j = y;
				j++;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM admin WHERE name LIKE ? AND NO = ?");
					ps->setString(1, "%" + name + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == lastAdminID) {
						c = false;
					}
					else {
						j++;
					}



				}
				arrow[y] = "-> ";
			}
			break;
		case '\r':
			check = false;
			return y;
		case '\b':
			if (name.size() >= 1) {
				name.pop_back();
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM admin WHERE name LIKE ?");
				ps->setString(1, "%" + name + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}
			}
			break;
		default:
			if (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z' || c == ' ' || c == '.' || c == '/')) {
				name += c;

				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM admin WHERE name LIKE ?");
				ps->setString(1, "%" + name + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}

			}
			break;
		}

		if (c == '0') { return 0; }

		if (check) {




			system("cls");
			cout << "\t\t\t\t\t\tType Name to Search" << endl;
			cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
			cout << "\n\n" << setw(8) << "Admin ID" << setw(40) << "Admin Name" << setw(20) << "Telephone Number " << endl;
			cout << "===================================================================" << endl << endl;

			for (int i = 1; i <= lastAdminID; i++) {
				ps = dbConn.prepareStatement("SELECT NO FROM admin WHERE name LIKE ? AND NO = ?");
				ps->setString(1, "%" + name + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{
					admin = selectAdminNO(rs->getInt(1));
					cout << arrow[i] << admin->adminID << setw(40) << admin->name << setw(19) << admin->noTel << endl;
				}


			}
			cout << "===================================================================" << endl << endl;
		}
	}

	return 1;
}