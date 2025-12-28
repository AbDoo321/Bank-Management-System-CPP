#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n===============\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number  : " << Client.AccountNumber();
		cout << "\nAcc. Balance: " << Client.getAccountBalance();
		cout << "\n===============" << endl;

	}
	static string _ReadAccountNumber() {
		string AccountNumber = "";
		cout << "\nEnter The Account Number of the Client to Find :";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nClient Not Found, Enter another Account Number :";
			AccountNumber = clsInputValidate::ReadString();

			return AccountNumber;
		}
	}
	static double _ReadAmount(clsBankClient SourceClient) {
		double Amount = 0;
		cout << "enter the Amount: ";
		Amount = clsInputValidate::ReadDblNumber();
		while (Amount > SourceClient.getAccountBalance()) 
		{
			cout << "Amount exceeds the available Balance (" << SourceClient.getAccountBalance() << "), ";
			cout << "Enter another Amount : ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}


public:

	static void ShowTransferScreen() {

		_PrintScreenHeader("Transfer Screen");

		string AccountNumber1 = _ReadAccountNumber();
		clsBankClient SourceClient = clsBankClient::Find(AccountNumber1);
		_PrintClient(SourceClient);
		
		string AccountNumber2 = _ReadAccountNumber();
		clsBankClient DestinationClient = clsBankClient::Find(AccountNumber2);
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this Operation ? (y/n) ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			if (clsBankClient::Transfer(SourceClient, DestinationClient, Amount, CurrentUser.getUserName()))
				cout << "\nTransfer Done Successfully" << endl;
			else
				cout << "\nTransfer Failed" << endl;
		}
		else
			cout << "Transfer Canceled" << endl;
 
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);

	}
};

