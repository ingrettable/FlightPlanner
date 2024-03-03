#pragma once

#include <sstream>
#include <string>
#include <cppTPS_Transaction.h>
#include "Num.h"

/**
 * AddToNum_Transaction.java
 *
 * This class is a transaction that can be executed and undone. It
 * can be stored in the jTPS transaction stack and must be constructed
 * with all the data necessary to perform both do and undo.
 *
 * @author THE McKilla Gorilla (accept no imposters)
 * @version 2.0
 */
class AddToNum_Transaction : public cppTPS_Transaction {
private:
    // THIS IS THE OBJECT IT WILL MANIPULATE
    Num* num;

    // AMOUNT TO ADD/REMOVE FOR NUM
    int amountToAdd;

public:
    /**
     * Constructor for this transaction, it initializes this
     * object with all the data needed to both do and undo
     * the transaction.
     *
     * @param initNum
     * @param initAmountToAdd
     */
    AddToNum_Transaction(Num* initNum, int initAmountToAdd) {
        // KEEP THESE FOR LATER
        num = initNum;
        amountToAdd = initAmountToAdd;
    }

    /**
     * This transaction simply adds the value to the num.
     */
    void doTransaction() {
        int oldNum = num->getNum();
        int newNum = oldNum + amountToAdd;
        num->setNum(newNum);
    }

    /**
     * As the reverse of do, this method substracts from num.
     */
    void undoTransaction() {
        int oldNum = num->getNum();
        int newNum = oldNum - amountToAdd;
        num->setNum(newNum);
    }

    /**
     * Provides a textual summary of this transaction.
     *
     * @return A string storing a textual summary of this object.
     */
    wstring toString() {
        wstringstream wss;
        wss << L"Add " << this->amountToAdd;
        return wss.str();
    }
};