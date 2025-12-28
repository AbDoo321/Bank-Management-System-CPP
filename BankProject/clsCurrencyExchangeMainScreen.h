#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{

private:
	enum enCurrencyExchangeMenuOption {
		eListCurrencies = 1, eFindCurrency, eUpdateCurrency, eCurrencyCalculator, GoBackToMainMenu
	};


	static short _ReadCurrencyExchangeMenuOption() {
		short FirstChoiceNumber = 1, LastChoiceNumber = enCurrencyExchangeMenuOption::GoBackToMainMenu;

		cout << "Choose what do you want to do ["
			<< FirstChoiceNumber << " to " << LastChoiceNumber << "]? : " << endl;
		short Choice = clsInputValidate::ReadIntNumberBetween(FirstChoiceNumber, LastChoiceNumber,
			"Enter a number between " + to_string(FirstChoiceNumber)
			+ " and " + to_string(LastChoiceNumber) + " : ");
		return Choice;
	}

	static void _GoBackToCurrencyExchangeMainScreen() {
		cout << "\n\nPress any key to go back to Currency Exchange Menu...";
		system("pause>0");
		ShowCurrencyExchangeMainScreen();
	}

	static void _ShowCurrenciesList() {
		//cout << "Currencies List Screen Code..." << endl;
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindCurrencyScreen() {
		//cout << "Find Currency Screen Code..." << endl;
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateCurrencyScreen() {
		//cout << "Update Currency Screen Code..." << endl;
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCurrencyCalculatorScreen() {
		//cout << "Currency Calculator Screen Code..." << endl;
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}
	static void _PerformCurrenciesExchangeMenuOption(enCurrencyExchangeMenuOption Option) {
		
		switch (Option)
		{
		case clsCurrencyExchangeMainScreen::eListCurrencies:
			system("cls");
			_ShowCurrenciesList();
			_GoBackToCurrencyExchangeMainScreen();
			break;
		case clsCurrencyExchangeMainScreen::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMainScreen();
			break;
		case clsCurrencyExchangeMainScreen::eUpdateCurrency:
			system("cls");
			_ShowUpdateCurrencyScreen();
			_GoBackToCurrencyExchangeMainScreen();
			break;
		case clsCurrencyExchangeMainScreen::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMainScreen();
			break;
		case clsCurrencyExchangeMainScreen::GoBackToMainMenu:
			break;
		default:
			break;
		}
	}

public:

	static void ShowCurrencyExchangeMainScreen() {

		if (!_CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
			return;
		system("cls");
		_PrintScreenHeader("Currency Exchange Main Menu");

		cout << "\n==========================================================\n";
		cout << "\t\tCurrency Exchange Menu";
		cout << "\n==========================================================\n";
		cout << "\t[1] Currencies List.\n";
		cout << "\t[2] Find Currency.\n";
		cout << "\t[3] Update Currency.\n";
		cout << "\t[4] Currency Calculator.\n";
		cout << "\t[5] Go back to Main Menu.\n";
		cout << "==========================================================" << endl;

		_PerformCurrenciesExchangeMenuOption((enCurrencyExchangeMenuOption)_ReadCurrencyExchangeMenuOption());
	}
};

