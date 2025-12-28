#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;
//const string UsersFileName = "C:\\Users\\PC\\Desktop\\Programming Advices courses\\course11\\BankProject\\UsersFile.txt";
const string UsersFileName = "UsersFile.txt";
const string LoginRegisterFileName = "LoginRegister.txt";


class clsUser : public clsPerson
{
private:
	static const short EncryptionKey = 3;

	enum enMode { EmptyMode = 0, UpdateMode, AddNewMode };
	enMode _Mode;
	string _UserName ;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	static clsUser _GetEmptyUserObject() {
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserObjectToLine(clsUser& User, string Separator = "#//#") {
		string UserRecord = "";

		UserRecord += User.getFirstName() + Separator;
		UserRecord += User.getLastName() + Separator;
		UserRecord += User.getEmail() + Separator;
		UserRecord += User.getPhone() + Separator;
		UserRecord += User.getUserName() + Separator;
		UserRecord += clsUtil::Encrypt(User._Password, EncryptionKey) + Separator;
		UserRecord += to_string(User.getPermissions());

		return UserRecord;
	}
	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#") {
		vector <string> vUserData = clsString::Split(Line, Separator);

		return clsUser(enMode::UpdateMode, vUserData.at(0), vUserData.at(1), vUserData.at(2),
			vUserData.at(3), vUserData.at(4), clsUtil::Decrypt(vUserData.at(5), EncryptionKey), stoi(vUserData.at(6)));
	}

	static vector <clsUser> _LoadUsersDataFromFile() {
		fstream UsersFile;
		vector <clsUser> vUsers;

		UsersFile.open(UsersFileName, ios::in); //Read Mode
		if (UsersFile.is_open()) 
		{
			string Line = "";
			while (getline(UsersFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			UsersFile.close();
		}
		return vUsers;
	}
	static void _SaveUsersDataToFile(vector <clsUser> vUsers) {
		fstream UsersFile;
		UsersFile.open(UsersFileName, ios::out); //overwrite the file

		if (UsersFile.is_open()) 
		{
			string Line = "";
			for (clsUser& User : vUsers) 
				if (!User.MarkedForDelete()) 
				{
					Line = _ConvertUserObjectToLine(User);
					UsersFile << Line << endl;
				}
			UsersFile.close();
		}
	}
	static void _AddDataLineToFile(string FileName, string Line) {
		fstream File;
		File.open(FileName, ios::out | ios::app);
		if (File.is_open()) 
		{
			File << Line << endl;
			File.close();
		}
	}

	void _Update() {
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
			if (User.getUserName() == _UserName) { //this->_UserName
				User = *this;
				break;
			}
		_SaveUsersDataToFile(vUsers);
	}
	void _AddNew() {
		_AddDataLineToFile(UsersFileName, _ConvertUserObjectToLine(*this));
	}

	string _PrepareLogInRecord(string Separator = "#//#") {
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += _UserName + Separator;
		LoginRecord += clsUtil::Encrypt(_Password, EncryptionKey) + Separator;
		LoginRecord += to_string(_Permissions);

		return LoginRecord;
	}
	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#") {

		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> vLoginRegisterDataLine = clsString::Split(Line, Separator);
		LoginRegisterRecord.DateTime = vLoginRegisterDataLine.at(0);
		LoginRegisterRecord.UserName = vLoginRegisterDataLine.at(1);
		LoginRegisterRecord.Password = clsUtil::Decrypt(vLoginRegisterDataLine.at(2), EncryptionKey);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterDataLine.at(3));

		return LoginRegisterRecord;
	}
		
public:
	enum enPermissions {
		pAll = -1, pClientsList = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
		pLoginRegisterList = 128, pCurrencyExchange = 256
	};
	struct stLoginRegisterRecord {

		string DateTime = "";
		string UserName = "";
		string Password = "";
		int Permissions = 0;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}


	string getUserName() {
		return _UserName;
	}
	void setUserName(string UserName) {
		_UserName = UserName;
	}
	__declspec(property(get = getUserName, put = setUserName)) string UserName;

	string getPassword() {
		return _Password;
	}
	void setPassword(string Password) {
		_Password = Password;
	}
	__declspec(property(get = getPassword, put = setPassword)) string Password;

	int getPermissions() {
		return _Permissions;
	}
	void setPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}


	bool isEmpty() {
		return _Mode == enMode::EmptyMode;
	}
	static clsUser Find(string UserName) {
		fstream UsersFile;
		UsersFile.open(UsersFileName, ios::in);

		if (UsersFile.is_open()) 
		{
			string Line = "";
			while (getline(UsersFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.getUserName() == UserName) 
				{
					UsersFile.close();
					return User;
				}
			}
			UsersFile.close();
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password) {
		fstream UsersFile;
		UsersFile.open(UsersFileName, ios::in);

		if (UsersFile.is_open())
		{
			string Line = "";
			while (getline(UsersFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.getUserName() == UserName && User.getPassword() == Password)
				{
					UsersFile.close();
					return User;
				}
			}
			UsersFile.close();
		}
		return _GetEmptyUserObject();
	}
	static bool isUserExist(string UserName) {
		clsUser User = clsUser::Find(UserName);
		return !User.isEmpty();
	}

	enum enSaveResults{ svFailedEmptyObject = 0, svSucceeded, svFailedUserExists };
	enSaveResults Save() {
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			if (isEmpty())
				return enSaveResults::svFailedEmptyObject;
			break;
		case clsUser::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case clsUser::AddNewMode:
			if (clsUser::isUserExist(_UserName))
				return enSaveResults::svFailedUserExists;
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
	}

	bool Delete() {
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
			if (User.getUserName() == _UserName) {
				User._MarkedForDelete = true;
				break;
			}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}
	static vector <clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool CheckPermissions(enPermissions Permission) {
		if (this->_Permissions == enPermissions::pAll)
			return true;
		if (Permission == (this->_Permissions & Permission))
			return true;
		else
			return false;
	}

	void RegisterLogIn() {
		string DataLine = _PrepareLogInRecord();
		_AddDataLineToFile(LoginRegisterFileName, DataLine);
	}
	static vector <stLoginRegisterRecord> GetLoginRegisterList () {
		vector <stLoginRegisterRecord> vLoginRecords;
		fstream LoginRegisterFile;
		LoginRegisterFile.open(LoginRegisterFileName, ios::in);
		if (LoginRegisterFile.is_open()) 
		{
			string Line = "";
			stLoginRegisterRecord LoginRecord;
			while ( getline(LoginRegisterFile, Line) ) 
			{
				LoginRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRecords.push_back(LoginRecord);
			}
			LoginRegisterFile.close();
		}
		return vLoginRecords;

	}



};

