#pragma once
#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientUtil.h"
using namespace std;
class clsAddNewClientScreen : protected clsScreen
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
	static void ShowAddNewClientScreen() {

        if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            return;

		//_DrawScreenHeader("\tAdd New Client Screen");
        clsScreen::_PrintScreenHeader("Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::isClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            clsClientUtil::PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFailedAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }
	
};

