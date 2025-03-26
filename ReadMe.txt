Budget Tracker

## Overview

The program consists 2 libaryes:
- lib.h
	-1. `Date`: Represents a date with day, month, and year attributes.
	-2. `Target`: Represents a savings target with attributes such as name, limit, amount, and target date.
	-3. `Payment`: Represents a payment with attributes including name, amount, type (income or expense), and date.
	-4. `Owner`: Represents the owner of the account with attributes like name, address, and phone number.
	-5. `Account`: Represents the main account with attributes including account number, owner, balance, and various vectors to store targets, payments, incomes, etc.

- huff.h
	-1. `Huffman` : Represents a compres and decompres utility and im using it for encrypt and decrypt

The use of this libaryes:
- Users can add Acount
- Users can add part owners to the account.
- Users can add targets for savings to the account
- Users can add payments (expenses) and monthly payments to the account
- Users can add incomes to the account.
- Users can save informations in files and this files are encrypted
- Users can generate reports on the whole account or on individual Targets
- Users can remove targets.
- Users can calculate the months remaining to reach a specific savings target based on monthly contributions.

The mains files:
- Main.cpp - its implementation of RestApi with a Crow framework
- Main2.cpp - its implementation of simple console aplication
- Main3.cpp - its implementation of simple use in main funkcion

Documentation is in folder name Document both HTML and latex.

For compilation u need Cmake, in main folder is CMakeFile.txt
with this file u can compile a whole project.

If u want to use the RestApi I build, u will need a vcpkg (https://vcpkg.io/en/)
after u install this program u will need thru that program install a Crow Framework (https://crowcpp.org/master/)
and then u need add a path in CMakeFile 

in some ways its very scav.

HAVE FUN 
