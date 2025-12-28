#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"


using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static double _ReadRate() {
		double Rate = 0;
		cout << "\nEnter New Rate : ";
		Rate = clsInputValidate::ReadDblNumber();
		return Rate;
	}
	static void _PrintCurrencyCard(clsCurrency Currency) {
		cout << "\nCurrency Card :";
		cout << "\n____________________________";
		cout << "\nCountry: " << Currency.Country();
		cout << "\nCode: " << Currency.CurrencyCode();
		cout << "\nName: " << Currency.CurrencyName();
		cout << "\nRate(1$): " << Currency.Rate();
		cout << "\n____________________________" << endl;
	}


public:
	static void ShowUpdateCurrencyRateScreen() {
		_PrintScreenHeader("Update Currency Rate Screen");

		string CurrencyCode = "";
		cout << "\nEnter the Currency Code : ";
		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "Currency was NOT Found, Enter another Currency Code :";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		cout << "Do you want to update this Currency Rate ? (y/n) : ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') 
		{
			cout << "\n\nUpdate Currency Rate :";
			cout << "\n__________________________\n";
			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency was Updated successfully !" << endl;
			_PrintCurrencyCard(Currency);

		}
		else 
		{
			cout << "\nOperation was Cancelled" << endl;
		}




	}

};

