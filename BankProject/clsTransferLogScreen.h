#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsTransferScreen.h"

using namespace std;
class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord TransferLogRecord) 
	{
		cout << setw(8) << left << "" << "| " << setw(20) << left << TransferLogRecord.SystemDateTime;
		cout << "| " << setw(8) << left << TransferLogRecord.SourceClientAccountNumber;
		cout << "| " << setw(8) << left << TransferLogRecord.DestinationClientAccountNumber;
		cout << "| " << setw(15) << left << TransferLogRecord.Amount;
		cout << "| " << setw(20) << left << TransferLogRecord.SourceClientAccountBalance;
		cout << "| " << setw(20) << left << TransferLogRecord.DestinationClientAccountBalance;
	}


public:
	static void ShowTransferLogScreen() {

		vector <clsBankClient::stTransferLogRecord> vTransferLog = clsBankClient::GetTransferLogList();

		string Title = "Transfer Log Screen";
		string subTitle = to_string(vTransferLog.size()) + " Log(s) Registered.";
		_PrintScreenHeader(Title, subTitle);


		cout << left << setw(8) << "" 
			<< "==============================================================================================================\n";

		cout << setw(8) << left << "" << "| " << setw(20) << left << "SystemDateTime";
		cout << "| " << setw(8) << left << "S.Acc";
		cout << "| " << setw(8) << left << "D.Acc";
		cout << "| " << setw(15) << left << "Amount";
		cout << "| " << setw(20) << left << "S.AccountBalance";
		cout << "| " << setw(20) << left << "D.AccountBalance";
		cout << endl << setw(8) << left << ""
			<< "==============================================================================================================\n";
		if (vTransferLog.empty())
			cout << "\t\t\tNo Transfer Logs Available in the System !" << endl;
		else
			for (clsBankClient::stTransferLogRecord& TransferLogRecord : vTransferLog) 
			{
				_PrintTransferLogRecord(TransferLogRecord);
				cout << endl;
			}
		cout << setw(8) << ""
			<< "==============================================================================================================\n";
	}
};

