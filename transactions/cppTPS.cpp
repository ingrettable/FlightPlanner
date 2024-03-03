// cppTPS.cpp : Defines the functions for the static library.

// C++ LIBRARIES FOR I/O AND TEXT
#include <sstream>
#include <string>
#include "cppTPS.h"

cppTPS::cppTPS() {
    add = false;
    performingDo = false;
    performingUndo = false;
    mostRecentTransaction = -1;
    transactions = std::vector<cppTPS_Transaction*>();
    //add
}


void cppTPS::addTransaction(cppTPS_Transaction* transaction) {
    if (mostRecentTransaction < 0 || mostRecentTransaction < (transactions.size() - 1)) {
        for (size_t i = transactions.size() - 1; i > mostRecentTransaction; i--) {
            transactions.erase(transactions.begin() + i);
        }
    }
    transactions.push_back(transaction);
    //mostRecentTransaction++;
    add = true;
    doTransaction();
    // add
}

void cppTPS::doTransaction() {
    if (hasTransactionToRedo() || mostRecentTransaction < 0) {
        performingDo = true;
        cppTPS_Transaction* transaction = transactions[mostRecentTransaction+1];
        transaction->doTransaction();
        mostRecentTransaction++;
        add = false;
        performingDo = false;
    }
    // ADD CODE HERE
}


void cppTPS::undoTransaction() {
    if (hasTransactionToUndo()) {
        performingUndo = true;
        cppTPS_Transaction* transaction = transactions[mostRecentTransaction];
        transaction->undoTransaction();
        mostRecentTransaction--;
        performingUndo = false;
    }
    // ADD CODE HERE
}


void cppTPS::clearAllTransactions() {
    transactions.clear();
    mostRecentTransaction = -1;
    // ADD CODE HERE
}

wstring cppTPS::toString() {
    // ADD CODE HERE
    wstring text = L"--Number of Transactions: " + to_wstring(transactions.size()) + L"\n";
    text += L"--Current Index on Stack: " + to_wstring(mostRecentTransaction) + L"\n";
    text += L"--Current Transaction Stack:\n";
    for (int i = 0; i <= mostRecentTransaction; i++) {
        cppTPS_Transaction* jT = transactions[i];
        text += L"----" + jT->toString() + L"\n";
    }
    return text;
}