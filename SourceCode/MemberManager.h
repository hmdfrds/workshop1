#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

class MemberManager
{
public:
	int insertMember(Member* member);
	Member* selectMember(string memberID);
	Member* selectMemberNo(int NO);
	int updateMember(string ID, string att, string data);
	bool login(Member* member);
	int deleteMember(string ID);
	void showAllMember();
	int updateMembershipTime();

	int checkMemberTime(string ID);

	int searchMember(int lastMemberID);

	int addMembershipTime(string memberID, int day);




};

#endif 
