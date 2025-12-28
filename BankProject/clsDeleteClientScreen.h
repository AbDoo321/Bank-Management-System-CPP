#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientUtil.h"
using namespace std;
class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen() {

        if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
            return;

        //_DrawScreenHeader("\tDelete Client Screen");
        clsScreen::_PrintScreenHeader("Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter an Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::isClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            if (Client1.Delete()) {
                cout << "\nClient Deleted Successfully :-)\n";
                clsClientUtil::PrintClient(Client1);
            }
            else
                cout << "\nError Client Was not Deleted\n";
        }
	}
};

