#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientUtil.h"
using namespace std;

class clsFindClientScreen : clsScreen
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

public:
	static void ShowFindClientScreen() {

		if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
			return;

		//_DrawScreenHeader("Find Client Screen");
		clsScreen::_PrintScreenHeader("Find Client Screen");


		string AccountNumber = "";
		cout << "\nEnter The Account Number of the Client to Find :";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::isClientExist(AccountNumber)) {
			cout << "\nClient Not Found, Enter another Account Number :";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.isEmpty())
			cout << "\nClient Found." << endl;
		else
			cout << "\nClient NOT Found." << endl;


		clsClientUtil::PrintClient(Client);
	}

};

