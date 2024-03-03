#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cppTPS_Transaction {

public:
    /**
     * This method is called by jTPS when a transaction is executed.
     */
    virtual void doTransaction() = 0;

    /**
     * This method is called by jTPS when a transaction is undone.
     */
    virtual void undoTransaction() = 0;

    virtual wstring toString() = 0;
};