#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include "clsUtil.h"
#include "clsDate.h"
#include "Global.h"
using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string subTitle = "") {
		cout << "\t\t\t\t-----------------------------------------" << endl;
		cout << "\t\t\t\t\t\t" << Title << endl;
		if (subTitle != "")
			cout << "\t\t\t\t\t\t" << subTitle << endl;
		cout << "\t\t\t\t-----------------------------------------" << endl;
	}

    static void _PrintScreenHeader(const string& title, const string& subtitle = "", 
                           const short& outerIndent = 40, const string& symbol = "-") 
    {
        const short maxLength = max(title.length(), subtitle.length());
        const short shortIndent = round(sqrt(3 * maxLength));
        const short longIndent = shortIndent + abs(static_cast<short>(title.length() - subtitle.length())) / 2;

        cout << setw(outerIndent) << ""
            << clsUtil::getCharacterString(symbol, maxLength + shortIndent * 2)
            << "\n";

        cout << setw(outerIndent) << ""
            << clsUtil::getCharacterString(' ', title.length() > subtitle.length() ? shortIndent : longIndent)
            << title << "\n";

        if (subtitle != "") {
            cout << setw(outerIndent) << ""
                << clsUtil::getCharacterString(' ', subtitle.length() > title.length() ? shortIndent : longIndent)
                << subtitle << "\n";
        }

        cout << setw(outerIndent) << ""
             << clsUtil::getCharacterString(symbol, maxLength + shortIndent * 2)
             << "\n" << endl;

        cout << setw(outerIndent) << "" << "Date: ";
        clsDate::GetSystemDate().clsDate::Print();
        cout << setw(outerIndent) << "" << "User: " << CurrentUser.getUserName() 
             << endl << endl;
    }


    static bool _CheckAccessRights(clsUser::enPermissions Permission) {
        if (CurrentUser.CheckPermissions(Permission)) 
            return true;
        else 
        {
            system("cls");
            _PrintScreenHeader("Access Denied, Contact Your Admin!");
            return false;
        }
    }

};

