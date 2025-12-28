#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientUtil.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "\nEnter FirstName: ";
		Client.setFirstName(clsInputValidate::ReadString());

		cout << "\nEnter LastName: ";
		Client.setLastName(clsInputValidate::ReadString());

		cout << "\nEnter Email: ";
		Client.setEmail(clsInputValidate::ReadString());

		cout << "\nEnter Phone: ";
		Client.setPhone(clsInputValidate::ReadString());

		cout << "\nEnter PinCode: ";
		Client.setPinCode(clsInputValidate::ReadString());

		cout << "\nEnter Account Balance: ";
		Client.setAccountBalance(clsInputValidate::ReadFloatNumber());
	}
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

	static void ShowUpdateClientScreen() {

        if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClient))
            return;

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::isClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        { 
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded: 
                {
                cout << "\nAccount Updated Successfully :-)\n";
                clsClientUtil::PrintClient(Client1);
                break;
                }
            case clsBankClient::enSaveResults::svFailedEmptyObject:
            
                cout << "\nError account was not saved because it's Empty";
                break;
            }

        }

	}

};

