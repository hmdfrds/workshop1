#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

class AdminManager
{
public:
	int insertAdmin(Admin* admin);
	int updateAdmin(string ID, string att, string data);
	Admin* selectAdmin(string adminID);
	Admin* selectAdminNO(int no);
	bool login(Admin* admin);
	int deleteAdmin(string ID);
	void showAllAdmin();
	int searchAdmin(int lastAdminID);
};

#endif 
