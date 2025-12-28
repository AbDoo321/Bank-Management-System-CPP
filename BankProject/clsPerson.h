#pragma once
#include <iostream>
#include <string>
using namespace std;


class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string FirstName, string LastName, string Email, string Phone) {
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}


	string getFirstName() {
		return _FirstName;
	}
	void setFirstName(string FirstName) {
		_FirstName = FirstName;
	}
	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	string getLastName() {
		return _LastName;
	}
	void setLastName(string LastName) {
		_LastName = LastName;
	}
	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	string FullName() {
		return _FirstName + " " + _LastName;
	}

	string getEmail() {
		return _Email;
	}
	void setEmail(string Email) {
		_Email = Email;
	}
	__declspec(property(get = getEmail, put = setEmail)) string Email;

	string getPhone() {
		return _Phone;
	}
	void setPhone(string Phone) {
		_Phone = Phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) string Phone;

	void Print()
	{
		cout << "\nPerson Info:";
		cout << "\n___________________";
		cout << "\nFirstName: " << _FirstName;
		cout << "\nLastName : " << _LastName;
		cout << "\nFullName : " << FullName();
		cout << "\nEmail    : " << _Email;
		cout << "\nPhone    : " << _Phone;
		cout << "\n___________________" << endl;
	}



};

