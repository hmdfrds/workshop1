#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "NonMember.h"
#include "NonMemberManager.h"

int NonMemberManager::insertNonMember(NonMember* nonMember)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO member VALUES (?, ?, ?)");

	ps->setString(1, nonMember->IC);
	ps->setString(2, nonMember->name);
	ps->setString(3, nonMember->noTel);



	int status = ps->executeUpdate();

	delete ps;

	return status;
}
