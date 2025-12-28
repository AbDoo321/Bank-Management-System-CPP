#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void PrintLoginRegisterRecord(clsUser::stLoginRegisterRecord LoginRegisterRecord) {
		cout << setw(8) << left << "";
		cout << "|" << setw(35) << left << LoginRegisterRecord.DateTime;
		cout << "|" << setw(20) << left << LoginRegisterRecord.UserName;
		cout << "|" << setw(20) << left << LoginRegisterRecord.Password;
		cout << "|" << setw(10) << left << LoginRegisterRecord.Permissions;
	}


public:
	static void ShowLoginRegisterScreen() {

		if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegisterList))
			return;

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecords = clsUser::GetLoginRegisterList();
		string Title = "Login Register Screen";
		string subTitle = to_string(vLoginRegisterRecords.size()) + " Record(s).";
		_PrintScreenHeader(Title, subTitle);

		cout << setw(8) << left << ""
			 << "==================================================================================================\n";
		cout << setw(8) << left << "";
		cout << "|" << setw(35) << left << "DateTime";
		cout << "|" << setw(20) << left << "UserName";
		cout << "|" << setw(20) << left << "Password";
		cout << "|" << setw(10) << left << "Permissions";

		cout << endl << setw(8) << left << ""
			<< "==================================================================================================\n";

		if (vLoginRegisterRecords.empty())
			cout << "No Logins Available in the System !" << endl;
		else 
			for (clsUser::stLoginRegisterRecord& LoginRecord : vLoginRegisterRecords) 
			{
				PrintLoginRegisterRecord(LoginRecord);
				cout << endl;
			}

		cout << setw(8) << left << ""
			<< "==================================================================================================\n";
	}
};

