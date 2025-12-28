#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsers : protected clsScreen
{
private:
	enum enManageUsersOption {
		eListUsers = 1, eAddNewUser, eDeleteUser,
		eUpdateUser, eFindUser, eMainMenu = 6
	};

	static short _ReadManageUsersMenuOption() {
		short FirstChoiceNumber = 1, LastChoiceNumber = 6;

		cout << "Choose what do you want to do [" << FirstChoiceNumber << " to "
			<< LastChoiceNumber << "]? : " << endl;

		string ErrorMessage = "Enter a number between " + to_string(FirstChoiceNumber)
							+ " and " + to_string(LastChoiceNumber) + " : ";

		short Choice = clsInputValidate::ReadIntNumberBetween(FirstChoiceNumber, LastChoiceNumber,
																ErrorMessage);
		return Choice;
	}
	static void _GoBackToManageUsersMenu() {
		cout << "\n\nPress any key to go back to Manage Users Menu..." << endl;
		system("pause>0");
		ShowManageUsersScreen();
	}

	static void _ShowUsersListScreen() {
		//cout << "Users List Screen Code..." << endl;
		clsUsersListScreen::ShowUsersListScreen();
	}
	static void _ShowAddNewUserScreen() {
		//cout << "Add New User Screen Code..." << endl;
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUserScreen() {
		//cout << "Delete User Screen Code..." << endl;
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen() {
		//cout << "Update User Screen Code..." << endl;
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindUserScreen() {
		//cout << "Find User Screen Code..." << endl;
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenuOption(enManageUsersOption Option) {
		switch (Option)
		{
		case clsManageUsers::eListUsers:
			system("cls");
			_ShowUsersListScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eMainMenu:

			break;
		default:
			break;
		}
	}

public:

	static void ShowManageUsersScreen() {

		if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
			return;

		system("cls");
		_PrintScreenHeader("Manage Users Screen");

		cout << "\n==========================================================\n";
		cout << "\t\t\tManage Users Menu";
		cout << "\n==========================================================\n";
		cout << "\t[1] Show Users List.\n";
		cout << "\t[2] Add New User.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User Info.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Back to Main Menu.\n";
		cout << "==========================================================" << endl;

		_PerformManageUsersMenuOption((enManageUsersOption)_ReadManageUsersMenuOption());
	}
};

