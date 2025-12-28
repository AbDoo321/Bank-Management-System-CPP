#pragma once
#include <iostream>
#include <vector>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : clsScreen
{

private:

    static void _PrintUser(clsUser& User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.getFirstName();
        cout << "\nLastName    : " << User.getLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.getEmail();
        cout << "\nPhone       : " << User.getPhone();
        cout << "\nUser Name   : " << User.getUserName();
        cout << "\nPassword    : " << User.getPassword();
        cout << "\nPermissions : " << User.getPermissions();
        cout << "\n___________________\n";
    }


public:

	static void ShowFindUserScreen() {

        _PrintScreenHeader("Find User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::isUserExist(UserName))
        {
            cout << "\nUser is NOT Found, Enter another UserName: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        if (User.isEmpty()) {
            cout << "User was NOT found!" << endl;
        }
        else {
            cout << "User Found : " << endl;
        }
        _PrintUser(User);

	}
};

