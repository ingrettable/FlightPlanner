// cppTPSTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include "Num.h"
#include "AddToNum_Transaction.h"
#include <cppTPS.h>

// GLOBAL VARIABLES

// HERE'S OUR TRANSACTION PROCESSING SYSTEM
cppTPS tps;

// HERE'S THE DATA WE'RE MANIPULATING IN THIS DEMO
Num num;

int main()
{
    // LOOP FLAG VARIABLE
    bool keepGoing = true;
    while (keepGoing) {
        // DISPLAY THE CURRENT TPS
        wcout << "\n\nCURRENT cppTPS:" << endl;
        wcout << tps.toString();

        // DISPLAY NUM
        wcout << "num is " << num.getNum() << endl;

        // DISPLAY THE MENU
        wcout << "ENTER A SELECTION" << endl;
        wcout << "1) Add a Transaction" << endl;
        wcout << "2) Undo a Transaction" << endl;
        wcout << "3) Redo a Transaction" << endl;
        wcout << "4) Clear All Transactions" << endl;
        wcout << "5) Reset Num and Transactions" << endl;
        wcout << "Q) Quit" << endl;
        wcout << "-";

        // GET THE USER SELECTION
        wstring entry;
        wcin >> entry;

        // ADD AND EXECUTE A TRANSACTION
        if (entry.compare(L"1") == 0) {
            cout << "\nEnter an amount to add: ";
            wcin >> entry;
            int amountToAdd = stoi(entry);
            AddToNum_Transaction *transaction = new AddToNum_Transaction(&num, amountToAdd);
            tps.addTransaction(transaction);
        }
        // UNDO A TRANSACTION
        else if (entry.compare(L"2") == 0) {
            tps.undoTransaction();
        }
        // REDO A TRANSACTION
        else if (entry.compare(L"3") == 0) {
            tps.doTransaction();
        }
        // CLEAR ALL TRANSACTIONS
        else if (entry.compare(L"4") == 0) {
            tps.clearAllTransactions();
        }
        // CLEAR ALL TRANSACTIONS AND RESET NUM TO 0
        else if (entry.compare(L"5") == 0) {
            tps.clearAllTransactions();
            num.setNum(0);
        }
        // QUIT
        else if (entry.compare(L"Q") == 0) {
            keepGoing = false;
        }
    }
    wcout << L"GOODBYE";
}