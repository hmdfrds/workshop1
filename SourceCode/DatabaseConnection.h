#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

class DatabaseConnection
{
private:
	Connection* connection;

public:
	DatabaseConnection();
	~DatabaseConnection();

	PreparedStatement* prepareStatement(string query);
};

#endif