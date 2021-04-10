#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H
#include "Allocating.h"
#include "Payment.h"
class PaymentManager
{
public:



	void addIntoList(Allocating* allocate);

	Payment* selectPaymentNo(int NO);

	void paid(string paymentID);

	int showUnpaid();

	void showAll();

	void graph(string today);

	void scaledGraph(string today);

	void monthGraph(int month, int year);

	

	void yearlyGraph();

	

	


};

#endif