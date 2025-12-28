#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;
class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenuOption {
		eDeposit = 1, eWithdraw, eShowTotalBalances,
		eTransfer, eTransferLog, eGoBackToMainMenu
	};

	static short _ReadTransactionsMenuOption() {
		short FirstChoiceNumber = 1, LastChoiceNumber = eGoBackToMainMenu;

		cout << "Choose what do you want to do ["
			<< FirstChoiceNumber << " to " << LastChoiceNumber << "]? : " << endl;
		short Choice = clsInputValidate::ReadIntNumberBetween(FirstChoiceNumber, LastChoiceNumber,
			"Enter a number between " + to_string(FirstChoiceNumber)
			+ " and " + to_string(LastChoiceNumber) + " : ");
		return Choice;
	}

	static void _GoBackToTransactionsMenu() {
		cout << "Press any key to go back to Transactions Menu...";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _ShowDepositScreen() {
		//cout << "Deposit Screen code..." << endl;
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen() {
		//cout << "Withdraw Screen code..." << endl;
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		//cout << "Total Balances Screen code..." << endl;
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}
	static void _ShowTransferScreen() {
		//cout << "Transfer Screen code..." << endl;
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen() {
		//cout << "Transfer log screen code..." << endl;
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionsMenuOption(enTransactionsMenuOption Option) {
		switch (Option)
		{
		case enTransactionsMenuOption::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::eShowTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOption::eGoBackToMainMenu:
			return;//Nothing here the code is in main Menu 
			break;
		}
	
	}

public:

	static void ShowTransactionsMenu() {

		if (!_CheckAccessRights(clsUser::enPermissions::pTransactions))
			return;

		system("cls");
		_PrintScreenHeader("Transaction Screen");

		cout << "\n=============================================\n";
		cout << "\t\t\Transaction Menu";
		cout << "\n=============================================\n";
		cout << "\t[1] Deposit.\n";
		cout << "\t[2] Withdraw.\n";
		cout << "\t[3] Show Total Balances.\n";
		cout << "\t[4] Transfer.\n";
		cout << "\t[5] Transfer Log.\n";
		cout << "\t[6] Go Back to Main Menu.\n";
		cout << "=============================================" << endl;

		_PerformTransactionsMenuOption((enTransactionsMenuOption)_ReadTransactionsMenuOption());
	}
};

