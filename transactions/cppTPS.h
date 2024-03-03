#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "cppTPS_Transaction.h"

class cppTPS {
private:
    bool add;
    bool performingDo;
    bool performingUndo;
    int mostRecentTransaction = -1;
    std::vector<cppTPS_Transaction*> transactions;
    // Vector of pointers

public:
    // INLINED FUNCTIONS

    bool isPerformingDo() {
        return this->performingDo;
    }

    bool isPerformingUndo() {
        return this->performingUndo;
    }

    bool hasTransactionToRedo() {
        return mostRecentTransaction < (transactions.size() - 1);
    }

    bool hasTransactionToUndo() {
        return mostRecentTransaction >= 0;
    }

    size_t getSize() {
        return transactions.size();
    }

    size_t getRedoSize() {
        return getSize() - mostRecentTransaction - 1;
    }

    int getUndoSize() {
        return mostRecentTransaction + 1;
    }

    // THE REMAINING FUNCTIONS ARE DEFINED INSIDE cppTPS.cpp

    cppTPS(); // Default constructor

    void addTransaction(cppTPS_Transaction* transaction);

    void doTransaction();

    void undoTransaction();

    void clearAllTransactions();

    std::wstring toString();
};