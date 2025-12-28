#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsClientUtil.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& Client) {
		cout << "\nClient Info:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.getFirstName();
		cout << "\nLastName    : " << Client.getLastName();
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nEmail       : " << Client.getEmail();
		cout << "\nPhone       : " << Client.getPhone();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPinCode     : " << Client.getPinCode();
		cout << "\nBalance     : " << Client.getAccountBalance();
		cout << "\n___________________" << endl;
	}
	static string _ReadAccountNumber(string message = "\nPlease enter AccountNumber? ") {
		string AccountNumber = "";
		cout << message;
		AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}


public:

	static void ShowWithdrawScreen() {

		_PrintScreenHeader("Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::isClientExist(AccountNumber)) {
			cout << "\nClient with AccountNumber [" << AccountNumber << "] does NOT exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		clsClientUtil::PrintClient(Client);

		double Amount = 0;
		cout << "Enter the Amount to Withdraw: ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you Want to Perform this Transaction ? ";
		char Answer = 'N';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Withdraw(Amount)) {
				cout << "\nTransactions done Successfully.";
				cout << "\nNew Balance is : " << Client.getAccountBalance() << endl;
			}
			else {
				cout << "\nCannot Withdraw, Insufficient Balance!";
				cout << "\nAmount to Withdraw = " << Amount;
				cout << "\nYour Balance is = " << Client.getAccountBalance() << endl;
			} 
		}
		else
			cout << "\nTransaction Cancelled.\n" << endl;

	}

};

