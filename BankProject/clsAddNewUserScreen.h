#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen: protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User) {
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

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            return -1;

        cout << "\nDo you want to give access to : \n ";

        cout << "Show Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pClientsList;


        cout << "Add New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pAddNewClient;

        cout << "Delete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pDeleteClient;

        cout << "Update Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pUpdateClient;

        cout << "Find Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pFindClient;

        cout << "Transactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pTransactions;

        cout << "Manage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pManageUsers;

        cout << "Login Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pLoginRegisterList;

        cout << "Currency Exchange? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pCurrencyExchange;

        return Permissions;
    }

public:
    static void ShowAddNewUserScreen() {

        _PrintScreenHeader("Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::isUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
            cout << "\nUser Added Successfully :-)\n";
            _PrintUser(NewUser);
            break;

        case clsUser::enSaveResults::svFailedEmptyObject:
            cout << "\nError User was not saved because it's Empty";
            break;

        case clsUser::enSaveResults::svFailedUserExists:
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
    }

};

