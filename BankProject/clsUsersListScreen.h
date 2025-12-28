#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsUsersListScreen : protected clsScreen
{ 
private:
	static void _PrintUserRecord(clsUser User) {
		cout << setw(10) << left << "" << "|" << setw(15) << left << User.getUserName();
		cout << "|" << setw(30) << left << User.FullName();
		cout << "|" << setw(12) << left << User.getPhone();
		cout << "|" << setw(20) << left << User.getEmail();
		cout << "|" << setw(10) << left << User.getPassword();
		cout << "|" << setw(12) << left << User.getPermissions();
	}

public:

	static void ShowUsersListScreen() {

		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "Users List Screen";
		string subTitle = "(" + to_string(vUsers.size()) + ") User(s).";
		_PrintScreenHeader(Title, subTitle);

		cout << "\n\n\t  ========================================================================================================\n";
		cout << setw(10) << left << "" << "|" << setw(15) << left << "UserName";
		cout << "|" << setw(30) << left << "Full Name";
		cout << "|" << setw(12) << left << "Phone";
		cout << "|" << setw(20) << left << "Email";
		cout << "|" << setw(10) << left << "Password";
		cout << "|" << setw(12) << left << "Permissions";
		cout << "\n\t  ========================================================================================================\n";
		if (vUsers.empty())
			cout << "\t\t\t\t\t\tNo Users in the system" << endl;
		else
			for (clsUser& User : vUsers)
			{
				_PrintUserRecord(User);
				cout << endl;
			}
				cout << "\t  ========================================================================================================\n";
			
	}

};

