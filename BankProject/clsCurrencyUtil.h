#pragma once
#include <iostream>
#include "clsCurrency.h"

using namespace std;


class clsCurrencyUtil
{
public:

	static void PrintCurrencyCard(clsCurrency Currency) {
		cout << "\nCurrency Card :";
		cout << "\n____________________________";
		cout << "\nCountry: " << Currency.Country();
		cout << "\nCode: " << Currency.CurrencyCode();
		cout << "\nName: " << Currency.CurrencyName();
		cout << "\nRate(1$): " << Currency.Rate();
		cout << "\n____________________________" << endl;
	}

};

