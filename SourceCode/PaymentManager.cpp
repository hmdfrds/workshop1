#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Payment.h"
#include "PaymentManager.h"
#include "Allocating.h"
#include <conio.h>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

int lastPaymentID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from payment");

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

int firstPaymentID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MIN(NO) from payment");

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

void PaymentManager::addIntoList(Allocating* allocate) {

	time_t now = time(0);
	tm* ltm = localtime(&now);
	time_t current = time(0);

	string id = to_string(ltm->tm_mday) + to_string(ltm->tm_mon) + to_string(ltm->tm_year - 100) + to_string(lastPaymentID() + 1);

	double price;
	string hour = "", min = "", sec = "";

	int k = 0;
	for (int j = 0; j < allocate->totalTime.size(); j++) {
		if (allocate->totalTime[j] != ':' && k == 0) {
			hour += allocate->totalTime[j];
		}
		if (allocate->totalTime[j] != ':' && k == 1) {
			min += allocate->totalTime[j];
		}
		if (allocate->totalTime[j] != ':' && k == 2) {
			sec += allocate->totalTime[j];
		}
		if (allocate->totalTime[j] == ':') {
			k++;
		}
	}
	price = stod(hour) * 2.5 + stod(min) * 0.4 + stod(sec) * 0.006;

	if ((allocate->userID)[0] == 'M' || (allocate->userID)[0] == 'm') {
		price *= 0.75;
	}
	price = (int)(price * 100 + .5);
	price = (double)price / 100;

	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO payment VALUES (?, ?, ?,?, ?, ?,?,?)");

	ps->setString(1, to_string(lastPaymentID() + 1));
	ps->setString(2, id);
	ps->setString(3, allocate->userID);
	ps->setString(4, allocate->computerID);
	ps->setString(5, allocate->totalTime);
	ps->setDouble(6, price);
	ps->setString(7, to_string(ltm->tm_mday) + "/" + to_string(ltm->tm_mon + 1) + "/" + to_string(ltm->tm_year - 100));
	ps->setString(8, "Unpaid");



	int status = ps->executeUpdate();

	delete ps;



}

Payment* PaymentManager::selectPaymentNo(int NO)
{

	Payment* payment = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM payment WHERE NO = ?");

	ps->setInt(1, NO);

	ResultSet* rs = ps->executeQuery();
	payment = 0;
	if (rs->next())
	{
		payment = new Payment();

		payment->NO = rs->getInt(1);
		payment->paymentID = rs->getString(2);
		payment->userID = rs->getString(3);
		payment->computerID = rs->getString(4);
		payment->totalTime = rs->getString(5);
		payment->price = rs->getDouble(6);
		payment->date = rs->getString(7);
		payment->paid = rs->getString(8);
	}
	delete rs;
	delete ps;
	return payment;
}

void PaymentManager::paid(string paymentID) {


	DatabaseConnection dbConn;

	PreparedStatement* ps = dbConn.prepareStatement("UPDATE payment SET Paid = (?) WHERE paymentID = (?) ");

	ps->setString(1, "Paid");
	ps->setString(2, paymentID);
	ps->executeUpdate();
}

int  PaymentManager::showUnpaid() {


	Payment* payment = new Payment();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;

	bool check = true;

	int y = 1;
	ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE Paid = 'Unpaid'");
	rs = ps->executeQuery();
	if (rs->next()) {
		y = rs->getInt(1);
	}
	int c = 0;
	int NO = 0;
	string paymentID = "";
	vector <string> arrow;
	for (int i = 0; i <= lastPaymentID(); i++) {
		arrow.push_back("  ");
	}
	if (lastPaymentID() != 0) {
		arrow[1] = "-> ";
	}


	ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE Paid = 'Unpaid'");
	rs = ps->executeQuery();
	if (rs->next()) {
		if (rs->getInt(1) == NULL) {
			cout << "\t\t\t\t\t\tType Payment ID to Search" << endl;
			cout << "\t\t\t\t\tPayment ID : " << paymentID << endl;
			cout << "\n" << "  Payment ID" << setw(18) << "User ID/IC" << setw(21) << "Computer ID " << setw(18) << "Total Time" << setw(15) << "Price" << setw(13) << "Date" << setw(20) << "Paid/Unpaid" << endl;
			cout << " ====================================================================================================================" << endl << endl;


			cout << "  " << "						DATA IS EMPTY" << endl;


			cout << "\n ====================================================================================================================" << endl << endl;
			system("pause");
			return 0;
		}
		else {
			arrow[rs->getInt(1)] = "-> ";
		}
	}




	system("cls");
	cout << "\t\t\t\t\t\tType Payment ID to Search" << endl;
	cout << "\t\t\t\t\tPayment ID : " << paymentID << endl;
	cout << "\n" << "  Payment ID" << setw(18) << "User ID/IC" << setw(21) << "Computer ID " << setw(18) << "Total Time" << setw(15) << "Price" << setw(13) << "Date" << setw(20) << "Paid/Unpaid" << endl;
	cout << " ====================================================================================================================" << endl << endl;

	for (int i = 1; i <= lastPaymentID(); i++) {
		ps = dbConn.prepareStatement("SELECT * FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Unpaid'");
		ps->setString(1, paymentID + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{

			cout << arrow[i] << rs->getString(2) << setw(19) << rs->getString(3) << setw(20) << rs->getString(4) << setw(19) << rs->getString(5) << setw(13) << "RM" << rs->getDouble(6) << setw(16) << rs->getString(7) << setw(15) << rs->getString(8) << endl;
		}


	}
	cout << "\n ====================================================================================================================" << endl << endl;


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
					ps = dbConn.prepareStatement("SELECT NO FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Unpaid'");
					ps->setString(1, paymentID + "%");
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
			if (y < lastPaymentID()) {
				arrow[y] = "  ";
				int j = y;
				j++;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Unpaid'");
					ps->setString(1, paymentID + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == lastPaymentID()) {
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
			if (paymentID.size() >= 1) {
				paymentID.pop_back();
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE paymentID LIKE ? AND Paid = 'Unpaid'");
				ps->setString(1, paymentID + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}
			}
			break;
		default:
			if (c >= '0' && c <= '9') {
				paymentID += c;

				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE paymentID LIKE ? AND Paid = 'Unpaid'");
				ps->setString(1, paymentID + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}

			}
			break;
		}

		if (c == 'b' || c == 'B') { return 0; }

		if (check) {




			system("cls");
			cout << "\t\t\t\t\t\tType Payment ID to Search" << endl;
			cout << "\t\t\t\t\tPayment ID : " << paymentID << endl;
			cout << "\n" << "  Payment ID" << setw(18) << "User ID/IC" << setw(21) << "Computer ID " << setw(18) << "Total Time" << setw(15) << "Price" << setw(13) << "Date" << setw(20) << "Paid/Unpaid" << endl;
			cout << " ====================================================================================================================" << endl << endl;

			for (int i = 1; i <= lastPaymentID(); i++) {
				ps = dbConn.prepareStatement("SELECT * FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Unpaid'");
				ps->setString(1, paymentID + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{

					cout << arrow[i] << rs->getString(2) << setw(19) << rs->getString(3) << setw(20) << rs->getString(4) << setw(19) << rs->getString(5) << setw(13) << "RM" << rs->getDouble(6) << setw(16) << rs->getString(7) << setw(15) << rs->getString(8) << endl;
				}


			}
			cout << "\n ====================================================================================================================" << endl << endl;
		}
	}

	return 1;
}

void PaymentManager::showAll() {

	Payment* payment = new Payment();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;

	bool check = true;

	int y = 1;
	int c = 0;
	int NO = 0;
	string paymentID = "";
	vector <string> arrow;
	for (int i = 0; i <= lastPaymentID(); i++) {
		arrow.push_back("  ");
	}
	if (lastPaymentID() != 0) {
		arrow[1] = "-> ";
	}


	ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE Paid = 'Paid'");
	rs = ps->executeQuery();
	if (rs->next()) {
		if (rs->getInt(1) == NULL) {
			cout << "\t\t\t\t\t\tType Payment ID to Search" << endl;
			cout << "\t\t\t\t\tPayment ID : " << paymentID << endl;
			cout << "\n" << "  Payment ID" << setw(18) << "User ID/IC" << setw(21) << "Computer ID " << setw(18) << "Total Time" << setw(15) << "Price(RM)" << setw(13) << "Date" << setw(20) << "Paid/Unpaid" << endl;
			cout << " ====================================================================================================================" << endl << endl;


			cout << "  " << "						DATA IS EMPTY" << endl;


			cout << "\n ====================================================================================================================" << endl << endl;
			system("pause");
			return;
		}
		else {
			arrow[rs->getInt(1)] = "-> ";
		}
	}




	system("cls");
	cout << "\t\t\t\t\t\tType Payment ID to Search" << endl;
	cout << "\t\t\t\t\tPayment ID : " << paymentID << endl;
	cout << "\n" << "  Payment ID" << setw(18) << "User ID/IC" << setw(21) << "Computer ID " << setw(18) << "Total Time" << setw(15) << "Price(RM)" << setw(13) << "Date" << setw(20) << "Paid/Unpaid" << endl;
	cout << " ====================================================================================================================" << endl << endl;

	for (int i = 1; i <= lastPaymentID(); i++) {
		ps = dbConn.prepareStatement("SELECT * FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Paid'");
		ps->setString(1, paymentID + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{

			cout << arrow[i] << rs->getString(2) << setw(19) << rs->getString(3) << setw(20) << rs->getString(4) << setw(19) << rs->getString(5) << setw(13) << rs->getDouble(6) << setw(16) << rs->getString(7) << setw(15) << rs->getString(8) << endl;
		}


	}
	cout << "\n ====================================================================================================================" << endl << endl;


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
					ps = dbConn.prepareStatement("SELECT NO FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Paid'");
					ps->setString(1, paymentID + "%");
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
			if (y < lastPaymentID()) {
				arrow[y] = "  ";
				int j = y;
				j++;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Paid'");
					ps->setString(1, paymentID + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == lastPaymentID()) {
						c = false;
					}
					else {
						j++;
					}



				}
				arrow[y] = "-> ";
			}
			break;

		case '\b':
			if (paymentID.size() >= 1) {
				paymentID.pop_back();
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE paymentID LIKE ? AND Paid = 'Paid'");
				ps->setString(1, paymentID + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}
			}
			break;
		default:
			if (c >= '0' && c <= '9') {
				paymentID += c;

				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM payment WHERE paymentID LIKE ? AND Paid = 'Paid'");
				ps->setString(1, paymentID + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}

			}
			break;
		}

		if (c == 'b' || c == 'B') { return; }

		if (check) {




			system("cls");
			cout << "\t\t\t\t\t\tType Payment ID to Search" << endl;
			cout << "\t\t\t\t\tPayment ID : " << paymentID << endl;
			cout << "\n" << "  Payment ID" << setw(18) << "User ID/IC" << setw(21) << "Computer ID " << setw(18) << "Total Time" << setw(15) << "Price(RM)" << setw(13) << "Date" << setw(20) << "Paid/Unpaid" << endl;
			cout << " ====================================================================================================================" << endl << endl;

			for (int i = 1; i <= lastPaymentID(); i++) {
				ps = dbConn.prepareStatement("SELECT * FROM payment WHERE paymentID LIKE ? AND NO = ? AND Paid = 'Paid'");
				ps->setString(1, paymentID + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{

					cout << arrow[i] << rs->getString(2) << setw(19) << rs->getString(3) << setw(20) << rs->getString(4) << setw(19) << rs->getString(5) << setw(13) << rs->getDouble(6) << setw(16) << rs->getString(7) << setw(15) << rs->getString(8) << endl;
				}


			}
			cout << "\n ====================================================================================================================" << endl << endl;
		}
	}


}

void PaymentManager::graph(string today) {

	string latestDate;
	string day, month, year;
	Payment* payment = NULL;
	string date1, date2, date3, date4, date5, date6, date7;
	int d1, d2, d3, d4, d5, d6, d7;
	int price1 = 0, price2 = 0, price3 = 0, price4 = 0, price5 = 0, price6 = 0, price7 = 0;
	DatabaseConnection dbConn;
	PreparedStatement* ps;



	ResultSet* rs ;

		latestDate = today;
		int k = 0;
		for (int i = 0; i < latestDate.size(); i++) {

			if (k == 0) {
				day += latestDate[i];
			}
			else if (k == 1) {
				month += latestDate[i];
			}
			else if (k == 2) {
				year += latestDate[i];
			}
			if (latestDate[i + 1] == '/') {
				k++;
				i++;
			}
		}
	


	d1 = stoi(day) - 6;
	if (d1 <= 0) {
		month = to_string(stoi(month) - 1);
		if (stoi(month) % 2 == 0) {
			d1 = 30 + d1;
		}
		else {
			d1 = 31 + d1;
		}
	}
	date1 = to_string(d1) + "/" + month + "/" + year;

	d2 = stoi(day) - 5;
	if (d2 <= 0) {
		month = to_string(stoi(month) - 1);
		if (stoi(month) % 2 == 0) {
			d2 = 30 + d2;
		}
		else {
			d2 = 31 + d2;
		}
	}
	date2 = to_string(d2) + "/" + month + "/" + year;

	d3 = stoi(day) - 4;
	if (d3 <= 0) {
		month = to_string(stoi(month) - 1);
		if (stoi(month) % 2 == 0) {
			d3 = 30 + d3;
		}
		else {
			d3 = 31 + d3;
		}
	}
	date3 = to_string(d3) + "/" + month + "/" + year;

	d4 = stoi(day) - 3;
	if (d4 <= 0) {
		month = to_string(stoi(month) - 1);
		if (stoi(month) % 2 == 0) {
			d4 = 30 + d4;
		}
		else {
			d4 = 31 + d4;
		}
	}
	date4 = to_string(d4) + "/" + month + "/" + year;

	d5 = stoi(day) - 2;
	if (d5 <= 0) {
		month = to_string(stoi(month) - 1);
		if (stoi(month) % 2 == 0) {
			d5 = 30 + d5;
		}
		else {
			d5 = 31 + d5;
		}
	}
	date5 = to_string(d5) + "/" + month + "/" + year;

	d6 = stoi(day) - 1;
	if (d6 <= 0) {
		month = to_string(stoi(month) - 1);
		if (stoi(month) % 2 == 0) {
			d6 = 30 + d6;
		}
		else {
			d6 = 31 + d6;
		}
	}
	date6 = to_string(d6) + "/" + month + "/" + year;

	d7 = stoi(day);
	date7 = latestDate;

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date1);
	rs = ps->executeQuery();
	if (rs->next()) {
		price1 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date2);
	rs = ps->executeQuery();
	if (rs->next()) {
		price2 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date3);
	rs = ps->executeQuery();
	if (rs->next()) {
		price3 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date4);
	rs = ps->executeQuery();
	if (rs->next()) {
		price4 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date5);
	rs = ps->executeQuery();
	if (rs->next()) {
		price5 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date6);
	rs = ps->executeQuery();
	if (rs->next()) {
		price6 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date7);
	rs = ps->executeQuery();
	if (rs->next()) {
		price7 = rs->getDouble(1) +1;
	}


	int higest = max(price1, price2);
	higest = max(higest, price3);
	higest = max(higest, price4);
	higest = max(higest, price5);
	higest = max(higest, price6);
	higest = max(higest, price7);
	if (higest < 10) {
		higest = 10;
	}
	int size = to_string(higest).size();
	int start = 7 * 6 + size + 1;
	cout << "                                  ";
	cout << "  RM" << endl;
	cout << "                                  ";
	for (int i = 0; i < size ; i++) {
		cout << " ";
	}
	int scale = 1;
	char b = 178;
	cout << "^" << endl;
	
	if (higest > 20) {
		int temp = higest /  pow(10 , (to_string(higest).size() -1));
		temp = temp * pow(10 , (to_string(higest).size() - 1));
		scale = temp / 10;
		while (higest % scale != 0 ) {
			higest++;
		}
		bool up1 = true;
		bool up2 = true;
		bool up3 = true;
		bool up4 = true;
		bool up5 = true;
		bool up6 = true;
		bool up7 = true;

		for (int i = higest; i >= scale; i -= scale) {
			cout << "                                  ";
			for (int j = start; j >= 0; j--) {

				if (j == start) {
					cout << setw(size) << i << "|";
				}

				//-------------------price 1
				else if (i < price1 && j == 41) {
					cout << "|";
				}
				else if (i <= price1 + scale && j == 40) {
					if (up1) {
						cout << "_";
						up1 = false;
					}
					else {
						cout << b;
					}

				}
				else if (i < price1 && j == 39) {
					cout << "|";
				}

				//-------------------price 2
				else if (i < price2 && j == 36) {
					cout << "|";
				}
				else if ( i <= price2 + scale  && j == 35) {
					if (up2) {
						cout << "_";
						up2 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price2 && j == 34) {
					cout << "|";
				}

				//-------------------price 3
				else if (i < price3 && j == 31) {
					cout << "|";
				}
				else if ( i <= price3 + scale  && j == 30) {
					if (up3) {
						cout << "_";
						up3 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price3 && j == 29) {
					cout << "|";
				}


				//-------------------price 4
				else if (i < price4 && j == 26) {
					cout << "|";
				}
				else if ( i <= price4 + scale  && j == 25) {
					if (up4) {
						cout << "_";
						up4 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price4 && j == 24) {
					cout << "|";
				}

				//-------------------price 5
				else if (i < price5 && j == 21) {
					cout << "|";
				}
				else if ( i <= price5 + scale  && j == 20) {
					if (up5) {
						cout << "_";
						up5 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price5 && j == 19) {
					cout << "|";
				}


				//-------------------price 6
				else if (i < price6 && j == 16) {
					cout << "|";
				}
				else if ( i <= price6 + scale  && j == 15) {
					if (up6 ) {
						cout << "_";
						up6 = false;
					}
					else {
						cout << b;
					}
					
				}
				else if (i < price6 && j == 14) {
					cout << "|";
				}

				//-------------------price 7
				else if (i < price7 && j == 11) {
					cout << "|";
				}
				else if ( i <= price7 + scale+1  && j == 10) {
				if (up7) {
					cout << "_";
					up7 = false;
				}
				else {
					cout << b;
				}
				
				}
				else if (i < price7 && j == 9) {
					cout << "|";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}
	else {
	bool up1 = true;
	bool up2 = true;
	bool up3 = true;
	bool up4 = true;
	bool up5 = true;
	bool up6 = true;
	bool up7 = true;

	for (int i = higest; i >= scale; i -= scale) {
		cout << "                                  ";
		for (int j = start; j >= 0; j--) {

			if (j == start) {
				cout << setw(size) << i << "|";
			}

			//-------------------price 1
			else if (i < price1 && j == 41) {
				cout << "|";
			}
			else if ( i <= price1 && j == 40) {
				if (up1) {
					cout << "_";
					up1 = false;
				}
				else {
					cout << b;
				}

			}
			else if (i < price1 && j == 39) {
				cout << "|";
			}

			//-------------------price 2
			else if (i < price2 && j == 36) {
				cout << "|";
			}
			else if ( i <= price2 && j == 35) {
				if (up2) {
					cout << "_";
					up2 = false;
				}
				else {
					cout << b;
				}
			}
			else if (i < price2 && j == 34) {
				cout << "|";
			}

			//-------------------price 3
			else if (i < price3 && j == 31) {
				cout << "|";
			}
			else if ( i <= price3 && j == 30) {
				if (up3) {
					cout << "_";
					up3 = false;
				}
				else {
					cout << b;
				}
			}
			else if (i < price3 && j == 29) {
				cout << "|";
			}


			//-------------------price 4
			else if (i < price4 && j == 26) {
				cout << "|";
			}
			else if ( i <= price4 && j == 25) {
				if (up4) {
					cout << "_";
					up4 = false;
				}
				else {
					cout << b;
				}
			}
			else if (i < price4 && j == 24) {
				cout << "|";
			}

			//-------------------price 5
			else if (i < price5 && j == 21) {
				cout << "|";
			}
			else if ( i <= price5 && j == 20) {
				if (up5) {
					cout << "_";
					up5 = false;
				}
				else {
					cout << b;
				}
			}
			else if (i < price5 && j == 19) {
				cout << "|";
			}


			//-------------------price 6
			else if (i < price6 && j == 16) {
				cout << "|";
			}
			else if ( i <= price6 && j == 15) {
				if (up6) {
					cout << "_";
					up6 = false;
				}
				else {
					cout << b;
				}
			}
			else if (i < price6 && j == 14) {
				cout << "|";
			}

			//-------------------price 7
			else if (i < price7 && j == 11) {
				cout << "|";
			}
			else if ( i <= price7 && j == 10) {
			if (up7) {
				cout << "_";
				up7 = false;
			}
			else {
				cout << b;
			}
			}
			else if (i < price7 && j == 9) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}
	
	

	
		cout << "                                  ";
		for (int i = 0; i < size-1; i++) {
			cout << " ";
		}
		cout << "0-";
		char c  = 196;
		for (int i = 0; i <= start-7; i++) {
			cout << "-";
		}
		cout << "> DAY FROM MONTH";
		cout << endl;
		cout << "                                  ";
		for (int i = 0; i < size; i++) {
			cout << " ";
		}
		cout <<setw(size)<<"     " << d1 << "   " << setw(2) << d2 << "   " << setw(2) << d3 << "   " << setw(2) << d4 << "   " << setw(2) << d5 << "   " << setw(2) << d6 << "   " << setw(2) << d7<<endl;

	
}

void PaymentManager::scaledGraph(string today) {

	string latestDate;
	string day, month, year;
	Payment* payment = NULL;
	string date1, date2, date3, date4, date5, date6, date7;
	int d1, d2, d3, d4, d5, d6, d7;
	int price1 = 0, price2 = 0, price3 = 0, price4 = 0, price5 = 0, price6 = 0, price7 = 0;
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	time_t current = time(0);


	ResultSet* rs;

	latestDate = today;
	int k = 0;
	for (int i = 0; i < latestDate.size(); i++) {

		if (k == 0) {
			day += latestDate[i];
		}
		else if (k == 1) {
			month += latestDate[i];
		}
		else if (k == 2) {
			year += latestDate[i];
		}
		if (latestDate[i + 1] == '/') {
			k++;
			i++;
		}
	}


	string m1  = month, m2 = month, m3 = month, m4 = month, m5 = month, m6 = month, m7 = month;
	d1 = stoi(day) - 6;
	if (d1 <= 0) {
		m1 = to_string(stoi(month) - 1);
		if (stoi(m1) % 2 == 0) {
			d1 = 30 + d1;
		}
		else {
			d1 = 31 + d1;
		}
	}
	date1 = to_string(d1) + "/" + m1 + "/" + year;

	d2 = stoi(day) - 5;
	if (d2 <= 0) {
		m2 = to_string(stoi(month) - 1);
		if (stoi(m2) % 2 == 0) {
			d2 = 30 + d2;
		}
		else {
			d2 = 31 + d2;
		}
	}
	date2 = to_string(d2) + "/" + m2 + "/" + year;

	d3 = stoi(day) - 4;
	if (d3 <= 0) {
		m3 = to_string(stoi(month) - 1);
		if (stoi(m3) % 2 == 0) {
			d3 = 30 + d3;
		}
		else {
			d3 = 31 + d3;
		}
	}
	date3 = to_string(d3) + "/" + m3 + "/" + year;

	d4 = stoi(day) - 3;
	if (d4 <= 0) {
		m4 = to_string(stoi(month) - 1);
		if (stoi(m4) % 2 == 0) {
			d4 = 30 + d4;
		}
		else {
			d4 = 31 + d4;
		}
	}
	date4 = to_string(d4) + "/" + m4 + "/" + year;

	d5 = stoi(day) - 2;
	if (d5 <= 0) {
		m5 = to_string(stoi(month) - 1);
		if (stoi(m5) % 2 == 0) {
			d5 = 30 + d5;
		}
		else {
			d5 = 31 + d5;
		}
	}
	date5 = to_string(d5) + "/" + m5 + "/" + year;

	d6 = stoi(day) - 1;
	if (d6 <= 0) {
		m6 = to_string(stoi(m6) - 1);
		if (stoi(month) % 2 == 0) {
			d6 = 30 + d6;
		}
		else {
			d6 = 31 + d6;
		}
	}
	date6 = to_string(d6) + "/" + m6 + "/" + year;

	d7 = stoi(day);
	date7 = latestDate;

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date1);
	rs = ps->executeQuery();
	if (rs->next()) {
		price1 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date2);
	rs = ps->executeQuery();
	if (rs->next()) {
		price2 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date3);
	rs = ps->executeQuery();
	if (rs->next()) {
		price3 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date4);
	rs = ps->executeQuery();
	if (rs->next()) {
		price4 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date5);
	rs = ps->executeQuery();
	if (rs->next()) {
		price5 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date6);
	rs = ps->executeQuery();
	if (rs->next()) {
		price6 = rs->getDouble(1) + 1;
	}

	ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
	ps->setString(1, date7);
	rs = ps->executeQuery();
	if (rs->next()) {
		price7 = rs->getDouble(1) + 1;
	}


	int higest = max(price1, price2);
	higest = max(higest, price3);
	higest = max(higest, price4);
	higest = max(higest, price5);
	higest = max(higest, price6);
	higest = max(higest, price7);
	if (higest < 10) {
		higest = 10;
	}
	int size = to_string(higest).size();
	int start = 7 * 6 + size + 1;
	int scale = 1;
	char b = 178;

	cout << "\t\t\t\t WEEKLY PROFIT GRAPH";
	cout << "\t Today date is : " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year - 100 << endl;

	cout << "                                       Use arrow keys to scale the graph " << endl;
	cout << "                                     [UP/DOWN->+1/-1] [RIGHT/LEFT->+5/-5]" << endl;
	cout << "                                  ";
	cout << "  RM " << endl;
	cout << "                                  ";
	for (int i = 0; i < size; i++) {
		cout << " ";
	}
	
	cout << "^" << endl;

		int temp = higest / pow(10, (to_string(higest).size() - 1));
		temp = temp * pow(10, (to_string(higest).size() - 1));
		scale = temp / 10;
		while (higest % scale != 0) {
			higest++;
		}
		bool up1 = true;
		bool up2 = true;
		bool up3 = true;
		bool up4 = true;
		bool up5 = true;
		bool up6 = true;
		bool up7 = true;

		for (int i = higest; i >= scale; i -= scale) {
			cout << "                                  ";
			for (int j = start; j >= 0; j--) {

				if (j == start) {
					cout << setw(size) << i << "|";
				}

				//-------------------price 1
				else if (i < price1 && j == 41) {
					cout << "|";
				}
				else if (i < price1 + scale && j == 40) {
					if (up1) {
						cout << "_";
						up1 = false;
					}
					else {
						cout << b;
					}

				}
				else if (i < price1 && j == 39) {
					cout << "|";
				}

				//-------------------price 2
				else if (i < price2 && j == 36) {
					cout << "|";
				}
				else if (i < price2 + scale && j == 35) {
					if (up2) {
						cout << "_";
						up2 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price2 && j == 34) {
					cout << "|";
				}

				//-------------------price 3
				else if (i < price3 && j == 31) {
					cout << "|";
				}
				else if (i < price3 + scale && j == 30) {
					if (up3) {
						cout << "_";
						up3 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price3 && j == 29) {
					cout << "|";
				}


				//-------------------price 4
				else if (i < price4 && j == 26) {
					cout << "|";
				}
				else if (i < price4 + scale && j == 25) {
					if (up4) {
						cout << "_";
						up4 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price4 && j == 24) {
					cout << "|";
				}

				//-------------------price 5
				else if (i < price5 && j == 21) {
					cout << "|";
				}
				else if (i < price5 + scale && j == 20) {
					if (up5) {
						cout << "_";
						up5 = false;
					}
					else {
						cout << b;
					}
				}
				else if (i < price5 && j == 19) {
					cout << "|";
				}


				//-------------------price 6
				else if (i < price6 && j == 16) {
					cout << "|";
				}
				else if (i < price6 + scale && j == 15) {
					if (up6) {
						cout << "_";
						up6 = false;
					}
					else {
						cout << b;
					}

				}
				else if (i < price6 && j == 14) {
					cout << "|";
				}

				//-------------------price 7
				else if (i < price7 && j == 11) {
					cout << "|";
				}
				else if (i < price7 + scale && j == 10) {
					if (up7) {
						cout << "_";
						up7 = false;
					}
					else {
						cout << b;
					}

				}
				else if (i < price7 && j == 9) {
					cout << "|";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	
	
	cout << "                                  ";
	for (int i = 0; i < size - 1; i++) {
		cout << " ";
	}
	cout << "0-";

	for (int i = 0; i <= start - 7; i++) {
		cout << "-";
	}
	cout << "> DAY FROM MONTH";
	cout << endl;
	cout << "                                  ";
	for (int i = 0; i < size; i++) {
		cout << " ";
	}
	cout << setw(size) << "     " << d1 << "   " << setw(2) << d2 << "   " << setw(2) << d3 << "   " << setw(2) << d4 << "   " << setw(2) << d5 << "   " << setw(2) << d6 << "   " << setw(2) << d7 << endl;

	int c = 0;
	int h = 0;
	bool yes = false;
	while (true)
	{
		yes = false;
		c = 0;



		switch ((c = _getch())) {
		case KEY_UP:
			if (scale < higest/10) {
				scale++;
			}
			yes = true;
			break;
		case KEY_DOWN:
			if (scale > 1) {
				scale--;
			}
			yes = true;
			break;
		case KEY_RIGHT:
			if (scale + 5 < higest / 10) {
				scale += 5;
			}
			yes = true;
			break;
		case KEY_LEFT:
			if (scale - 5 > 1) {
				scale -=5;
			}
			yes = true;
			break;
		default:
			break;
		}

		if (c == '0') { return ; }
		if (yes) {


			system("cls");
			
			cout << "\t\t\t\t WEEKLY PROFIT GRAPH";
			cout << "\t Today date is : " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year - 100 << endl;

			
			cout << "                                       Use arrow keys to scale the graph " << endl;
			cout << "                                     [UP/DOWN->+1/-1] [RIGHT/LEFT->+5/-5]" << endl;
			cout << "                                  ";
			cout << "  RM " <<endl ;
			cout << "                                  ";
			for (int i = 0; i < size; i++) {
				cout << " ";
			}

			cout << "^" << endl;

			higest = 0;
			higest = max(price1, price2);
			higest = max(higest, price3);
			higest = max(higest, price4);
			higest = max(higest, price5);
			higest = max(higest, price6);
			higest = max(higest, price7);


			while (higest % scale != 0) {
				higest++;
			}
			size = to_string(higest).size();
			up1 = true;
			up2 = true;
			up3 = true;
			up4 = true;
			up5 = true;
			up6 = true;
			up7 = true;

			for (int i = higest; i >= scale; i -= scale) {
				cout << "                                  ";
				for (int j = start; j >= 0; j--) {

					if (j == start) {
						cout << setw(size) << i << "|";
					}

					//-------------------price 1
					else if (i < price1 && j == 41) {
						cout << "|";
					}
					else if (i < price1 + scale && j == 40) {
						if (up1) {
							cout << "_";
							up1 = false;
						}
						else {
							cout << b;
						}

					}
					else if (i < price1 && j == 39) {
						cout << "|";
					}

					//-------------------price 2
					else if (i < price2 && j == 36) {
						cout << "|";
					}
					else if (i < price2 + scale && j == 35) {
						if (up2) {
							cout << "_";
							up2 = false;
						}
						else {
							cout << b;
						}
					}
					else if (i < price2 && j == 34) {
						cout << "|";
					}

					//-------------------price 3
					else if (i < price3 && j == 31) {
						cout << "|";
					}
					else if (i < price3 + scale && j == 30) {
						if (up3) {
							cout << "_";
							up3 = false;
						}
						else {
							cout << b;
						}
					}
					else if (i < price3 && j == 29) {
						cout << "|";
					}


					//-------------------price 4
					else if (i < price4 && j == 26) {
						cout << "|";
					}
					else if (i < price4 + scale && j == 25) {
						if (up4) {
							cout << "_";
							up4 = false;
						}
						else {
							cout << b;
						}
					}
					else if (i < price4 && j == 24) {
						cout << "|";
					}

					//-------------------price 5
					else if (i < price5 && j == 21) {
						cout << "|";
					}
					else if (i < price5 + scale && j == 20) {
						if (up5) {
							cout << "_";
							up5 = false;
						}
						else {
							cout << b;
						}
					}
					else if (i < price5 && j == 19) {
						cout << "|";
					}


					//-------------------price 6
					else if (i < price6 && j == 16) {
						cout << "|";
					}
					else if (i < price6 + scale && j == 15) {
						if (up6) {
							cout << "_";
							up6 = false;
						}
						else {
							cout << b;
						}

					}
					else if (i < price6 && j == 14) {
						cout << "|";
					}

					//-------------------price 7
					else if (i < price7 && j == 11) {
						cout << "|";
					}
					else if (i < price7 + scale && j == 10) {
						if (up7) {
							cout << "_";
							up7 = false;
						}
						else {
							cout << b;
						}

					}
					else if (i < price7 && j == 9) {
						cout << "|";
					}
					else {
						cout << " ";
					}
				}
				cout << endl;
			}




			cout << "                                  ";
			for (int i = 0; i < size - 1; i++) {
				cout << " ";
			}
			cout << "0-";
		
			for (int i = 0; i <= start - 7; i++) {
				cout << "-";
			}
			cout << "> DAY FROM MONTH";
			cout << endl;
			cout << "                                  ";
			for (int i = 0; i < size; i++) {
				cout << " ";
			}
			cout << setw(size) << "     " << d1 << "   " << setw(2) << d2 << "   " << setw(2) << d3 << "   " << setw(2) << d4 << "   " << setw(2) << d5 << "   " << setw(2) << d6 << "   " << setw(2) << d7 << endl;
		
		}
	}
}

void PaymentManager::monthGraph(int month, int year) {


	bool check = true;
	int day = 30;

	month--;
	if (month <= 0) {
		month = 12;
		year--;
	}

	int long size = 0;
	int start = 0;

	while (check)
	{

		system("cls");
		cout << "\t\t\t\t\t\t\tMONTHLY PROFIT GRAPH" << endl;
		cout << "\t\t\t\t\t\t" << endl;
		cout << "\t\t\t\t\t\t" << endl;
		cout << "\t\t\t\t\t\t" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tclick 0 to return" << endl;
		
			cout << "\t\t\t\t\t\t\tMonth : " << month << "\tYear : 20" << year << endl;
			cout << "\t\t\t\t\t\t\t\t" << endl;
		

		if (month == 2) {
			day = 28;
		}
		else if (month % 2 == 0) {
			day = 31;
		}
		else {
			day = 30;
		}

		vector<string> date;
		for (int i = 1; i <= day; i++) {
			date.push_back(to_string(i) + "/" + to_string(month) + "/" + to_string(year));
		}

		DatabaseConnection dbConn;
		PreparedStatement* ps;
		ResultSet* rs;

		vector<bool>upBar;

		vector<double> profit;
		for (int i = 0; i < day; i++) {
			ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date = ? AND paid = 'paid'");
			ps->setString(1, date[i]);
			ps->executeQuery();
			rs = ps->executeQuery();
			if (rs->next()) {
				double price = rs->getDouble(1);

				profit.push_back(price);
				upBar.push_back(true);
			}
			else {
				profit.push_back(0);
				upBar.push_back(true);
			}

		}
		int higest = *max_element(profit.begin(), profit.end());


		if (higest < 10) {
			higest = 12;
		}

		int scale = 1;
		char b = 178;


		int temp = higest / pow(10, (to_string(higest).size() - 1));
		temp = temp * pow(10, (to_string(higest).size() - 1));
		scale = temp / 10;
		while (higest % scale != 0) {
			higest++;
		}
		higest += scale;
		size = to_string(higest).size();
		start = 127;
		cout << "           ";
		cout << setw(size + 1) << "RM" << endl;
		cout << "           ";
		cout << setw(size + 1) << "^" << endl;
		for (int i = higest; i >= scale; i -= scale) {
			cout << "           ";
			for (int j = start; j >= 0; j--) {

				if (j == start) {
					cout << setw(size) << i << "|";
				}
				else {
					int l = start - 4;
					int u = start - 5;
					int r = start - 6;
					bool print = true;
					for (int x = 0; x < day && print; x++) {
						if (i <= profit[x] && j == l) {
							cout << "|";
							print = false;
						}
						else if (i <= profit[x] + scale && j == u) {
							if (upBar[x]) {
								cout << "_";
								upBar[x] = false;
							}
							else {
								cout << b;
							}
							print = false;
						}
						else if (i <= profit[x] && j == r) {
							cout << "|";
							print = false;
						}

						l -= 4;
						u -= 4;
						r -= 4;
					}
					if (print) {
						cout << " ";
					}

				}

			}
			cout << endl;
		}
		cout << "           ";
		cout << setw(size) << " 0";
		for (int i = start + 4; i > 0; i--) {
			cout << "-";
		}
		cout << ">Day Of Month" << endl;
		cout << "           ";
		cout << setw(size + 6);
		int space = 0;
		for (int i = 1; i <= day; i++) {

			cout << i;
			space = to_string(i).size();
			for (int j = 0; j < 4 - space; j++) {
				cout << " ";
			}
		}
		cout << endl << endl;
		int z = 0;
		 space = 15;
		 int nspace = 15;
		bool stop = false;
		while (!stop) {
			cout << "             ";
			nspace = 15;
			for (int i = 0; i < 6; i++) {
				if (z < day) {
					int tem = profit[z];
					if (tem == 0) {
						tem = 1;
					}
					tem = to_string(tem * 1000).size();
					cout << setw(nspace) << z + 1 << " = RM" << profit[z++];
					nspace = space - (tem - 4);
				}
				else {
					stop = true;
				}
			}
			cout << endl;
		}

		if (_getch() == '0') {
			return;
		}
	}
}


void PaymentManager::yearlyGraph() {

	time_t now = time(0);
	tm* ltm = localtime(&now);
	time_t current = time(0);

	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	bool check = true, m = true, y = false;
	int month = 12;
	int year = ltm->tm_year - 100;
	int arrow  = 1;

	int long size = 0;
	int start = 0;
	vector<string> date;
	vector<bool>upBar;
	vector<double> profit;
	while (check)
	{
		date.clear();
		upBar.clear();
		profit.clear();
		system("cls");
		cout << "\t\t\t\t\t\t\tYEARLY PROFIT GRAPH" << endl;
		cout << "\t\t\t\t\t\tUse UP AND DOWN Arrow Keys to Change Year" << endl;
		cout << "\t\t\t\t\t\tUse RIGHT AND LEFT Arrow Keys to Select Month" << endl;
		cout << "\t\t\t\t\t\tClick ENTER to See The Monthly Profit" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tclick 0 to return" << endl;
	
			cout << "\t\t\t\t\t\t\tYear : 20" << year << endl;
			cout << "\t\t\t\t\t\t\t\t^" << endl;

		
		for (int i = 1; i <= month; i++) {
			date.push_back("/" + to_string(i) + "/" + to_string(year));
		}

		DatabaseConnection dbConn;
		PreparedStatement* ps;
		ResultSet* rs;

		
		for (int i = 0; i < month; i++) {
			ps = dbConn.prepareStatement("SELECT SUM(price) FROM payment WHERE date LIKE ? AND paid = 'paid'");
			ps->setString(1, "%"+date[i]);
			ps->executeQuery();
			rs = ps->executeQuery();
			if (rs->next()) {
				double price = rs->getDouble(1);
				profit.push_back(price);
				upBar.push_back(true);
			}
			else {
				profit.push_back(0);
				upBar.push_back(true);
			}

		}
		int higest = *max_element(profit.begin(), profit.end());

	
		if (higest < 10) {
			higest = 12;
		}

		int scale = 1;
		char b = 178;


		int temp = higest / pow(10, (to_string(higest).size() - 1));
		temp = temp * pow(10, (to_string(higest).size() - 1));
		scale = temp / 10;
		while (higest % scale != 0) {
			higest++;
		}
		higest += scale;
		size = to_string(higest).size();
		start = 54;
		cout << "                                               ";
		cout << setw(size + 1) << "RM" << endl;
		cout << "                                               ";
		cout << setw(size + 1) << "^" << endl;
		for (int i = higest; i >= scale; i -= scale) {
			cout << "                                               ";
			for (int j = start; j >= 0; j--) {

				if (j == start) {
					cout << setw(size) << i << "|";
				}
				else {
					int l = start - 4;
					int u = start - 5;
					int r = start - 6;
					bool print = true;
					for (int x = 0; x < month && print; x++) {
						if (i <= profit[x] && j == l) {
							cout << "|";
							print = false;
						}
						else if (i <= profit[x] + scale && j == u) {
							if (upBar[x]) {
								cout << "_";
								upBar[x] = false;
							}
							else {
								cout << b;
							}
							print = false;
						}
						else if (i <= profit[x] && j == r) {
							cout << "|";
							print = false;
						}

						l -= 4;
						u -= 4;
						r -= 4;
					}
					if (print) {
						cout << " ";
					}

				}

			}
			cout << endl;
		}
		cout << "                                               ";
		cout << setw(size) << " 0";
		for (int i = start + 4; i > 0; i--) {
			cout << "-";
		}
		cout << ">Month Of Year" << endl;
		cout << "                                               ";
		cout << setw(size + 6);
		int space = 0;
		for (int i = 1; i <= month; i++) {

			cout << i;
			space = to_string(i).size();
			for (int j = 0; j < 4 - space; j++) {
				cout << " ";
			}
		}
		cout << endl;
		cout << "                                               ";
		cout << setw(size + 6);
		for (int i = 1; i <= month; i++) {
			space = to_string(i).size();
			if (arrow == i) {
				cout << "^";
			}
			else {
				for (int j = 0; j < space; j++) {
					cout << " ";
				}
			}
			
			for (int j = 0; j < 4 - space; j++) {
				cout << " ";
			}
		}
		cout << endl;
		cout << "                                               ";
		cout << setw(size + 6);
		for (int i = 1; i <= month; i++) {

			space = to_string(i).size();
			if (arrow == i) {
				cout << "|";
			}
			else {
				for (int j = 0; j <space; j++) {
					cout << " ";
				}
			}
			space = to_string(i).size();
			for (int j = 0; j < 4 - space; j++) {
				cout << " ";
			}
		}
		cout << endl << endl;
		 int nspace = 15;
		 space = 15;
		int z = 0;
		bool stop = false;
		while (!stop) {
			cout << "             ";
			nspace = 15;
			for (int i = 0; i < 6; i++) {
				if (z < month) {
					int tem = profit[z];
					if (tem == 0){
						tem = 1;
					}
					tem = to_string(tem*1000).size();
					cout << setw(nspace) << z + 1 << " = RM" <<profit[z++];
					nspace = space - (tem - 4);
				}
				else {
					stop = true;
				}
			}
			cout << endl;
		}

		int c = _getch();
		if (c == '0') {
			check = false;
		}
		else if (c == '\r') {
			monthGraph(arrow +1, year);
		}
		if (c == 224) {

			int key = _getch();

			switch ((key)) {
			case KEY_UP:
					year++;
				break;
			case KEY_DOWN:
					year--;
				break;
			case KEY_LEFT:
				if (arrow > 1) {
					arrow--;
				}
				else {
					arrow = 12;
				}
				break;
			case KEY_RIGHT:
				if (arrow < 12) {
					arrow++;
				}
				else {
					arrow = 1;
				}
				break;
			default:
				break;
			}
		}

	}
}