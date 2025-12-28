#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{ 
private:
	static bool _Login() 
	{
		bool LoginFailed = false;
		short FailedLoginCounter = 0;
		string UserName = "", Password = "";
		do
		{
			if (LoginFailed) 
			{
				FailedLoginCounter++;
				cout << "\nInvalid UserName/Password!\n" << endl;
				cout << "You still Have " << 3 - FailedLoginCounter 
					 << " trial(s) to Login." << endl;
			}
			if (FailedLoginCounter == 3) {
				cout << "You are Locked after 3 Failed trials." << endl;
				return false;
			}

			cout << "Enter the UserName : ";
			UserName = clsInputValidate::ReadString();

			cout << "Enter the Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.isEmpty();


		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		_PrintScreenHeader("Login Screen");

		return _Login();
	}

};

