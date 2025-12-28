#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static double _ReadAmount() {
		cout << "Enter the Amount to Exchange: ";
		double Amount = clsInputValidate::ReadDblNumber();
		return Amount;
	}

	static clsCurrency _GetCurrency(string Message) {

		cout << Message << endl;
		string CurrencyCode = "";

		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "Currency was NOT Found, Enter another Currency Code :";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {
		cout << "\n" << Title;
		cout << "\n____________________________";
		cout << "\nCountry: " << Currency.Country();
		cout << "\nCode: " << Currency.CurrencyCode();
		cout << "\nName: " << Currency.CurrencyName();
		cout << "\nRate(1$): " << Currency.Rate();
		cout << "\n____________________________" << endl;
	}

	static void _PrintCalculationsResults(double Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrencyCard(CurrencyFrom, "Converting from :");
		double AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " USD" << endl;

		if (CurrencyTo.CurrencyCode() == "USD")
			return;
		
		//cout << "\nConverting from USD to :\n";
		_PrintCurrencyCard(CurrencyTo, "Converting from USD to :");
		double AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " 
			 << AmountInCurrencyTo << " " << CurrencyTo.CurrencyCode() << endl;





	}


public:
	static void ShowCurrencyCalculatorScreen() {

		char Continue = 'Y';
		while (Continue == 'Y' || Continue == 'y') 
		{
			system("cls");
			_PrintScreenHeader("Currency Calculator Screen");
			clsCurrency CurrencyFrom = _GetCurrency("Enter CurrencyFrom Code:");
			clsCurrency CurrencyTo = _GetCurrency("Enter CurrencyTo Code:");
			double Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\nDo you want to perform another Calculation ? y/n " << endl;
			cin >> Continue;
		}
	}
};

