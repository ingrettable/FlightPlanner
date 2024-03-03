# cppTPSTester ReadMe

## Overview

The `cppTPSTester` program is a C++ application designed to demonstrate the functionality of a Transaction Processing System (TPS) implemented using the C++TPS library. This program allows users to manipulate a `Num` object using various transactions, such as adding to the number, undoing transactions, redoing transactions, clearing all transactions, and resetting the number and transactions.

## Dependencies

The program depends on the following components:

- **C++ Standard Library:** The program uses functionalities provided by the C++ Standard Library for input/output operations, string handling, and general program execution.
- **cppTPS Library:** The cppTPS library provides the core functionality for implementing transaction processing systems in C++.

## Files

- **cppTPSTester.cpp:** Contains the main function where program execution begins and ends. This file interacts with the user and demonstrates the functionality of the TPS.
- **Num.h:** Header file defining the Num class, which represents the data manipulated by transactions.
- **AddToNum_Transaction.h:** Header file defining the AddToNum_Transaction class, which represents a transaction that adds a specified amount to the Num object.
- **cppTPS.h:** Header file defining the cppTPS class, which implements the Transaction Processing System.

## Functionality

The program provides the following functionality:

1. **Add a Transaction:** Allows users to add a transaction that adds a specified amount to the Num object.
2. **Undo a Transaction:** Enables users to undo the last transaction performed.
3. **Redo a Transaction:** Allows users to redo the last undone transaction.
4. **Clear All Transactions:** Clears all transactions from the transaction history.
5. **Reset Num and Transactions:** Resets the Num object to 0 and clears all transactions.
6. **Quit:** Exits the program.

## Usage

1. Compile the program using a C++ compiler compatible with C++11 or later standards.
2. Execute the compiled binary.
3. Follow the on-screen prompts to interact with the program:
   - Enter the selection number corresponding to the desired operation.
   - Follow additional prompts to provide input, such as the amount to add to the Num object.
4. To quit the program, enter 'Q' at the menu prompt.
