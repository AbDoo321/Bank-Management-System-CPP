#pragma once
#include <iostream>
#include <vector>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
using namespace std;


class clsClientsListScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient& Client) {
		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.getPhone();
		cout << "| " << setw(20) << left << Client.getEmail();
		cout << "| " << setw(10) << left << Client.getPinCode();
		cout << "| " << setw(12) << left << Client.getAccountBalance();
	}
public:

	static void ShowClientsList() {

		if (!_CheckAccessRights(clsUser::enPermissions::pClientsList))
			return;

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "Clients List Screen";
		string subTitle = "(" + to_string(vClients.size()) + ") Client(s).";

		//clsScreen::_DrawScreenHeader(Title, subTitle);
		clsScreen::_PrintScreenHeader(Title, subTitle);

		if (vClients.empty()) {
			cout << "\t\t\tNo Client Available In the System!" << endl;
		}
		else{
			cout << setw(8) << left << "" <<
			"==========================================================================="
			<< "=============================\n";
			cout << setw(8) << left << "" << "| " << setw(15) << left << "Account Number";
			cout << "| " << setw(20) << left << "FullName";
			cout << "| " << setw(12) << left << "Phone";
			cout << "| " << setw(20) << left << "Email";
			cout << "| " << setw(10) << left << "PinCode";
			cout << "| " << setw(12) << left << "Account Balance" << endl;
			cout << setw(8) << left << "" <<
			"==========================================================================="
			<< "=============================\n";

			for (clsBankClient& Client : vClients) {
				_PrintClientRecordLine(Client);
				cout << endl;
			}
			cout << setw(8) << left << "" <<
			"==========================================================================="
			<< "=============================\n";
		}
	}
};



