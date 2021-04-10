#include <string>
using namespace std;

#ifndef PAYMENT_H
#define PAYMENT_H

class Payment
{
public:
	string  paymentID, userID, computerID, totalTime, date , paid;
	int NO = 0;
	double price = 0;

};

#endif