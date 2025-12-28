#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsCurrency.h"
#include "clsScreen.h"
 

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecord(clsCurrency Currency) {
		cout << setw(10) << left << "" << "|" << setw(30) << left << Currency.Country();
		cout << "|" << setw(8) << left << Currency.CurrencyCode();
		cout << "|" << setw(50) << left << Currency.CurrencyName();
		cout << "|" << setw(12) << left << Currency.Rate();
	}

public:

	static void ShowCurrenciesListScreen() {
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "Currencies List Screen";
		string subTitle = "(" + to_string(vCurrencies.size()) + ") Currencies.";
		_PrintScreenHeader(Title, subTitle);

		cout << setw(10) << left << "" <<
			"==========================================================================="
			<< "=============================\n";		
		cout << setw(10) << left << "" << "|" << setw(30) << left << "Country";
		cout << "|" << setw(8) << left << "Code";
		cout << "|" << setw(50) << left << "Name";
		cout << "|" << setw(12) << left << "Rate/(1$)";
		cout << endl << setw(10) << left << "" <<
			"==========================================================================="
			<< "=============================\n";		if (vCurrencies.empty())
			cout << "\t\t\t\t\t\tNo Currencies in the system" << endl;
		else
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyRecord(Currency);
				cout << endl;
			}
		cout << setw(10) << left << "" <<
			"==========================================================================="
			<< "=============================" << endl;
	

	}
};

