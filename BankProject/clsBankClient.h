#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"


using namespace std;
//const string ClientsFileName = "C:\\Users\\PC\\Desktop\\Programming Advices courses\\course11\\BankProject\\Clients.txt";
const string ClientsFileName = "ClientsFile.txt";
const string TransferLogFileName = "TransferLog.txt";

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
		vector <string> vClientData(6);
		vClientData = clsString::Split(Line, Separator);
		return clsBankClient(enMode::UpdateMode, vClientData.at(0), vClientData.at(1), vClientData.at(2),
			vClientData.at(3), vClientData.at(4), vClientData.at(5), stof(vClientData.at(6)));
	}
	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
		string Line = "";
		Line += Client.getFirstName() + Separator;
		Line += Client.getLastName() + Separator;
		Line += Client.getEmail() + Separator;
		Line += Client.getPhone() + Separator;
		Line += Client._AccountNumber + Separator;
		Line += Client._PinCode + Separator;
		Line += to_string(Client._AccountBalance);

		return Line;
	}
	static clsBankClient _GetEmptyClientObject() {
		return 	clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector <clsBankClient> _LoadClientsDataFromFile() {
		fstream ClientsFile;
		vector <clsBankClient> vClients;
		ClientsFile.open(ClientsFileName, ios::in);
		if (ClientsFile.is_open()) {
			string Line = "";
			while (getline(ClientsFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			ClientsFile.close();
		}
		return vClients;
	}
	static void _SaveClientsDataToFile(vector <clsBankClient> vClients) {
		fstream ClientsFile;
		ClientsFile.open(ClientsFileName, ios::out);  //overwite the file
		if (ClientsFile.is_open()) {
			string Line = "";
			for (clsBankClient& Client : vClients)
				if (!Client._MarkedForDelete) {
					Line = _ConvertClientObjectToLine(Client);
					ClientsFile << Line << endl;
				}
			ClientsFile.close();
		}
	}
	void _Update() {
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();
		for (clsBankClient& Client : vClients)
			if (Client.AccountNumber() == _AccountNumber) {
				Client = *this;
				break;
			}
		_SaveClientsDataToFile(vClients);
	}
	static void _AddDataLineToFile(string FileName, string DataLine) {
		fstream MyFile;
		MyFile.open(FileName, ios::in | ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}
	void _AddNew() {
		_AddDataLineToFile(ClientsFileName, _ConvertClientObjectToLine(*this));
	}

	static string _PrepareTransferLog(double Amount, clsBankClient SourceClient, 
				clsBankClient DestinationClient, string CurrentUser_UserName, string Separator = "#//#")
	{
		string TransferLogLine = "";

		TransferLogLine += clsDate::GetSystemDateTimeString() + Separator;
		TransferLogLine += SourceClient.AccountNumber() + Separator;
		TransferLogLine += DestinationClient.AccountNumber() + Separator;
		TransferLogLine += to_string(Amount) + Separator;
		TransferLogLine += to_string(SourceClient.getAccountBalance()) + Separator;
		TransferLogLine += to_string(DestinationClient.getAccountBalance()) + Separator;
		TransferLogLine += CurrentUser_UserName;

		return TransferLogLine;
	}

	static void _RegisterTransferLog(double Amount,clsBankClient SourceClient, 
								clsBankClient DestinationClient, string CurrentUser_UserName, string Separator = "#//#")
	{
		string TransferLogLine = _PrepareTransferLog(Amount, SourceClient, DestinationClient,
													CurrentUser_UserName, Separator);
		_AddDataLineToFile(TransferLogFileName, TransferLogLine);
	
	}
	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string TransferLogLine, string Separator = "#//#") {
		vector <string> vTransferLogRecordData = clsString::Split(TransferLogLine, Separator);
		stTransferLogRecord TransferLogRecord;

		TransferLogRecord.SystemDateTime = vTransferLogRecordData.at(0);
		TransferLogRecord.SourceClientAccountNumber = vTransferLogRecordData.at(1);
		TransferLogRecord.DestinationClientAccountNumber = vTransferLogRecordData.at(2);
		TransferLogRecord.Amount = stod(vTransferLogRecordData.at(3));
		TransferLogRecord.SourceClientAccountBalance = stod(vTransferLogRecordData.at(4));
		TransferLogRecord.DestinationClientAccountBalance = stod(vTransferLogRecordData.at(5));
		TransferLogRecord.UserName = vTransferLogRecordData.at(6);

		return TransferLogRecord;


	}
	static vector <stTransferLogRecord> _LoadTransferLogFromFile() {
		fstream TransferLogFile;
		vector <stTransferLogRecord> vTransferLog;
		TransferLogFile.open(TransferLogFileName, ios::in);
		if (TransferLogFile.is_open()) {
			string Line = "";
			while (getline(TransferLogFile, Line)) {
				stTransferLogRecord Record = _ConvertTransferLogLineToRecord(Line);
				vTransferLog.push_back(Record);
			}
			TransferLogFile.close();
		}
		return vTransferLog;
	}



public:
	struct stTransferLogRecord 
	{
		string SystemDateTime = "";
		double Amount = 0;
		string SourceClientAccountNumber = "";
		string DestinationClientAccountNumber = "";
		double SourceClientAccountBalance = 0;
		double DestinationClientAccountBalance = 0;
		string UserName = "";
	};
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}
	

	bool isEmpty() {
		return _Mode == enMode::EmptyMode;
	}

	//only (read) get property
	string AccountNumber() {
		return _AccountNumber;
	}
	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	string getPinCode() {
		return _PinCode;
	}
	void setPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	float getAccountBalance() {
		return _AccountBalance;
	}
	void setAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber) {
		fstream ClientsFile;
		ClientsFile.open(ClientsFileName, ios::in);
		if (ClientsFile.is_open()) {
			vector <clsBankClient> vClients = _LoadClientsDataFromFile();
			for (clsBankClient &Client : vClients)
				if (Client.AccountNumber() == AccountNumber) {
					ClientsFile.close();
					return Client;
				}
			ClientsFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode) {
		fstream ClientsFile;
		ClientsFile.open(ClientsFileName, ios::in);
		if (ClientsFile.is_open()) {
			vector <clsBankClient> vClients = _LoadClientsDataFromFile();
			for (clsBankClient& Client : vClients)
				if (Client._AccountNumber == AccountNumber && Client._PinCode == PinCode)
				{
					ClientsFile.close();
					return Client;
				}
			ClientsFile.close();
		}
		return _GetEmptyClientObject();
	}

	bool Delete() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& Client : vClients)
			if (Client.AccountNumber() == _AccountNumber) {
				Client._MarkedForDelete = true;
				break;
			}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static bool isClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return !Client.isEmpty();
	}
	void Print()
	{
		cout << "\nPerson Info:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << getFirstName();
		cout << "\nLastName    : " << getLastName();
		cout << "\nFullName    : " << FullName();
		cout << "\nEmail       : " << getEmail();
		cout << "\nPhone       : " << getPhone();
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPinCode     : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________" << endl;
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };
	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (isEmpty())
				return enSaveResults::svFailedEmptyObject;
			break;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			if (clsBankClient::isClientExist(_AccountNumber))
				return enSaveResults::svFailedAccountNumberExists;
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static void ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

	static void PrintClientRecordLine(clsBankClient Client)
	{
		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBlances = 0;
		for (clsBankClient& Client : vClients) 
			TotalBlances += Client._AccountBalance;
		return TotalBlances;
	}
	static bool Transfer(clsBankClient &ClientFrom, clsBankClient &ClientTo, double Amount, string UserName) {
		if (ClientFrom._AccountBalance < Amount)
			return false;
		ClientFrom.Withdraw(Amount);
		ClientTo.Deposit(Amount);
		_RegisterTransferLog(Amount, ClientFrom, ClientTo, UserName);
		return true;
		//saving in file is done in Withdraw() and Deposit()
	}
	static vector <stTransferLogRecord> GetTransferLogList() {
		return _LoadTransferLogFromFile();
	}


};