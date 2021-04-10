#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <thread>        
#include <vector>
#include <mysql/jdbc.h>
using namespace sql;
using namespace std;
#include "Admin.h";
#include "AdminManager.h";
#include "Member.h";
#include "MemberManager.h";
#include "Computer.h"
#include "ComputerManager.h"
#include "DatabaseConnection.h"
#include "Allocating.h"
#include "AllocatingManager.h"
#include "PaymentManager.h"
#include "Payment.h"


//ARROW KEYS

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

//for loop purpose
char input() {
	char a;
	if (_kbhit()) {
		a = _getch();
		return a;
	}
}

//ADMIN

int lastAdminID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from admin");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}
	
}

void adminRegister()
{
	system("CLS");

	string ID = "A0319000";
	string lastID = to_string(lastAdminID() + 1);
	int k = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (i > (ID.size() - 1) - lastID.size() ) {
			ID[i] = lastID[k++];
		}
	}

	Admin* newadmin = new Admin();

	newadmin->NO = lastAdminID() + 1;
	newadmin->adminID = ID;

ANAME:
	
	system("cls");
	cout << "\t\t\t\t\t Maximun character is 30" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  ADMIN REGISTER			" << endl;
	cout << "\t\t\t 	Name			: ";

	newadmin->NO = lastAdminID() + 1;
	newadmin->adminID = ID;


	getline(cin, newadmin->name);
	if (newadmin->name == "0") {
		return;
	}
	if (newadmin->name.size() > 30) {
		cout << "\t\t\t\t\t MAX CHARACTER IS 30" << endl;
		system("pause");
		goto ANAME;
	}
	else if (newadmin->name.size() == 0) {
		cout << "\t\t\t\t\t PLEASE INSERT SOMETHING" << endl;
		system("pause");
		goto ANAME;
	}


APASSWORD:
	system("cls");
	cout << "\t\t\t\t\t Make sure to remember your password" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  ADMIN REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newadmin->name << endl;
	cout << "\t\t\t 	Password		: ";

	getline(cin, newadmin->password);
	if (newadmin->password == "0") {
		return;
	}

	system("cls");
	cout << "\t\t\t\t\t Type again your password" << endl << endl;

	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  ADMIN REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newadmin->name << endl;
	cout << "\t\t\t 	Password		: " << "***..." << endl;

	cout << "\n\n\t\t\tConfirm Password : ";

	string cpass;
	getline(cin, cpass);
	if (cpass != newadmin->password) {
		system("cls");
		cout << "\t\t\t\t\t !!!!!!!" << endl << endl;

		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			  ADMIN REGISTER			" << endl;
		cout << "\t\t\t 	Name			: " << newadmin->name << endl;
		cout << "\t\t\t 	Password		: " << "***..." << endl;

		cout << "\n\n\t\t\tConfirm Password : ***..." << endl;
		cout << "\n\t\t\t\tPASSWORD IS NOT SAME" << endl;
		system("pause");
		goto APASSWORD;

	}

ANOTEL:
	system("cls");
	cout << "\t\t\t\t\t Insert a valid phone number" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  ADMIN REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newadmin->name << endl;
	cout << "\t\t\t 	Password		: " << "***..." << endl;
	cout << "\t\t\t 	noTel			: ";

	bool check = false;
	getline(cin, newadmin->noTel);
	if (newadmin->noTel == "0") {
		return;
	}
	if (isdigit(newadmin->noTel[0]) && newadmin->noTel[0] == '0') {
		int intNoPhone = stoi(newadmin->noTel);
		newadmin->noTel = "0" + to_string(intNoPhone);
	}
	else { check = true; }
	if (newadmin->noTel.size() != 10 || check) {
		cout << "\t\t\t\t\t INVALID TELEPHONE NUMBER" << endl;
		cout << "\t\t\t\t\t MUST BE DIGIT" << endl;
		system("pause");
		goto ANOTEL;
	}


	AdminManager adminManage;
	int status = adminManage.insertAdmin(newadmin);

	if (status != 0)
		cout << "\n\n\t\t\tSuccessfully added a new admin with no ID = " << ID << endl << endl;
	else
		cout << "\n\n\t\t\tUnable to add a new admin." << endl;
	delete newadmin;
	system("pause");

}

bool adminLogin()
{

	system("CLS");
	AdminManager Manager;
	Admin* login = new Admin;

	bool check = true;
	while (check) {

		system("CLS");

		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN ADMIN			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Admin ID : ";



		getline(cin, login->adminID);
		if (login->adminID == "0") {
			return "0";
		}
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN ADMIN			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Admin ID : " << login->adminID << endl;
		cout << "\t\t\t			Password  : ";

		string pass;
		int i = 0;
		char a;
		for (i = 0;;) {
			a = _getch();
			if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {

				pass += a;
				++i;
				cout << "*";

			}
			if (a == '\b' && i >= 1) {
				cout << "\b \b";
				--i;
			}
			if (a == '\r') {
				break;
			}

		}


		login->password = pass;
		if (login->password == "0") {
			return "0";
		}

		if (Manager.login(login))
		{
			check = false;
		}
		else
		{
			check = true;
		}
	}


}

void showAllAdmin()
{
	AdminManager admin;

	admin.showAllAdmin();
	cout << endl << endl;
	system("pause");
}

void updateAdmin()
{
	START:
	system("CLS");
	bool stay = false;

		AdminManager manage;
		Admin* admin;
		int y = 1;
		int c = 0;

		int z = manage.searchAdmin(lastAdminID());

		if (z == 0) {
			return;
		}

	AGAIN:

		admin = manage.selectAdminNO(z);
		system("cls");
		cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t->Name			: " << admin->name << endl;
		cout << "\t\t\t\t  Password		: ***...." << endl;
		cout << "\t\t\t\t  Telephone Number	: " << admin->noTel << endl;
		cout << "\n\t==============================================================================================" << endl << endl;

		y = 0;
		bool check = true;
		while (check) {
			c = 0;

			switch ((c = _getch())) {
			case KEY_UP:

				y--;

				break;
			case KEY_DOWN:

				y++;

				break;
			case '\r':
				check = false;
			default:
				// not arrow
				break;
			}
			if (c == '0') {
				goto START;
			}
			if (y < 0) {
				y = 0;

			}
			if (y > 2) {
				y = 2;

			}
			if (y == 0) {
				system("cls");
				cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
				cout << endl;
				cout << "\t==============================================================================================" << endl << endl;
				cout << "\t\t\t\t->Name			: " << admin->name << endl;
				cout << "\t\t\t\t  Password		: ***...." << endl;
				cout << "\t\t\t\t  Telephone Number	: " << admin->noTel << endl;
				cout << "\n\t==============================================================================================" << endl << endl;
			}
			else if (y == 1) {
				system("cls");
				cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
				cout << endl;
				cout << "\t==============================================================================================" << endl << endl;
				cout << "\t\t\t\t  Name			: " << admin->name << endl;
				cout << "\t\t\t\t->Password		: ***...." << endl;
				cout << "\t\t\t\t  Telephone Number	: " << admin->noTel << endl;
				cout << "\n\t==============================================================================================" << endl << endl;
			}
			else if (y == 2) {
				system("cls");
				cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
				cout << endl;
				cout << "\t==============================================================================================" << endl << endl;
				cout << "\t\t\t\t  Name			: " << admin->name << endl;
				cout << "\t\t\t\t  Password		: ***...." << endl;
				cout << "\t\t\t\t->Telephone Number	: " << admin->noTel << endl;
				cout << "\n\t==============================================================================================" << endl << endl;
			}

			else {}

		}
		system("cls");
		string update;
		if (y == 0) {
			cout << "\t\t\t\tUpdate Name" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: ";
			getline(cin, update);
		}
		else if (y == 1) {
			cout << "\t\t\t\tUpdate Password" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Password			: ";
			getline(cin, update);
		}
		else if (y == 2) {
			cout << "\t\t\t\tUpdate Telephone Number" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Telephone Number		: ";
			getline(cin, update);
		}

		if (manage.updateAdmin(admin->adminID, to_string(y), update)) {
			cout << "\t\t\t\tUPDATE SUCCESS" << endl;
		}
		else {
			cout << "\t\t\t\tUPDATE FAILED" << endl;
		}
		system("pause");
		goto AGAIN;

	
	return ;
}

void deleteAdmin()
{

	AdminManager manage;
	Admin* admin = new Admin();
	string option;
	int y = manage.searchAdmin(lastAdminID());
	if (y == 0) {
		return;
	}

	do {
		admin = manage.selectAdminNO(y);
		system("cls");
		cout << "\t\t\t\t" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Name			: " << admin->name << endl;
		cout << "\t\t\t\t  Password		: ***...." << endl;
		cout << "\t\t\t\t  Telephone Number	: " << admin->noTel << endl;
		cout << "\n\t==============================================================================================" << endl << endl;


		cout << "\t\t\tCONFIRM TO DELETE ADMIN (Y/N) : ";
		getline(cin, option);
		if (!(option == "N" || option == "n" || option == "y" || option == "Y")) {
			cout << "\n\t\t\t INSERT APPROPIATE INPUT";
			boost::detail::Sleep(1000);
		}

	} while (!(option == "N" || option == "n" || option == "y" || option == "Y"));
	if (option == "N" || option == "n") {
		return;
	}
	int status = manage.deleteAdmin(admin->adminID);
	if (status) {
		cout << "\n\t\t\tdelete succeed."<<endl;
	}
	else {
		cout << "\n\t\t\tdelete failed." << endl;
	}
	system("pause");
	
}

void adminMastery() {

START:
	system("CLS");
	bool check = true;
	int c, y = 0;
	cout << endl << endl;
	cout << "\t\t\tMENU > ADMIN" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#                         ADMIN                                 #" << endl;
	cout << "\t\t\t#               ->1.Register Admin                              #" << endl;
	cout << "\t\t\t#                 2.Show Admin                                  #" << endl;
	cout << "\t\t\t#                 3.Update Admin                                #" << endl;
	cout << "\t\t\t#                 4.Delete Admin                                #" << endl;
	cout << "\t\t\t#                 0.Return                                      #" << endl;
	cout << "\t\t\t#################################################################" << endl;
	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				if (y > 0) {
					y--;
				}
				break;
			case KEY_DOWN:
				if (y < 4) {
					y++;
				}
				break;
			default:
				break;
			}
		}
		system("cls");

		if (y == 0) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ADMIN" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         ADMIN                                 #" << endl;
			cout << "\t\t\t#               ->1.Register Admin                              #" << endl;
			cout << "\t\t\t#                 2.Show Admin                                  #" << endl;
			cout << "\t\t\t#                 3.Update Admin                                #" << endl;
			cout << "\t\t\t#                 4.Delete Admin                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 1) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ADMIN" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         ADMIN                                 #" << endl;
			cout << "\t\t\t#                 1.Register Admin                              #" << endl;
			cout << "\t\t\t#               ->2.Show Admin                                  #" << endl;
			cout << "\t\t\t#                 3.Update Admin                                #" << endl;
			cout << "\t\t\t#                 4.Delete Admin                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 2) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ADMIN" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         ADMIN                                 #" << endl;
			cout << "\t\t\t#                 1.Register Admin                              #" << endl;
			cout << "\t\t\t#                 2.Show Admin                                  #" << endl;
			cout << "\t\t\t#               ->3.Update Admin                                #" << endl;
			cout << "\t\t\t#                 4.Delete Admin                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 3) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ADMIN" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         ADMIN                                 #" << endl;
			cout << "\t\t\t#                 1.Register Admin                              #" << endl;
			cout << "\t\t\t#                 2.Show Admin                                  #" << endl;
			cout << "\t\t\t#                 3.Update Admin                                #" << endl;
			cout << "\t\t\t#               ->4.Delete Admin                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 4) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ADMIN" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         ADMIN                                 #" << endl;
			cout << "\t\t\t#                 1.Register Admin                              #" << endl;
			cout << "\t\t\t#                 2.Show Admin                                  #" << endl;
			cout << "\t\t\t#                 3.Update Admin                                #" << endl;
			cout << "\t\t\t#                 4.Delete Admin                                #" << endl;
			cout << "\t\t\t#               ->0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}

	}

	if (y == 0) {
		system("cls");
		adminRegister();
	}
	else if (y == 1) {
		system("cls");
		showAllAdmin();
	}
	else if (y == 2) {
		system("cls");
		updateAdmin();
	}
	else if (y == 3) {
		system("cls");
		deleteAdmin();
	}
	else if (y == 4) {
		system("cls");
		return;
	}
	goto START;

}

//MEMBER

int lastMemberID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from member");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}
	
}

int firstMemberID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MIN(NO) from member");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

void updateMembershipTime() {
	
	MemberManager memberManager;
	memberManager.updateMembershipTime();
	
}

void memberRegister()
{



	
	string ID = "M0319000";
	string lastID = to_string(lastMemberID() + 1);
	int k = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (i > (ID.size() - 1) - lastID.size()) {
			ID[i] = lastID[k++];
		}
	}

	MNAME:
	Member* newMember = new Member();
	system("cls");
	cout << "\t\t\t\t\t Maximun character is 30"<<endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  MEMBER REGISTER			" << endl;
	cout << "\t\t\t 	Name			: ";

	newMember->NO = lastMemberID() + 1;
	newMember->memberID = ID;
	
	
	getline(cin, newMember->name);
	if (newMember->name == "0") {
		return;
	}
	if (newMember->name.size() > 30) {
		cout<<"\t\t\t\t\t MAX CHARACTER IS 30" << endl;
		system("pause");
		goto MNAME;
	}
	else if (newMember->name.size() == 0) {
		cout << "\t\t\t\t\t PLEASE INSERT SOMETHING" << endl;
		system("pause");
		goto MNAME;
	}


MIC:
	system("cls");
	cout << "\t\t\t\t\t Put your IC number" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  MEMBER REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newMember->name << endl;
	cout << "\t\t\t 	IC Number		: ";

	getline(cin, newMember->icNumber);
	if (newMember->icNumber == "0") {
		return;
	}
	if (newMember->icNumber.size() != 12) {
		cout << "\n\t\t\t\tPASSWORD IS NOT SAME" << endl;
		goto MIC;
	}


	MPASSWORD:
	system("cls");
	cout << "\t\t\t\t\t Make sure to remember your password" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  MEMBER REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newMember->name << endl;
	cout << "\t\t\t 	IC Number		: "<< newMember->icNumber<<endl;
	cout << "\t\t\t 	Password		: ";
	
	getline(cin, newMember->password);
	if (newMember->password == "0") {
		return;
	}

	system("cls");
	cout << "\t\t\t\t\t Type again your password" << endl<<endl;
	
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  MEMBER REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newMember->name << endl;
	cout << "\t\t\t 	IC Number		: " << newMember->icNumber << endl;
	cout << "\t\t\t 	Password		: " << "***..." << endl;
	
	cout << "\n\n\t\t\tConfirm Password : " ;
	
	string cpass;
	getline(cin, cpass);
	if (cpass != newMember->password) {
		system("cls");
		cout << "\t\t\t\t\t !!!!!!!" << endl<<endl;
		
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			  MEMBER REGISTER			" << endl;
		cout << "\t\t\t 	Name			: " << newMember->name << endl;
		cout << "\t\t\t 	IC Number		: " << newMember->icNumber << endl;
		cout << "\t\t\t 	Password		: " << "***..." << endl;

		cout << "\n\n\t\t\tConfirm Password : ***..."<<endl;
		cout << "\n\t\t\t\tPASSWORD IS NOT SAME"<< endl;
		system("pause");
		goto MPASSWORD;

	}

	MNOTEL:
	system("cls");
	cout << "\t\t\t\t\t Insert a valid phone number" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  MEMBER REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newMember->name << endl;
	cout << "\t\t\t 	IC Number		: " << newMember->icNumber << endl;
	cout << "\t\t\t 	Password		: " << "***..." << endl;
	cout << "\t\t\t 	noTel			: " ;

	bool check = false;
	getline(cin, newMember->noTel);
	if (newMember->noTel == "0") {
		return;
	}
	if (isdigit(newMember->noTel[0]) && newMember->noTel[0] =='0') {
		int intNoPhone = stoi(newMember->noTel);
		newMember->noTel = "0" + to_string(intNoPhone);
	}
	else { check = true; }
	if (newMember->noTel.size() != 10 || check ) {
		cout << "\t\t\t\t\t INVALID TELEPHONE NUMBER" << endl;
		cout << "\t\t\t\t\t MUST BE DIGIT" << endl;
		system("pause");
		goto MNOTEL;
	}

	
	newMember->membershipTime = "30";

	MemberManager memberManage;
	int status = memberManage.insertMember(newMember);

	if (status != 0)
		cout << "\n\n\t\t\tSuccessfully added a new member with no ID = " << ID  << endl << endl;
	else
		cout << "Unable to add a new member." << endl;
	delete newMember;
	system("pause");
}

string memberLogin()
{
	Member* login = new Member;
	bool check = true;
	while (check) {

		system("CLS");
		
		MemberManager Manager;
		
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN MEMBER			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Member ID : ";



		getline(cin, login->memberID);
		if (login->memberID == "0") {
			return "0";
		}
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN MEMBER			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Member ID : "<<login->memberID<<endl;
		cout << "\t\t\t			Password  : ";

		string pass;
		int i = 0;
		char a;
		for (i = 0;;) {
			a = _getch();
			if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {

				pass += a;
				++i;
				cout << "*";

			}
			if (a == '\b' && i >= 1) {
				cout << "\b \b";
				--i;
			}
			if (a == '\r') {
				break;
			}

		}

		
		login->password = pass;
		if (login->password == "0") {
			return "0";
		}

		if (Manager.login(login))
		{
			check = false;
		}
		else
		{
			check = true;
		}
	}
	return login->memberID;
}

void showAllMember()
{
	if (lastMemberID() == 0) {
		system("cls");
		cout << endl << endl;
		cout << setw(8) << "Member ID" << setw(40) << "Member Name" << setw(20) << "IC Number " << setw(20) << "Telephone Number" << setw(25) << "Membership Time(day)" << endl;
		cout << "==================================================================================================================" << endl << endl;
		cout << "\t\t\t DATA IS EMPTY" << endl << endl;
		cout << "==================================================================================================================" << endl << endl;
		system("pause");
		return;
	}
	MemberManager Member;
	Member.showAllMember();
	system("pause");
	
}

void updateMember() {

START:
	system("cls");
	MemberManager memberManager;
	Member* member = new Member();
	
	int y = 1;
	int c = 0;

			y = memberManager.searchMember(lastMemberID());
			if (y == 0) {
				return;
			}
			
	int a = y;
	AGAIN:
	
	member = memberManager.selectMemberNo(a);
	system("cls");
	cout << "\t\t\t\tChoose Data to Udate.Press 0 to return" << endl << endl;
	cout << endl;
	cout << "\t==============================================================================================" << endl << endl;
	cout << "\t\t\t\t->Name			: " << member->name << endl;
	cout << "\t\t\t\t  Password		: ***...." << endl;
	cout << "\t\t\t\t  Telephone Number	: " << member->noTel << endl;
	cout << "\t\t\t\t  Membership Time	: " << member->membershipTime << endl;
	cout << "\n\t==============================================================================================" << endl << endl;

	y = 0;
	bool check = true;
	while (check) {
		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			
			y--;
			
			break;
		case KEY_DOWN:
			
			y++;
			
			break;
		case '\r':
			check = false;
		default:
			// not arrow
			break;
		}
		if (c == '0') {
			goto START;
		}
		if (y < 0) {
			y = 0;
			
		}
		if (y > 3) {
			y = 3;
			
		}
		if (y == 0) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Udate.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t->Name			: " << member->name << endl;
			cout << "\t\t\t\t  Password		: ***...." << endl;
			cout << "\t\t\t\t  Telephone Number	: " << member->noTel << endl;
			cout << "\t\t\t\t  Membership Time	: " << member->membershipTime << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else if (y == 1) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Udate.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: " << member->name << endl;
			cout << "\t\t\t\t->Password		: ***...." << endl;
			cout << "\t\t\t\t  Telephone Number	: " << member->noTel << endl;
			cout << "\t\t\t\t  Membership Time	: " << member->membershipTime << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else if (y == 2) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Udate.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: " << member->name << endl;
			cout << "\t\t\t\t  Password		: ***...." << endl;
			cout << "\t\t\t\t->Telephone Number	: " << member->noTel << endl;
			cout << "\t\t\t\t  Membership Time	: " << member->membershipTime << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else if (y == 3) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Udate.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: " << member->name << endl;
			cout << "\t\t\t\t  Password		: ***...." << endl;
			cout << "\t\t\t\t  Telephone Number	: " << member->noTel << endl;
			cout << "\t\t\t\t->Membership Time	: " << member->membershipTime << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else{}
		
	}
	system("cls");
	string update;
	if (y == 0) {
		cout << "\t\t\t\tUpdate Name" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Name			: ";
		getline(cin, update);
	}
	else if (y == 1) {
		cout << "\t\t\t\tUpdate Password" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Password			: ";
		getline(cin, update);
	}
	else if (y == 2) {
		cout << "\t\t\t\tUpdate Telephone Number" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Telephone Number		: ";
		getline(cin, update);
	}
	else if (y == 3) {
		cout << "\t\t\t\tUpdate Membership Time" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Membership Time		: ";
		getline(cin, update);
	}
	if (memberManager.updateMember(member->memberID, to_string(y), update)) {
		cout << "\t\t\t\tUPDATE SUCCESS"<<endl;
	}
	else {
		cout << "\t\t\t\tUPDATE FAILED"<<endl;
	}
	system("pause");
	goto AGAIN;
	
}

void deleteMember()
{
	
	MemberManager memberManager;
	Member* member = new Member();

	int y = 1;

	y = memberManager.searchMember(lastMemberID());
	if (y == 0) {
		return;
	}


	NOOPTION:
	member = memberManager.selectMemberNo(y);
	system("cls");
	cout << "\t\t\t " << endl << endl;
	cout << "\t" << setw(8) << "Member ID" << setw(40) << "Member Name" << setw(20) << "Telephone Number" << setw(30) << "Membership Time(day)" << endl;
	cout << "\t===================================================================================================" << endl << endl;
	cout << "\t  "<< member->memberID << setw(40) << member->name << setw(20) << member->noTel << setw(20) << member->membershipTime << endl;
	cout << "\n\t===================================================================================================" << endl << endl;
	cout << "\n\n\t\t\t\t CONFIRM DELETE (Y/N) : " ;
	string option;
	getline(cin, option);
	if (option == "Y" || option == "y") {
		int status = memberManager.deleteMember(member->memberID);
		if (status) {
			system("cls");
			cout << "\t\t\t " << endl << endl;
			cout << "\tMember ID" << setw(40) << "Member Name" << setw(20) << "Telephone Number" << setw(30) << "Membership Time(day)" << endl;
			cout << "\t===================================================================================================" << endl << endl;
			cout << "\n\t===================================================================================================" << endl << endl;
			cout << "\n\n\t\t\t\tDELETE SUCCEEDED" << endl;
		}
		else {
			system("cls");
			cout << "\t\t\t\t " << endl << endl;
			cout << "\tMember ID" << setw(40) << "Member Name" << setw(20) << "Telephone Number" << setw(30) << "Membership Time(day)" << endl;
			cout << "\t===================================================================================================" << endl << endl;
			cout << "  " << member->memberID << setw(40) << member->name << setw(20) << member->noTel << setw(20) << member->membershipTime << endl;
			cout << "\n\t===================================================================================================" << endl << endl;
			cout << "\n\n\t\t\t\tDELETE FAILED" << endl;
		}
		system("pause");
	}
	else if (option == "N" || option == "n") {
		
	}
	else {
		cout << "\n\t\t\tINSERT OPTION" << endl;
		system("pause");
		goto NOOPTION;
	}
	
	deleteMember();
}

void memberMastery()
{
	START:
		system("CLS");
		int c, y = 0 ;
		bool check = true;

		cout << endl << endl;
		cout << "\t\t\tMENU > MEMBER ENTRY" << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t#			  MEMBER ENTRY				#" << endl;
		cout << "\t\t\t#		->1.Add Member					#" << endl;
		cout << "\t\t\t#		  2.Update Member				#" << endl;
		cout << "\t\t\t#		  3.Show All Members				#" << endl;
		cout << "\t\t\t#		  4.Delete Member				#" << endl;
		cout << "\t\t\t#		  0.Return					#" << endl;
		cout << "\t\t\t#################################################################" << endl;
		while (check)
		{

			int c = _getch();
			if (c == '\r') {
				check = false;
			}
			if (c == 224) {

				int key = _getch();


				switch ((key)) {
				case KEY_UP:
					if (y > 0) {
						y--;
					}
					break;
				case KEY_DOWN:
					if (y < 4) {
						y++;
					}
					break;
				default:
					break;
				}
			}
			system("cls");

			if (y == 0) {
				cout << endl << endl;
				cout << "\t\t\tMENU > MEMBER ENTRY" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  MEMBER ENTRY				#" << endl;
				cout << "\t\t\t#		->1.Add Member					#" << endl;
				cout << "\t\t\t#		  2.Update Member				#" << endl;
				cout << "\t\t\t#		  3.Show All Members				#" << endl;
				cout << "\t\t\t#		  4.Delete Member				#" << endl;
				cout << "\t\t\t#		  0.Return					#" << endl;
				cout << "\t\t\t#################################################################" << endl;
			}
			else if (y == 1) {
				cout << endl << endl;
				cout << "\t\t\tMENU > MEMBER ENTRY" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  MEMBER ENTRY				#" << endl;
				cout << "\t\t\t#		  1.Add Member					#" << endl;
				cout << "\t\t\t#		->2.Update Member				#" << endl;
				cout << "\t\t\t#		  3.Show All Members				#" << endl;
				cout << "\t\t\t#		  4.Delete Member				#" << endl;
				cout << "\t\t\t#		  0.Return					#" << endl;
				cout << "\t\t\t#################################################################" << endl;
			}
			else if (y == 2) {
				cout << endl << endl;
				cout << "\t\t\tMENU > MEMBER ENTRY" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  MEMBER ENTRY				#" << endl;
				cout << "\t\t\t#		  1.Add Member					#" << endl;
				cout << "\t\t\t#		  2.Update Member				#" << endl;
				cout << "\t\t\t#		->3.Show All Members				#" << endl;
				cout << "\t\t\t#		  4.Delete Member				#" << endl;
				cout << "\t\t\t#		  0.Return					#" << endl;
				cout << "\t\t\t#################################################################" << endl;
			}
			else if (y == 3) {
				cout << endl << endl;
				cout << "\t\t\tMENU > MEMBER ENTRY" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  MEMBER ENTRY				#" << endl;
				cout << "\t\t\t#		  1.Add Member					#" << endl;
				cout << "\t\t\t#		  2.Update Member				#" << endl;
				cout << "\t\t\t#		  3.Show All Members				#" << endl;
				cout << "\t\t\t#		->4.Delete Member				#" << endl;
				cout << "\t\t\t#		  0.Return					#" << endl;
				cout << "\t\t\t#################################################################" << endl;
			}
			else if (y == 4) {
				cout << endl << endl;
				cout << "\t\t\tMENU > MEMBER ENTRY" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  MEMBER ENTRY				#" << endl;
				cout << "\t\t\t#		  1.Add Member					#" << endl;
				cout << "\t\t\t#		  2.Update Member				#" << endl;
				cout << "\t\t\t#		  3.Show All Members				#" << endl;
				cout << "\t\t\t#		  4.Delete Member				#" << endl;
				cout << "\t\t\t#		->0.Return					#" << endl;
				cout << "\t\t\t#################################################################" << endl;
			}
			else {

			}

		}
		
		if (y == 0) {
			system("cls");
			memberRegister();
		}
		else if (y == 1) {
			system("cls");
			updateMember();
		}
		else if (y == 2) {
			system("cls");
			showAllMember();
		}
		else if (y == 3) {
			system("cls");
			deleteMember();
		}
		else if (y == 4) {
			system("cls");
			return;
		}
		else {

		}
		goto START;
}

int checkMemberTime(string ID) {

	MemberManager memberManager;
	
	return memberManager.checkMemberTime(ID);


}


//COMPUTERS

int lastComputerID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from computer");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}
	
}

int lastAvailableComputerID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from computer where status = 'available'");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

int lastUnavailableComputerID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from computer where status = 'unavailable'");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

int firstComputerID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MIN(NO) from computer");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

int firstAvailableComputerID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MIN(NO) from computer where status = 'available'");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

int firstUnavailableComputerID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MIN(NO) from computer where status = 'unavailable'");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

void addComputer()
{
	system("CLS");
	cout << "TAMBAH COMPUTER" << endl;
	string ID = "PC0319000";
	string lastID = to_string(lastComputerID() + 1);
	int k = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (i > (ID.size() - 1) - lastID.size()) {
			ID[i] = lastID[k++];
		}
	}

	Computer* newComputer = new Computer();

	newComputer->NO = lastComputerID() + 1;
	newComputer->computerID =  ID ;
	newComputer->status = "available";



	ComputerManager computerManage;
	int status = computerManage.insertComputer(newComputer);

	if (status) {
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t#			   SUCCEEDED				#" << endl;
		cout << "\t\t\t#			New Computer ID				#" << endl;
		cout << "\t\t\t#			+-------------+				#" << endl;
		cout << "\t\t\t#			|  "<<ID<<"  |				#" << endl;
		cout << "\t\t\t#			+-------------+				#" << endl;
		cout << "\t\t\t#								#" << endl;
		cout << "\t\t\t#################################################################" << endl<<endl;
	}
	else {
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t#			    FAILED					#" << endl;
		cout << "\t\t\t#			!!!!!!!!!!!!!!!				#" << endl;
		cout << "\t\t\t#			+-------------+				#" << endl;
		cout << "\t\t\t#			|!!!!!!!!!!!!!|				#" << endl;
		cout << "\t\t\t#			+-------------+				#" << endl;
		cout << "\t\t\t#								#" << endl;
		cout << "\t\t\t#################################################################" << endl<<endl;
	}
	delete newComputer;
	system("pause");
}

void showAllComputer()
{
	if (lastComputerID() == 0) {
		cout << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		
		

			cout << "\t\t\t\t|	   EMPTY     	  |" << endl;

		
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << endl;
		system("pause");
		return;
	}
	ComputerManager computer;
	computer.showAllComputer();
	cout << endl;
	system("pause");
}

void deleteComputer()
{
	system("cls");
	ComputerManager computerManager;
	Computer* computer = new Computer();
	bool check = true;
	int y = 1;
	int c = 0;

	vector <string> arrow;
	for (int i = 0; i <= lastAvailableComputerID() + 1; i++) {
		arrow.push_back("  ");
	}
	arrow[firstAvailableComputerID()] = "->";
	

	if (lastAvailableComputerID() == 0) {
		cout << "\t\t\tCan only delete computer that not in use" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		cout << "\t\t\t\t|	   EMPTY     	  |" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "\t\t\tCan only delete computer that not in use" << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
	cout << "\t\t\t\t|=========================|" << endl;
	for(int i = 0 ;i<=lastComputerID();i++)
	{
		computer = computerManager.selectComputerNo(i);
		if (computer != 0 && computer->status == "available") {
			
			cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
		}
	}
	cout << "\t\t\t\t+-------------------------+" << endl;


	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
		case KEY_UP:
			arrow[y] = "  ";
			y--;
			if (y > firstAvailableComputerID()) {
				computer = computerManager.selectComputerNo(y);
				while (computer == 0 || computer->status == "unavailable") {
					y--;
					computer = computerManager.selectComputerNo(y);
				}
			}
			arrow[y] = "->";
			break;
		case KEY_DOWN:
			arrow[y] = "  ";
			y++;
			if (y < lastAvailableComputerID()) {
				computer = computerManager.selectComputerNo(y);
				while (computer == 0 || computer->status == "unavailable") {
					y++;
					computer = computerManager.selectComputerNo(y);
				}
			}
			arrow[y] = "->";

			break;
	
		default:
			// not arrow
			break;
		}
	}
		if (c == '0') { return; }

		if (y < firstAvailableComputerID()) {
			y = lastAvailableComputerID();
			arrow[y] = "->";
		}
		if (y > lastAvailableComputerID()) {
			y = firstAvailableComputerID();
			arrow[y] = "->";
		}



		system("cls");
		cout << "\t\t\tCan only delete computer that not in use"<<endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		for (int i = 0; i <= lastComputerID(); i++)
		{
			computer = computerManager.selectComputerNo(i);
			if (computer != 0 && computer->status == "available") {
				
				cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
			}
		}
		cout << "\t\t\t\t+-------------------------+" << endl;

	}
NOOPTION1:
	computer = computerManager.selectComputerNo(y);
	system("cls");
	cout << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
	cout << "\t\t\t\t|=========================|" << endl;
	cout << "\t\t\t\t|" << computer->computerID << setw(16) << computer->status << "|" << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\n\n\t\t\t CONFIRM DELETE (Y/N) : ";
	string option;
	getline(cin, option);
	if (option == "Y" || option == "y") {
		int status = computerManager.deleteComputer(computer->computerID);
		if (status) {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
			cout << "\t\t\t\t|=========================|" << endl;
			cout << "\t\t\t\t|                         |" << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\n\n\t\t\tDELETE SUCCEEDED" << endl;
		}
		else {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
			cout << "\t\t\t\t|=========================|" << endl;
			cout << "\t\t\t\t|" << computer->computerID << setw(16) << computer->status << "|" << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\n\n\t\t\tDELETE FAILED" << endl;
		}
		system("pause");
	}
	else if (option == "N" || option == "n") {

	}
	else {
		cout << "\n\t\t\tINSERT OPTION" << endl;
		system("pause");
		goto NOOPTION1;
	}

	deleteComputer();
}

void computerMastery()
{
START:
	system("CLS");
	int c, y = 0;
	bool check = true;

	cout << endl << endl;
	cout << "\t\t\tMENU > COMPUTER ENTRY" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			  COMPUTER ENTRY			#" << endl;
	cout << "\t\t\t#		->1.Add Computer				#" << endl;
	cout << "\t\t\t#		  2.Show All Computer				#" << endl;
	cout << "\t\t\t#		  3.Delete Computer				#" << endl;
	cout << "\t\t\t#		  0.Return					#" << endl;
	cout << "\t\t\t#								#" << endl;
	cout << "\t\t\t#################################################################" << endl;
	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				if (y > 0) {
					y--;
				}
				break;
			case KEY_DOWN:
				if (y < 3) {
					y++;
				}
				break;


			default:
				break;
			}
		}
		system("cls");

		if (y == 0) {
			cout << endl << endl;
			cout << "\t\t\tMENU > COMPUTER ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			  COMPUTER ENTRY			#" << endl;
			cout << "\t\t\t#		->1.Add Computer				#" << endl;
			cout << "\t\t\t#		  2.Show All Computer				#" << endl;
			cout << "\t\t\t#		  3.Delete Computer				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#								#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 1) {
			cout << endl << endl;
			cout << "\t\t\tMENU > COMPUTER ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			  COMPUTER ENTRY			#" << endl;
			cout << "\t\t\t#		  1.Add Computer				#" << endl;
			cout << "\t\t\t#		->2.Show All Computer				#" << endl;
			cout << "\t\t\t#		  3.Delete Computer				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#								#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 2) {
			cout << endl << endl;
			cout << "\t\t\tMENU > COMPUTER ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			  COMPUTER ENTRY			#" << endl;
			cout << "\t\t\t#		  1.Add Computer				#" << endl;
			cout << "\t\t\t#		  2.Show All Computer				#" << endl;
			cout << "\t\t\t#		->3.Delete Computer				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#								#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 3) {
			cout << endl << endl;
			cout << "\t\t\tMENU > COMPUTER ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			  COMPUTER ENTRY			#" << endl;
			cout << "\t\t\t#		  1.Add Computer				#" << endl;
			cout << "\t\t\t#		  2.Show All Computer				#" << endl;
			cout << "\t\t\t#		  3.Delete Computer				#" << endl;
			cout << "\t\t\t#		->0.Return					#" << endl;
			cout << "\t\t\t#								#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else {

		}

	}

	if (y == 0) {
		system("cls");
		addComputer();
	}
	else if (y == 1) {
		system("cls");
		showAllComputer();
	}
	else if (y == 2) {
		system("cls");
		deleteComputer();
	}
	else if (y == 3) {
		system("cls");
		return;
	}
	else {

	}
	goto START;
}


//ALLOCATING

void checkTime() {
	AllocatingManager allocatingManager;
	allocatingManager.checkTime();
}

void addTime() {

	system("cls");
	AllocatingManager allocatingManager;
	
	ComputerManager computerManager;
	Computer* computer = new Computer();
	bool check = true;
	int y = 1;
	int c = 0;

	vector <string> arrow;
	for (int i = 0; i <= lastUnavailableComputerID() + 1; i++) {
		arrow.push_back("  ");
	}
	arrow[firstUnavailableComputerID()] = "->";


	if (lastUnavailableComputerID() == 0) {
		cout << "\t\t\tCHOOSE PC TO ADD TIME" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		cout << "\t\t\t\t|	   EMPTY     	  |" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "\t\t\tCHOOSE PC TO ADD TIME" << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
	cout << "\t\t\t\t|=========================|" << endl;
	for (int i = 0; i <= lastComputerID(); i++)
	{
		computer = computerManager.selectComputerNo(i);
		if (computer != 0 && computer->status == "unavailable") {

			cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
		}
	}
	cout << "\t\t\t\t+-------------------------+" << endl;


	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				arrow[y] = "  ";
				y--;
				if (y > firstUnavailableComputerID()) {
					computer = computerManager.selectComputerNo(y);
					while (computer == 0 || computer->status == "available") {
						y--;
						computer = computerManager.selectComputerNo(y);
					}
				}
				arrow[y] = "->";
				break;
			case KEY_DOWN:
				arrow[y] = "  ";
				y++;
				if (y < lastUnavailableComputerID()) {
					computer = computerManager.selectComputerNo(y);
					while (computer == 0 || computer->status == "available") {
						y++;
						computer = computerManager.selectComputerNo(y);
					}
				}
				arrow[y] = "->";

				break;
			case '\r':
				check = false;

			default:
				// not arrow
				break;
			}
		}
		if (c == '0') { return; }

		if (y < firstUnavailableComputerID()) {
			y = firstUnavailableComputerID();
			arrow[y] = "->";
		}
		if (y > lastUnavailableComputerID()) {
			y = lastUnavailableComputerID();
			arrow[y] = "->";
		}



		system("cls");
		cout << "\t\t\tCHOOSE PC TO ADD TIME" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		for (int i = 0; i <= lastComputerID(); i++)
		{
			computer = computerManager.selectComputerNo(i);
			if (computer != 0 && computer->status == "unavailable") {

				cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
			}
		}
		cout << "\t\t\t\t+-------------------------+" << endl;

	}
	computer = computerManager.selectComputerNo(y);
	check = true;
	y = 0;
	int x = 0;
	c = 0;
	string bar1 = "^", bar2;


	int ihour = 0, imin = 0;

	system("cls");
	cout << endl << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			   Time To Play				#" << endl;
	cout << "\t\t\t#								#" << endl;
	cout << "\t\t\t#			  					#" << endl;
	cout << "\t\t\t#			 " << ihour << " hour " << imin << " minutes 			#" << endl;
	cout << "\t\t\t#			 " << bar1 << "      " << bar2 << "				#" << endl;
	cout << "\t\t\t#			  					#" << endl;
	cout << "\t\t\t#################################################################" << endl;



	while (check)
	{

		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:

			if (x == 0 && ihour < 4) {
				ihour++;
			}
			else if (x == 1 && imin < 60) {
				imin++;
			}
			break;
		case KEY_DOWN:
			if (x == 0 && ihour > 0) {
				ihour--;
			}
			else if (x == 1 && imin > 0) {
				imin--;
			}
			y++;
			break;
		case KEY_LEFT:
			if (x > 0) {
				x--;
				bar2 = " ";
				bar1 = "^";
			}
			break;
		case KEY_RIGHT:
			if (x < 1) {
				x++;
				bar2 = "^";
				bar1 = " ";
			}
			break;
		case '\r':
			check = false;

		default:
			// not arrow
			break;
		}

		if (c == '0') {
			return;
		}





		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t#			   Time To Play				#" << endl;
		cout << "\t\t\t#								#" << endl;
		cout << "\t\t\t#			  					#" << endl;
		cout << "\t\t\t#			 " << ihour << " hour " << imin << " minutes 			#" << endl;
		cout << "\t\t\t#			 " << bar1 << "      " << bar2 << "				#" << endl;
		cout << "\t\t\t#			  					#" << endl;
		cout << "\t\t\t#################################################################" << endl;
	}

	
	int status = allocatingManager.addTime(computer->computerID, ihour, imin);
	if (status) {
		cout << "\t\t\t\t\tSUCCEEDED\n";
	}
	else {
		cout << "\t\t\t\t\tFAILED\n";
	}
	system("pause");
}

void stopPc() {

	checkTime();
	system("cls");
	AllocatingManager allocatingManager;

	ComputerManager computerManager;
	Computer* computer = new Computer();
	bool check = true;
	int y = 1;
	int c = 0;

	vector <string> arrow;
	for (int i = 0; i <= lastUnavailableComputerID() + 1; i++) {
		arrow.push_back("  ");
	}
	arrow[firstUnavailableComputerID()] = "->";


	if (lastUnavailableComputerID() == 0) {
		cout << "\t\t\t "<< endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		cout << "\t\t\t\t|	   EMPTY     	  |" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "\t\t\t" << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
	cout << "\t\t\t\t|=========================|" << endl;
	for (int i = 0; i <= lastComputerID(); i++)
	{
		computer = computerManager.selectComputerNo(i);
		if (computer != 0 && computer->status == "unavailable") {

			cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
		}
	}
	cout << "\t\t\t\t+-------------------------+" << endl;


	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				arrow[y] = "  ";
				y--;
				if (y > firstUnavailableComputerID()) {
					computer = computerManager.selectComputerNo(y);
					while (computer == 0 || computer->status == "available") {
						y--;
						computer = computerManager.selectComputerNo(y);
					}
				}
				arrow[y] = "->";
				break;
			case KEY_DOWN:
				arrow[y] = "  ";
				y++;
				if (y < lastUnavailableComputerID()) {
					computer = computerManager.selectComputerNo(y);
					while (computer == 0 || computer->status == "available") {
						y++;
						computer = computerManager.selectComputerNo(y);
					}
				}
				arrow[y] = "->";

				break;
			

			default:
				// not arrow
				break;
			}
		}
		if (c == '0') { return; }

		if (y < firstUnavailableComputerID()) {
			y = lastUnavailableComputerID();
			arrow[y] = "->";
		}
		if (y > lastUnavailableComputerID()) {
			y = firstUnavailableComputerID();
			arrow[y] = "->";
		}



		system("cls");
		cout << "\t\t\t" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		for (int i = 0; i <= lastComputerID(); i++)
		{
			computer = computerManager.selectComputerNo(i);
			if (computer != 0 && computer->status == "unavailable") {

				cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
			}
		}
		cout << "\t\t\t\t+-------------------------+" << endl;

	}

	computer = computerManager.selectComputerNo(y);
	NOOPTION2:
	system("cls");
	cout << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
	cout << "\t\t\t\t|=========================|" << endl;
	cout << "\t\t\t\t|" << computer->computerID << setw(16) << computer->status << "|" << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\n\n\t\t\t CONFIRM TO STOP (Y/N) : ";
	string option;
	getline(cin, option);
	if (option == "Y" || option == "y") {
		allocatingManager.stopPcUpdate(computer->computerID);
		int status = allocatingManager.stopPc(computer->computerID);
		
		if (status) {
			computerManager.updateComputerA(computer->computerID);
			system("cls");
			cout << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
			cout << "\t\t\t\t|=========================|" << endl;
			cout << "\t\t\t\t|                         |" << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\n\n\t\tSTOP SUCCEEDED" << endl;
		}
		else {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
			cout << "\t\t\t\t|=========================|" << endl;
			cout << "\t\t\t\t|" << computer->computerID << setw(16) << computer->status << "|" << endl;
			cout << "\t\t\t\t+-------------------------+" << endl;
			cout << "\n\n\t\tSTOP FAILED" << endl;
		}
		system("pause");
	}
	else if (option == "N" || option == "n") {

	}
	else {
		cout << "\n\t\t\tINSERT OPTION" << endl;
		system("pause");
		goto NOOPTION2;
	}



}

void printInformation()
{
	checkTime();

	ComputerManager computerManager;
	AllocatingManager allocatingManager;
	Computer* computer = new Computer();
	Allocating* allocating = new Allocating();
	
	
		
			this_thread::sleep_for(std::chrono::seconds(1));
			time_t now = time(0);
			tm* ltm = localtime(&now);
			time_t current = time(0);
			system("cls");

			cout << "\tComputer ID\t\tStatus\t\t\tUser ID\t\t\tTime left\tEnd Time" << endl;
			cout << "\t=================================================================================================" << endl << endl;
			for (int i = 1; i <= lastComputerID(); i++) {
				string sec, min, hour;

				computer = computerManager.selectComputerNo(i);
				if (computer != 0) {


					if (computer->status != "available") {
						

						allocating = allocatingManager.getComputer(computer->computerID);

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


						if (isec < ltm->tm_sec ) {
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

						

						cout << "\t"<<computer->computerID ;
						cout << "\t\t"<< computer->status;
						cout <<  "\t\t"<<allocating->userID  ;
						cout << "\t\t"<< rhour << ":" << rmin << ":" << rsec ;
						cout << "\t\t"<< allocating->endTime << endl<<endl;


					}
					else {
						cout <<"\t"<< computer->computerID;
						cout << "\t\t" << computer->status;
						cout << "\t\t--" ;
						cout << "\t\t\t--";
						cout << "\t\t--" << endl << endl;
					}



				}



			}
			cout << "\t\t\t\t\tpress 0 to return." << endl;

		
	
}

void allocatingToPc() {
	
	checkTime();
	system("CLS");
	string pcID;
	string userID;
	string choose;
	AllocatingManager allocatingManager;
	ComputerManager computerManager;
	Computer* computer = new Computer();
	Allocating* allocating = new Allocating();
	int c, y = 0;
	bool check = true;

	cout << "\t\t\t\t\t\t 0 to return"<<endl << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			Allocating To PC			#" << endl;
	cout << "\t\t\t#								#" << endl;
	cout << "\t\t\t#		-> 1. Member        2.Non-Member		#" << endl;
	cout << "\t\t\t#		  						#" << endl;
	cout << "\t\t\t#		  						#" << endl;
	cout << "\t\t\t#		  						#" << endl;
	cout << "\t\t\t#################################################################" << endl;
	while (check)
	{

		c = 0;



		switch ((c = _getch())) {
		case KEY_LEFT:
			if (y > 0) {
				y--;
			}
			break;
		case KEY_RIGHT:
			if (y < 1) {
				y++;
			}
			break;

		case '\r':
			check = false;
		default:
			break;
		}

		if (c == '0') { return; }

		system("cls");

		if (y == 0) {
			cout << "\t\t\t\t\t\t 0 to return" << endl << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating To PC			#" << endl;
			cout << "\t\t\t#								#" << endl;
			cout << "\t\t\t#		-> 1. Member        2.Non-Member		#" << endl;
			cout << "\t\t\t#		  						#" << endl;
			cout << "\t\t\t#		  						#" << endl;
			cout << "\t\t\t#		  						#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 1) {
			cout << "\t\t\t\t\t\t 0 to return" << endl << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating To PC			#" << endl;
			cout << "\t\t\t#								#" << endl;
			cout << "\t\t\t#		   1. Member     -> 2.Non-Member		#" << endl;
			cout << "\t\t\t#		  						#" << endl;
			cout << "\t\t\t#		  						#" << endl;
			cout << "\t\t\t#		  						#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else {

		}

	}
	system("cls");

	if (y == 0) {
		userID = memberLogin();
		
		if (userID == "0") {
			return;
		}
		if (!(checkMemberTime(userID))) {
			cout << "\n\n\t\t\t\t\tTHE MEMBERSHIP TIME IS NOT ACTIVE" << endl;
			system("pause");
			return;
		}
	}
	else if (y == 1) {
		bool invalid = true;
		while (invalid) {
			system("cls");
			cout << "\t\t\t\t\t " << endl;
			cout << "\t\t\t\t\t Input 0 to return" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t 			  NON-MEMBER REGISTER			" << endl;
			cout << "\t\t\t\t		IC : ";

			getline(cin, userID);
			if (userID == "0") {
				return;
			}
			if (userID.size() != 12) {
				cout << "\n\n\t\t\t\t\tINVALID IC" << endl;
				system("pause");
			}
			else {
				invalid = false;
			}
		}
	}


	system("cls");
	

	 check = true;
	 y = 1;
	 c = 0;

	vector <string> arrow;
	for (int i = 0; i <= lastAvailableComputerID() + 1; i++) {
		arrow.push_back("  ");
	}
	arrow[firstAvailableComputerID()] = "->";


	if (lastAvailableComputerID() == 0) {
		cout << "\t\t\tChoose computer to play" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		cout << "\t\t\t\t|	   EMPTY     	  |" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "\t\t\tChoose computer to play" << endl;
	cout << "\t\t\t\t+-------------------------+" << endl;
	cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
	cout << "\t\t\t\t|=========================|" << endl;
	for (int i = 0; i <= lastComputerID(); i++)
	{
		computer = computerManager.selectComputerNo(i);
		if (computer != 0 && computer->status == "available") {

			cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
		}
	}
	cout << "\t\t\t\t+-------------------------+" << endl;


	while (check)
	{

		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			arrow[y] = "  ";
			y--;
			if (y > firstAvailableComputerID()) {
				computer = computerManager.selectComputerNo(y);
				while (computer == 0 || computer->status == "unavailable") {
					y--;
					computer = computerManager.selectComputerNo(y);
				}
			}
			arrow[y] = "->";
			break;
		case KEY_DOWN:
			arrow[y] = "  ";
			y++;
			if (y < lastAvailableComputerID()) {
				computer = computerManager.selectComputerNo(y);
				while (computer == 0 || computer->status == "unavailable") {
					y++;
					computer = computerManager.selectComputerNo(y);
				}
			}
			arrow[y] = "->";

			break;
		case '\r':
			check = false;

		default:
			// not arrow
			break;
		}

		if (c == '0') { return; }

		if (y < firstAvailableComputerID()) {
			y = firstAvailableComputerID();
			arrow[y] = "->";
		}
		if (y > lastAvailableComputerID()) {
			y = lastAvailableComputerID();
			arrow[y] = "->";
		}



		system("cls");
		cout << "\t\t\tChoose computer to play" << endl;
		cout << "\t\t\t\t+-------------------------+" << endl;
		cout << "\t\t\t\t|Computer ID" << setw(15) << "Status  |" << endl;
		cout << "\t\t\t\t|=========================|" << endl;
		for (int i = 0; i <= lastComputerID(); i++)
		{
			computer = computerManager.selectComputerNo(i);
			if (computer != 0 && computer->status == "available") {

				cout << "\t\t\t      " << arrow[i] << "|" << computer->computerID << setw(16) << computer->status << "|" << endl;
			}
		}
		cout << "\t\t\t\t+-------------------------+" << endl;

	}
	computer = computerManager.selectComputerNo(y);

			

	
	string endTime;
	string semi = ":";

	time_t now = time(0);
	tm* ltm = localtime(&now);
	time_t current = time(0);
	int sec = ltm->tm_sec, min = ltm->tm_min, hour = ltm->tm_hour;

	 check = true;
	 y = 0;
	 int x = 0;
	 c = 0;
	 string bar1 = "^", bar2;
	

	int ihour = 0, imin = 0;

	system("cls");
	cout << endl << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			   Time To Play				#" << endl;
	cout << "\t\t\t#								#" << endl;
	cout << "\t\t\t#			  					#" << endl;
	cout << "\t\t\t#			 "<<ihour<<" hour "<<imin<<" minutes 			#" << endl;
	cout << "\t\t\t#			 "<<bar1<<"      "<<bar2<<"				#" << endl;
	cout << "\t\t\t#			  					#" << endl;
	cout << "\t\t\t#################################################################" << endl;



	while (check)
	{

		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			
			if (x == 0 && ihour < 4) {
				ihour++;
			}
			else if (x == 1 && imin < 60) {
				imin++;
			}
			break;
		case KEY_DOWN:
			if (x == 0 && ihour > 0) {
				ihour--;
			}
			else if (x == 1 && imin > 0) {
				imin--;
			}
			y++;
			break;
		case KEY_LEFT:
			if (x > 0) {
				x--;
				bar2 = " ";
				bar1 = "^";
			}
			break;
		case KEY_RIGHT:
			if (x < 1) {
				x++;
				bar2 = "^";
				bar1 = " ";
			}
			break;
		case '\r':
			check = false;

		default:
			// not arrow
			break;
		}

		if (c == '0') {
			return;
		}





		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t#			   Time To Play				#" << endl;
		cout << "\t\t\t#								#" << endl;
		cout << "\t\t\t#			  					#" << endl;
		cout << "\t\t\t#			 " << ihour << " hour " << imin << " minutes 			#" << endl;
		cout << "\t\t\t#			 " << bar1 << "      " << bar2 << "				#" << endl;
		cout << "\t\t\t#			  					#" << endl;
		cout << "\t\t\t#################################################################" << endl;
	}

	min += imin;
	hour += ihour;
	if (min > 59) {
		min = min - 60;
		hour++;
	}

	endTime = to_string(hour) +semi+ to_string(min) +semi+ to_string(sec);
	string totalTime = to_string(ihour) + ":" + to_string(imin) + ":0";
	string startTime = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
	allocating->computerID = computer->computerID;
	allocating->userID = userID;
	allocating->endTime = endTime;
	allocating->totalTime = totalTime;
	allocating->startTime = startTime;

	allocatingManager.allocating(allocating);
	computerManager.updateComputerU(computer->computerID);
	system("cls");
	cout << endl << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			   Done Allocating			#" << endl;
	cout << "\t\t\t#								#" << endl;
	cout << "\t\t\t#			PC :"<<computer->computerID<<" 				#" << endl;
	cout << "\t\t\t#			Time :" << ihour << " hour " << imin << " minutes			#" << endl;
	cout << "\t\t\t#			 					#" << endl;
	cout << "\t\t\t#			  					#" << endl;
	cout << "\t\t\t#################################################################" << endl<<endl;
	system("pause");
}

void allocatingMastery()
{
	checkTime();
START:
	system("CLS");
	int c, y = 0;
	bool check = true;

	cout << endl << endl;
	cout << "\t\t\tMENU > ALLOCATING ENTRY" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			Allocating Entry			#" << endl;
	cout << "\t\t\t#		->1.Allocating to Computer			#" << endl;
	cout << "\t\t\t#		  2.Add Time					#" << endl;
	cout << "\t\t\t#		  3.Stop Pc					#" << endl;
	cout << "\t\t\t#		  4.Print Information				#" << endl;
	cout << "\t\t\t#		  0.Return					#" << endl;
	cout << "\t\t\t#################################################################" << endl;
	while (check)
	{
		checkTime();

		int c = _getch();
		if (c == '\r') {
			 check = false;;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				if (y > 0) {
					y--;
				}
				break;
			case KEY_DOWN:
				if (y < 4) {
					y++;
				}
				break;
			default:
				break;
			}
		}
		system("cls");

		if (y == 0) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ALLOCATING ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating Entry			#" << endl;
			cout << "\t\t\t#		->1.Allocating to Computer			#" << endl;
			cout << "\t\t\t#		  2.Add Time					#" << endl;
			cout << "\t\t\t#		  3.Stop Pc					#" << endl;
			cout << "\t\t\t#		  4.Print Information				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 1) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ALLOCATING ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating Entry			#" << endl;
			cout << "\t\t\t#		  1.Allocating to Computer			#" << endl;
			cout << "\t\t\t#		->2.Add Time					#" << endl;
			cout << "\t\t\t#		  3.Stop Pc					#" << endl;
			cout << "\t\t\t#		  4.Print Information				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 2) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ALLOCATING ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating Entry			#" << endl;
			cout << "\t\t\t#		  1.Allocating to Computer			#" << endl;
			cout << "\t\t\t#		  2.Add Time					#" << endl;
			cout << "\t\t\t#		->3.Stop Pc					#" << endl;
			cout << "\t\t\t#		  4.Print Information				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if (y == 3) {
			cout << endl << endl;
			cout << "\t\t\tMENU > ALLOCATING ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating Entry			#" << endl;
			cout << "\t\t\t#		  1.Allocating to Computer			#" << endl;
			cout << "\t\t\t#		  2.Add Time					#" << endl;
			cout << "\t\t\t#		  3.Stop Pc					#" << endl;
			cout << "\t\t\t#		->4.Print Information				#" << endl;
			cout << "\t\t\t#		  0.Return					#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else if(y ==4){
			cout << endl << endl;
			cout << "\t\t\tMENU > ALLOCATING ENTRY" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#			Allocating Entry			#" << endl;
			cout << "\t\t\t#		  1.Allocating to Computer			#" << endl;
			cout << "\t\t\t#		  2.Add Time					#" << endl;
			cout << "\t\t\t#		  3.Stop Pc					#" << endl;
			cout << "\t\t\t#		  4.Print Information				#" << endl;
			cout << "\t\t\t#		->0.Return					#" << endl;
			cout << "\t\t\t#################################################################" << endl;
		}
		else {

		}

	}

	if (y == 0) {
		system("cls");
		checkTime();
		allocatingToPc();
	}
	else if (y == 1) {
		system("cls");
		checkTime();
		addTime();
	}
	else if (y == 2) {
		system("cls");
		stopPc();
	}
	else if (y == 3) {
		while (1) {
			char a = ' ';
			a = input();
			printInformation();
			if (a == '0') {
				break;
			}
		}
		system("cls");
	}
	else if (y == 4) {
		system("cls");
		return;
	}
	else {

	}
	goto START;
}


//PYAYMENTS

void paying() {

START:
	system("cls");
	PaymentManager paymentManager;
	Payment* payment = new Payment();
	int y = paymentManager.showUnpaid();
	if (y == 0) {
		return;
	}

	payment = paymentManager.selectPaymentNo(y);

	
	char a ;
	string money = "";
	int i = 0;
	bool dot = true;
	while (true) {
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t                             PAYING                                 " << endl;
		cout << "\t\t\t         User ID/IC : " << payment->userID << setw(14) << "Pc ID : " << payment->computerID << setw(10) << "            " << endl;
		cout << "\t\t\t                  Play Time   : " << payment->totalTime << setw(28) << " " << endl;
		cout << "\t\t\t                  Total Price : RM" << payment->price << setw(28) << " " << endl;
		cout << "\t\t\t         Total money from customer : RM"<<money<<"                                       " << endl;
		cout << "\t\t\t                                                                 " << endl;
		cout << "\t\t\t#################################################################" << endl;
		 
		
			a = _getch();
			if ((a >= '0' && a <= '9')) {

				money += a;
				++i;
				

			}
			if (a == '\b' && i >= 1) {
				if (money[i ] == '.')
				{
					dot = true;
				}
				money.pop_back();
				--i;
			}
			if (a == '.' && dot) {
				money += a;
				dot = false;
				++i;
			}
			if (a == '\r') {
				break;
			}
			if (a == 'b') {
				return;
			}
			

		

	}
	double balance = stod(money) - (payment->price);

	system("cls");
	cout << endl << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t                             PAYING                                 " << endl;
	cout << "\t\t\t         User ID/IC : " << payment->userID << setw(14) << "Pc ID : " << payment->computerID << setw(10) << "            " << endl;
	cout << "\t\t\t                  Play Time   : " << payment->totalTime << setw(28) << " " << endl;
	cout << "\t\t\t                  Total Price : RM" << payment->price << setw(28) << " " << endl;
	cout << "\t\t\t                  Balance : RM" << balance << "                                      " << endl;
	cout << "\t\t\t                       ======PAID======                                               " << endl;
	cout << "\t\t\t#################################################################" << endl<<endl;

	paymentManager.paid(payment->paymentID);
	system("pause");
	goto START;
}

void membershipTopup() {
	MemberManager memberManager;
	Member* member = new Member();
	bool check = true;
	int c;
	int y = 0;
	cout << "Choose member to topup" << endl;
	int z = memberManager.searchMember(lastMemberID());

	if (z == 0) {
		return;
	}

	member = memberManager.selectMemberNo(z);
	
	
		system("cls");
		if (stoi(member->membershipTime) > 0) {
			cout << endl << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
			cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
			cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
			cout << "\t\t\t                                                                    " << endl;
			cout << "\t\t\t                   Membership is ACTIVE. (" << member->membershipTime << ") day left                                               " << endl;
			cout << "\t\t\t                                                                    " << endl;
			cout << "\t\t\t#################################################################" << endl << endl;
		}
		else {
			cout << endl << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
			cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
			cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
			cout << "\t\t\t                                                                    " << endl;
			cout << "\t\t\t                   Membership is NOT ACTIVE.                                              " << endl;
			cout << "\t\t\t                                                                 " << endl;
			cout << "\t\t\t#################################################################" << endl << endl;
		}
		cout << "\t\t\t =====1 MONTH = RM 10=====" << endl;
		cout << "\t\t\t->1 month" << endl;
		cout << "\t\t\t  2 month" << endl;
		cout << "\t\t\t  3 month" << endl;
		cout << "\t\t\t  4 month" << endl<<endl;
		cout << "\t\t\tPrice : RM 10.00" << endl;


		while (check) {
			c = 0;

			switch ((c = _getch())) {
			case KEY_UP:
				if (y > 0) {
					y--;
				}
				break;
			case KEY_DOWN:
				if (y < 3) {
					y++;
				}
				break;

			case '\r':
				check = false;
			default:
				break;
			}
			if (c == '0') {
				return;
			}

			system("cls");
			if (y == 0) {
				if (stoi(member->membershipTime) > 0) {
					cout << endl << endl;
					cout << "\t\t\t#################################################################" << endl;
					cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
					cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
					cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t                   Membership is ACTIVE. (" << member->membershipTime << ") day left                                               " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t#################################################################" << endl << endl;
				}
				else {
					cout << endl << endl;
					cout << "\t\t\t#################################################################" << endl;
					cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
					cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
					cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t                   Membership is NOT ACTIVE.                                              " << endl;
					cout << "\t\t\t                                                                 " << endl;
					cout << "\t\t\t#################################################################" << endl << endl;
				}
				cout << "\t\t\t =====1 MONTH = RM 10=====" << endl;
				cout << "\t\t\t->1 month" << endl;
				cout << "\t\t\t  2 month" << endl;
				cout << "\t\t\t  3 month" << endl;
				cout << "\t\t\t  4 month" << endl << endl;
				cout << "\t\t\tPrice : RM 10.00" << endl;

			}
			else if (y == 1) {
				if (stoi(member->membershipTime) > 0) {
					cout << endl << endl;
					cout << "\t\t\t#################################################################" << endl;
					cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
					cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
					cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t                   Membership is ACTIVE. (" << member->membershipTime << ") day left                                               " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t#################################################################" << endl << endl;
				}
				else {
					cout << endl << endl;
					cout << "\t\t\t#################################################################" << endl;
					cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
					cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
					cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t                   Membership is NOT ACTIVE.                                              " << endl;
					cout << "\t\t\t                                                                 " << endl;
					cout << "\t\t\t#################################################################" << endl << endl;
				}
				cout << "\t\t\t =====1 MONTH = RM 10=====" << endl;
				cout << "\t\t\t  1 month" << endl;
				cout << "\t\t\t->2 month" << endl;
				cout << "\t\t\t  3 month" << endl;
				cout << "\t\t\t  4 month" << endl << endl;
				cout << "\t\t\tPrice : RM 20.00" << endl;

			}
		
			else if (y == 2) {
			if (stoi(member->membershipTime) > 0) {
				cout << endl << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
				cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
				cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
				cout << "\t\t\t                                                                    " << endl;
				cout << "\t\t\t                   Membership is ACTIVE. (" << member->membershipTime << ") day left                                               " << endl;
				cout << "\t\t\t                                                                    " << endl;
				cout << "\t\t\t#################################################################" << endl << endl;
			}
			else {
				cout << endl << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
				cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
				cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
				cout << "\t\t\t                                                                    " << endl;
				cout << "\t\t\t                   Membership is NOT ACTIVE.                                              " << endl;
				cout << "\t\t\t                                                                 " << endl;
				cout << "\t\t\t#################################################################" << endl << endl;
			}
			cout << "\t\t\t =====1 MONTH = RM 10=====" << endl;
			cout << "\t\t\t  1 month" << endl;
			cout << "\t\t\t  2 month" << endl;
			cout << "\t\t\t->3 month" << endl;
			cout << "\t\t\t  4 month" << endl << endl;
			cout << "\t\t\tPrice : RM 30.00" << endl;

			}
			else if (y == 3) {
				if (stoi(member->membershipTime) > 0) {
					cout << endl << endl;
					cout << "\t\t\t#################################################################" << endl;
					cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
					cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
					cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t                   Membership is ACTIVE. (" << member->membershipTime << ") day left                                               " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t#################################################################" << endl << endl;
				}
				else {
					cout << endl << endl;
					cout << "\t\t\t#################################################################" << endl;
					cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
					cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
					cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
					cout << "\t\t\t                                                                    " << endl;
					cout << "\t\t\t                   Membership is NOT ACTIVE.                                              " << endl;
					cout << "\t\t\t                                                                 " << endl;
					cout << "\t\t\t#################################################################" << endl << endl;
				}
				cout << "\t\t\t =====1 MONTH = RM 10=====" << endl;
				cout << "\t\t\t  1 month" << endl;
				cout << "\t\t\t  2 month" << endl;
				cout << "\t\t\t  3 month" << endl;
				cout << "\t\t\t->4 month" << endl << endl;
				cout << "\t\t\tPrice : RM 40.00" << endl;
			}
		}
		
		int status = memberManager.addMembershipTime(member->memberID, member->day + (y + 1) * 30);
		updateMembershipTime();
		member = memberManager.selectMemberNo(z);
		system("cls");
		if (status) {
			cout << endl << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
			cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
			cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
			cout << "\t\t\t                                                                    " << endl;
			cout << "\t\t\t                   Membership is ACTIVE. (" << member->membershipTime << ") day left                                               " << endl;
			cout << "\t\t\t                     ======TOPUP MEMBERSHIPTIME SUCCESSFUL======                                          " << endl;
			cout << "\t\t\t#################################################################" << endl << endl;

		}
		else {
			cout << endl << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t                             MEMBERSHIP TOPUP                                 " << endl;
			cout << "\t\t\t           Member ID : " << member->memberID << "                                                         " << endl;
			cout << "\t\t\t           Name : " << member->name << "                                                        " << endl;
			cout << "\t\t\t                                                                    " << endl;
			cout << "\t\t\t                                                                 " << endl;
			cout << "\t\t\t                     !!!!!TOPUP MEMBERSHIPTIME FAIL!!!!!!                                          " << endl;
			cout << "\t\t\t#################################################################" << endl << endl;
		}
		system("pause");
}

void paymentHistory()
{
	PaymentManager paymentManager;
	
	paymentManager.showAll();
}

void profit() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	time_t current = time(0);
	string today = to_string(ltm->tm_mday) + "/" + to_string(ltm->tm_mon + 1) + "/" + to_string(ltm->tm_year - 100);
	PaymentManager paymentManager;
	
	//paymentManager.graph(today);
	//paymentManager.scaledGraph(today);
	paymentManager.yearlyGraph();
	
}

void  paymentMastery() {

	START:
	system("CLS");
	bool check = true;
	int c, y = 0;
	cout << endl << endl;
	cout << "\t\t\tMENU > PAYMENT" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#                         PAYMENT                               #" << endl;
	cout << "\t\t\t#               ->1.Paying                                      #" << endl;
	cout << "\t\t\t#                 2.Membership Topup                            #" << endl;
	cout << "\t\t\t#                 3.Payment History                             #" << endl;
	cout << "\t\t\t#                 4.Profit Graph                                #" << endl;
	cout << "\t\t\t#                 0.Return                                      #" << endl;
	cout << "\t\t\t#################################################################" << endl;
	while (check)
	{

		int c = _getch();
		if (c == '\r') {
			check = false;
		}
		if (c == 224) {

			int key = _getch();


			switch ((key)) {
			case KEY_UP:
				if (y > 0) {
					y--;
				}
				break;
			case KEY_DOWN:
				if (y < 4) {
					y++;
				}
				break;


			default:
				break;
			}
		}
		system("cls");

		if (y == 0) {
			cout << endl << endl;
			cout << "\t\t\tMENU > PAYMENT" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         PAYMENT                               #" << endl;
			cout << "\t\t\t#               ->1.Paying                                      #" << endl;
			cout << "\t\t\t#                 2.Membership Topup                            #" << endl;
			cout << "\t\t\t#                 3.Payment History                             #" << endl;
			cout << "\t\t\t#                 4.Profit Graph                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 1) {
			cout << endl << endl;
			cout << "\t\t\tMENU > PAYMENT" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         PAYMENT                               #" << endl;
			cout << "\t\t\t#                 1.Paying                                      #" << endl;
			cout << "\t\t\t#               ->2.Membership Topup                            #" << endl;
			cout << "\t\t\t#                 3.Payment History                             #" << endl;
			cout << "\t\t\t#                 4.Profit Graph                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 2) {
			cout << endl << endl;
			cout << "\t\t\tMENU > PAYMENT" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         PAYMENT                               #" << endl;
			cout << "\t\t\t#                 1.Paying                                      #" << endl;
			cout << "\t\t\t#                 2.Membership Topup                            #" << endl;
			cout << "\t\t\t#               ->3.Payment History                             #" << endl;
			cout << "\t\t\t#                 4.Profit Graph                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 3) {
			cout << endl << endl;
			cout << "\t\t\tMENU > PAYMENT" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         PAYMENT                               #" << endl;
			cout << "\t\t\t#                 1.Paying                                      #" << endl;
			cout << "\t\t\t#                 2.Membership Topup                            #" << endl;
			cout << "\t\t\t#                 3.Payment History                             #" << endl;
			cout << "\t\t\t#               ->4.Profit Graph                                #" << endl;
			cout << "\t\t\t#                 0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}
		else if (y == 4) {
			cout << endl << endl;
			cout << "\t\t\tMENU > PAYMENT" << endl;
			cout << "\t\t\t#################################################################" << endl;
			cout << "\t\t\t#                         PAYMENT                               #" << endl;
			cout << "\t\t\t#                 1.Paying                                      #" << endl;
			cout << "\t\t\t#                 2.Membership Topup                            #" << endl;
			cout << "\t\t\t#                 3.Payment History                             #" << endl;
			cout << "\t\t\t#                 4.Profit Graph                                #" << endl;
			cout << "\t\t\t#               ->0.Return                                      #" << endl;
			cout << "\t\t\t#################################################################" << endl;

		}

	}

	if (y == 0) {
		system("cls");
		paying();
	}
	else if (y == 1) {
		system("cls");
		membershipTopup();
	}
	else if (y == 2) {
		system("cls");
		paymentHistory();
	}
	else if (y == 3) {
		system("cls");
		profit();
	}
	else if (y == 4) {
		return;

	}
	
	goto START;
}


//MENU

int  mainMenu() {
	
	
	system("CLS");
	bool check = true;
	
	int y = 0;
	cout << endl << endl;
	cout << "\t\t\tMENU" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t#			  CHOOSE YOUR OPTION			#"<<endl;
	cout << "\t\t\t#		->1.Member Mastery				#"<<endl;
	cout << "\t\t\t#		  2.Computer Mastery				#" << endl;
	cout << "\t\t\t#		  3.Allotment of Computers			#" << endl;
	cout << "\t\t\t#		  4.Payment					#" << endl;
	cout << "\t\t\t#		  0.Log Out					#" << endl;
	cout << "\t\t\t#################################################################" << endl;
	
	while (check)
	{
		
	
		int c = _getch();
		
		if (c == '\r') {
			return y;
		}
		if (c == 224) {
			
			int key = _getch();
			

			switch ((key)) {
			case KEY_UP:

				if (y > 0) {
					y--;
				}

				break;
			case KEY_DOWN:

				if (y < 4) {
					y++;

				}
				break;


			default:
				break;
			}
		}

		
		system("cls");
		
		
		
			if (y == 0) {
				cout << endl << endl;
				cout << "\t\t\tMENU" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  CHOOSE YOUR OPTION			#" << endl;
				cout << "\t\t\t#		->1.Member Mastery				#" << endl;
				cout << "\t\t\t#		  2.Computer Mastery				#" << endl;
				cout << "\t\t\t#		  3.Allotment of Computers			#" << endl;
				cout << "\t\t\t#		  4.Payment					#" << endl;
				cout << "\t\t\t#		  0.Log Out					#" << endl;
				cout << "\t\t\t#################################################################" << endl;

			}
			else if (y == 1) {
				cout << endl << endl;
				cout << "\t\t\tMENU" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  CHOOSE YOUR OPTION			#" << endl;
				cout << "\t\t\t#		  1.Member Mastery				#" << endl;
				cout << "\t\t\t#		->2.Computer Mastery				#" << endl;
				cout << "\t\t\t#		  3.Allotment of Computers			#" << endl;
				cout << "\t\t\t#		  4.Payment					#" << endl;
				cout << "\t\t\t#		  0.Log Out					#" << endl;
				cout << "\t\t\t#################################################################" << endl;

			}
			else if (y == 2) {
				cout << endl << endl;
				cout << "\t\t\tMENU" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  CHOOSE YOUR OPTION			#" << endl;
				cout << "\t\t\t#		  1.Member Mastery				#" << endl;
				cout << "\t\t\t#		  2.Computer Mastery				#" << endl;
				cout << "\t\t\t#		->3.Allotment of Computers			#" << endl;
				cout << "\t\t\t#		  4.Payment					#" << endl;
				cout << "\t\t\t#		  0.Log Out					#" << endl;
				cout << "\t\t\t#################################################################" << endl;

			}
			else if (y == 3) {
				cout << endl << endl;
				cout << "\t\t\tMENU" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  CHOOSE YOUR OPTION			#" << endl;
				cout << "\t\t\t#		  1.Member Mastery				#" << endl;
				cout << "\t\t\t#		  2.Computer Mastery				#" << endl;
				cout << "\t\t\t#		  3.Allotment of Computers			#" << endl;
				cout << "\t\t\t#		->4.Payment					#" << endl;
				cout << "\t\t\t#		  0.Log Out					#" << endl;
				cout << "\t\t\t#################################################################" << endl;

			}
			else if (y == 4) {
				cout << endl << endl;
				cout << "\t\t\tMENU" << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#			  CHOOSE YOUR OPTION			#" << endl;
				cout << "\t\t\t#		  1.Member Mastery				#" << endl;
				cout << "\t\t\t#		  2.Computer Mastery				#" << endl;
				cout << "\t\t\t#		  3.Allotment of Computers			#" << endl;
				cout << "\t\t\t#		  4.Payment					#" << endl;
				cout << "\t\t\t#		->0.Log Out					#" << endl;
				cout << "\t\t\t#################################################################" << endl;

			}
			
	}
}


//OUT
void thankYou() {
	string text = "LOGGING OUT";
	string text0;
	for (auto c : text) {
		text0 += c;
		boost::detail::Sleep(25);
		system("cls");
		cout << "                                              "<<text0;

	}
	boost::detail::Sleep(1000);
	system("cls");
	cout << "                       =======================" << text0 << "=======================\n\n\n\n\n\n\n\n\n\n\n\n";
}

//ADMIN SECTET

void welcome() {

	string secretWord = "";
	char a;
	
	while(true) {
		system("cls");
		
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t#                       +=CYBER CAFE SYSTEM=+                   #" << endl;
		cout << "\t\t\t#                                                               #" << endl;
		cout << "\t\t\t#                    CLICK ENTER TO GET CONTINUE                #" << endl;
		cout << "\t\t\t#                    ---------------------------                #" << endl;
		cout << "\t\t\t#                      enter password to go to                  #" << endl;
		cout << "\t\t\t#                            admin entry                        #" << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << secretWord;
		a = _getch();
		if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {

			secretWord += a;

		}
		if (a == '\b' ) {
			secretWord = "";
			
		}
		if (a == '\r') {
			break;
		}
		if (secretWord == "cybercafe123") {
			string GO = "GOING TO ADMIN MASTERY";
			
			string j = "                        #                                                               #";
			int k = 47;
			for (int i = 0; i < GO.size(); i++) {
				boost::detail::Sleep(25);
				j[k++] = GO[i];
				system("cls");
				cout << endl << endl;
				cout << "\t\t\t#################################################################" << endl;
				cout << "\t\t\t#                       +=CYBER CAFE SYSTEM=+                   #" << endl;
				cout << "\t\t\t#                                                               #" << endl;
				cout << j;
				cout << "\n\t\t\t#                                                               #" << endl;
				cout << "\t\t\t#                                                               #" << endl;
				cout << "\t\t\t#                                                               #" << endl;
				cout << "\t\t\t#################################################################" << endl;
				
			}
			boost::detail::Sleep(1000);
			adminMastery();
			secretWord = "";
			
		}

	}
	

}

//MAIN
int main()
{

	while (1) {
		adminLogin();
		welcome();
		while (1) {
			checkTime();

			int option = mainMenu();
			if (option == 0) {
				updateMembershipTime();
				memberMastery();
			}
			else if (option == 1) {

				computerMastery();
			}
			else if (option == 2) {
				updateMembershipTime();
				allocatingMastery();
			}
			else if (option == 3) {
				updateMembershipTime();
				paymentMastery();

			}
			else if (option == 4) {

				system("cls");
				thankYou();
				break;
				//exit(0);

			}
		}
	}


	return 0;	
}