#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h" 
using namespace std;
class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum enFindBy { eByCode = 1, eByCountry = 2 };

	static void _PrintCurrencyCard(clsCurrency Currency) {
		cout << "\nCurrency Card :";
		cout << "\n____________________________";
		cout << "\nCountry: " << Currency.Country();
		cout << "\nCode: " << Currency.CurrencyCode();
		cout << "\nName: " << Currency.CurrencyName();
		cout << "\nRate(1$): " << Currency.Rate();
		cout << "\n____________________________" << endl;
	}
	static enFindBy _ReadFindBy() {
		cout << "Find By: [1] Code or [2] Country ? ";
		short Answer = 0;
		Answer = clsInputValidate::ReadIntNumberBetween(1, 2);
		return (enFindBy) Answer;
	}
	static void _ShowResults(clsCurrency Currency) {
		if (!Currency.isEmpty()) {
			cout << "\nCurrency is Found : \n";
			_PrintCurrencyCard(Currency);
		}
		else
			cout << "\nCurrency Not Found!" << endl;
	}
public:

	static void ShowFindCurrencyScreen() {
		_PrintScreenHeader("Find Currency Screen");
		enFindBy FindBy = _ReadFindBy();
		if (FindBy == enFindBy::eByCode)
		{
			cout << "Enter Currency Code : ";
			string CurrencyCode = clsString::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else     // (FindBy == clsFindCurrencyScreen::eByCountry)
		{
			cout << "Enter Currency Country : ";
			string Country = clsString::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);

		}
		

	}

};

