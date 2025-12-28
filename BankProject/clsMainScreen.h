#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenuOption {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eShowTransactionsMenu = 6, eManageUsers = 7,
		eRegisterLogin = 8, eCurrencyExchange, eExit 
	};

	static short _ReadMainMenuOption() {
		short FirstChoiceNumber = 1, LastChoiceNumber = enMainMenuOption::eExit;

		cout << "Choose what do you want to do ["
			<< FirstChoiceNumber << " to " << LastChoiceNumber << "]? : " << endl;
		short Choice = clsInputValidate::ReadIntNumberBetween(FirstChoiceNumber, LastChoiceNumber,
			"Enter a number between " + to_string(FirstChoiceNumber)
			+ " and " + to_string(LastChoiceNumber) + " : ");
		return Choice;
	}

	static void _GoBackToMainMenu() {
		cout << "\n\nPress any key to go back to Main Menu...";
		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen() {
		clsClientsListScreen::ShowClientsList();
	}
	static void _ShowAddNewClientsScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}
	static void _ShowDeleteClientScreen() {
		//cout << "\nDelete Clients Screen code..." << endl;
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientScreen() {
		//cout << "\nUpdating Clients Screen code..." << endl;
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindClientScreen() {
		//cout << "\nFind Client Screen code..." << endl;
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _ShowTransactionsScreen() {
		//cout << "\nTransactions Screen code..." << endl;
		clsTransactionsScreen::ShowTransactionsMenu();
	}
	static void _ShowManageUsersScreen() {
		//cout << "\nManage Users Screen code..." << endl;
		clsManageUsers::ShowManageUsersScreen();
	}
	static void _ShowLoginRegisterScreen() {
		//cout << "Login Register Screen Code..." << endl;
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void _ShowCurrencyExchangeMainScreen() {
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainScreen();
	}
	static void _Logout() {
		CurrentUser = clsUser::Find("", "");

	}
	/*static void _ShowEndScreen()
{
	cout << "\nEnd Screen code..." << endl;
}*/

	static void _PerformMainMenuOption(enMainMenuOption Option) {
		switch (Option)
		{
		case enMainMenuOption::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eShowTransactionsMenu:
			system("cls");
			_ShowTransactionsScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eManageUsers:
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eRegisterLogin:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eExit:
			system("cls");
			_Logout();
			break;
		}

	};

public:

	static void ShowMainMenu() {
		system("cls");
		//_DrawScreenHeader("Main Screen");
		clsScreen::_PrintScreenHeader("Main Menu");

		cout << "\n==========================================================\n";
		cout << "\t\t\tMain Menu";
		cout << "\n==========================================================\n";
		cout << "\t[1] Show Clients List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] Login Register.\n";
		cout << "\t[9] Currency Exchange.\n";
		cout << "\t[10] Logout.\n";
		cout << "==========================================================" << endl;
		_PerformMainMenuOption((enMainMenuOption)_ReadMainMenuOption());
	}
	

};