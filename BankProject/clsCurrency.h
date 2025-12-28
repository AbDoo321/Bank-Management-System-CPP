#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
using namespace std;
const string CurrenciesFileName = "CurrenciesFile.txt";

class clsCurrency
{
private:
	
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
	
	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#") {
		vector <string> vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData.at(0),vCurrencyData.at(1),
											   vCurrencyData.at(2), stof(vCurrencyData.at(3)) );
	}
	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#") {
		string Line = "";

		Line += Currency._Country + Separator;
		Line += Currency._CurrencyCode + Separator;
		Line += Currency._CurrencyName + Separator;
		Line += to_string(Currency._Rate);

		return Line;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {
		fstream CurrenciesFile;
		vector <clsCurrency> vCurrencies;

		CurrenciesFile.open(CurrenciesFileName, ios::in); //read mode
		if (CurrenciesFile.is_open()) 
		{
			string Line = "";
			clsCurrency Currency = _GetEmptyCurrencyObject();
			while (getline(CurrenciesFile, Line)) 
			{
				Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			CurrenciesFile.close();
		}
		return vCurrencies;
	}
	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies) 
	{
		fstream CurrenciesFile;
		CurrenciesFile.open(CurrenciesFileName, ios::out); //overwrite the file

		if (CurrenciesFile.is_open())
		{
			string CurrencyDataLine = "";
			for (clsCurrency& Currency : vCurrencies) 
			{
				CurrencyDataLine = _ConvertCurrencyObjectToLine(Currency);
				CurrenciesFile << CurrencyDataLine << endl;
			}
			CurrenciesFile.close();
		}
	}

	void _Update() {
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& Currency : vCurrencies) 
			if (Currency._CurrencyCode == _CurrencyCode)// it means this->_CurrencyCode
			{
				Currency = *this;
				break;
			}
		_SaveCurrenciesDataToFile(vCurrencies);
		
	}



public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	string Country() {
		return _Country;
	}
	string CurrencyCode() {
		return _CurrencyCode;
	}
	string CurrencyName() {
		return _CurrencyName;
	}
	float Rate() {
		return _Rate;
	}
	void UpdateRate(float NewRate) 
	{
		_Rate = NewRate;
		_Update();
	}
	
	bool isEmpty() {
		return _Mode == enMode::EmptyMode;
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream CurrenciesFile;
		
		CurrenciesFile.open(CurrenciesFileName, ios::in); //read mode
		if (CurrenciesFile.is_open())
		{
			string Line = "";
			clsCurrency Currency = _GetEmptyCurrencyObject();
			while (getline(CurrenciesFile, Line))
			{
				Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency._CurrencyCode == CurrencyCode) //no need to UpperAll to CurrencyCode 
				{
					CurrenciesFile.close();
					return Currency;
				}
			}
			CurrenciesFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static clsCurrency FindByCountry(string Country) {

		Country = clsString::UpperAllString(Country);
		fstream CurrenciesFile;

		CurrenciesFile.open(CurrenciesFileName, ios::in); //read mode
		if (CurrenciesFile.is_open())
		{
			string Line = "";
			clsCurrency Currency = _GetEmptyCurrencyObject();
			while (getline(CurrenciesFile, Line))
			{
				Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency._Country) == Country)
				{
					CurrenciesFile.close();
					return Currency;
				}
			}
			CurrenciesFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string CurrencyCode) {
		clsCurrency Currency = FindByCode(CurrencyCode);
		return !Currency.isEmpty();
 	}


	static vector <clsCurrency> GetCurrenciesList() {
		return _LoadCurrenciesDataFromFile();
	}

	double ConvertToUSD(double Amount) {
		return (double)(Amount / this->_Rate);
	}
	double ConvertToOtherCurrency(double Amount, clsCurrency CurrencyTo) {
		double AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyTo._CurrencyCode == "USD")
			return AmountInUSD;

		return (double)(AmountInUSD * CurrencyTo._Rate);
	}

};

