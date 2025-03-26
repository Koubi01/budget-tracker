/**
 * @file lib.h
 * @brief Contains the implementation of a financial management system.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <variant>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include "Huff.h"

/**
 * @class Target
 * @brief Represents a financial target with a name, limit, target date, and amount.
 */
class Target;

/**
 * @class Payment
 * @brief Represents a financial payment with a name, amount, type, and date.
 */
class Payment;

/**
 * @class Owner
 * @brief Represents an account owner with a name, address, and phone number.
 */
class Owner;

/**
 * @class Date
 * @brief Represents a date with day, month, and year components.
 */
class Date;

/**
 * @class Account
 * @brief Represents a financial account with various properties and functionalities.
 */
class Account;

/**
 * @brief Loads account data from a file.
 * @param filename The name of the file to load data from.
 * @param accounts Reference to the vector to store loaded account data.
 */
void loadFromFile(const std::string& filename, std::vector<Account>& accounts);

/**
 * @brief Writes account data to a file.
 * @param fileName The name of the file to write data to.
 * @param accounts Reference to the vector containing account data to write.
 */
void writeToTheFile(const std::string& fileName, std::vector<Account>& accounts);

/**
 * @brief Alias for a variant type that can hold Date, Target, Payment, Owner, or Account.
 */
using Value = std::variant<Date, Target, Payment, Owner, Account>;

/**
 * @brief Visitor for printing a Value to an output stream.
 */
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
std::ostream& operator<<(std::ostream& os, const Value& value);

/**
 * @brief Enum representing the type of payment.
 */
enum Payment_type{
    incomes, ///< Income payment type.
    expens   ///< Expense payment type.
};

/**
 * @class Date
 * @brief Represents a date with day, month, and year components.
 */
class Date{
    private:
    std::string day;   ///< Day component of the date.
    std::string month; ///< Month component of the date.
    std::string year;  ///< Year component of the date.
    public:
        Date():day(0),month(0),year(0){} ///< Default constructor.
        Date(std::string d, std::string m, std::string y) : day(d), month(m), year(y){} ///< Parameterized constructor.
        std::string getDay() const;    ///< Getter for the day component.
        std::string getMonth() const;  ///< Getter for the month component.
        std::string getYear() const;   ///< Getter for the year component.
        std::string getDate() const;   ///< Getter for the full date.
};

/**
 * @class Target
 * @brief Represents a financial target with a name, limit, target date, and amount.
 */
class Target{
    private:
        std::string name;      ///< Name of the target.
        double limit;          ///< Limit of the target.
        Date target_date;      ///< Target date.
        double amount;         ///< Amount associated with the target.
    public:
        /**
         * @brief Parameterized constructor.
         * @param name Name of the target.
         * @param lmt Limit of the target.
         * @param target_dat Target date.
         * @param Amnt Amount associated with the target.
         */
        Target(std::string name, double lmt, Date target_dat, double Amnt): name(name),limit(lmt), target_date(target_dat), amount(Amnt){}
        std::string getName() const;  ///< Getter for the target name.
        double getLimit() const;      ///< Getter for the target limit.
        Date getDate() const;         ///< Getter for the target date.
        void setTargetDate(Date NewDate);       ///< Setter for the target date.
        void setTagetLimit(double limit);       ///< Setter for the target limit.
        void setTargetName(std::string NewName); ///< Setter for the target name.
        void setTargetAmount(double n);          ///< Setter for the target amount.
        double getDifferences();                ///< Calculates the difference between limit and amount.
        double getAmount() const;                ///< Getter for the target amount.
        void addAmount (double value);          ///< Adds amount to the target.
        bool reached();                         ///< Checks if the target has been reached.
        std::string toString();                 ///< Converts target data to string format.
};

/**
 * @class Payment
 * @brief Represents a financial payment with a name, amount, type, and date.
 */
class Payment{
    private:
        std::string name;         ///< Name of the payment.
        double amount;            ///< Amount of the payment.
        Payment_type ptyp;        ///< Type of the payment.
        Date date;                ///< Date of the payment.
    public:
        /**
         * @brief Parameterized constructor.
         * @param name Name of the payment.
         * @param a Amount of the payment.
         * @param t Type of the payment.
         * @param dt Date of the payment.
         */
        Payment(std::string name, double a, Payment_type t, Date dt):name(name),amount(a),ptyp(t),date(dt){}
        std::string getName() const;        ///< Getter for the payment name.
        double getAmount() const;           ///< Getter for the payment amount.
        Payment_type getType() const;       ///< Getter for the payment type.
        Date getDate() const;               ///< Getter for the payment date.
        void setAmnt(double a);             ///< Setter for the payment amount.
        void setType(Payment_type t);       ///< Setter for the payment type.
        void setDate(Date d);               ///< Setter for the payment date.
        void setName(std::string n);        ///< Setter for the payment name.
        std::string toString();             ///< Converts payment data to string format.
};

/**
 * @class Owner
 * @brief Represents an account owner with a name, address, and phone number.
 */
class Owner{
    private:
        std::string name;            ///< Name of the owner.
        std::string address;         ///< Address of the owner.
        std::string phoneNumber;     ///< Phone number of the owner.
    public:
        /**
         * @brief Parameterized constructor.
         * @param n Name of the owner.
         * @param a Address of the owner.
         * @param pN Phone number of the owner.
         */
        Owner(std::string n, std::string a, std::string pN):name(n),address(a),phoneNumber(pN){}
        std::string getName() const;        ///< Getter for the owner name.
        std::string getAddress() const;     ///< Getter for the owner address.
        std::string getPhoneNumber() const; ///< Getter for the owner phone number.
        void setName(std::string n);        ///< Setter for the owner name.
        void setAddress(std::string a);     ///< Setter for the owner address.
        void setPhoneNumber(std::string pN);///< Setter for the owner phone number.
        std::string toString();             ///< Converts owner data to string format.
};

/**
 * @class Account
 * @brief Represents a financial account with various properties and functionalities.
 */
class Account{
    private:
        int accountNumber;                 ///< Account number.
        Owner owner;                       ///< Account owner.
        Date date_of_assembly;             ///< Date of account assembly.
        double balance;                    ///< Account balance.
        std::vector<Owner> part_owners;    ///< Additional owners of the account.
        std::vector<Target> targets;       ///< Financial targets associated with the account.
        std::vector<Payment> monthly_pays; ///< Monthly payments associated with the account.
        std::vector<Payment> payments;     ///< General payments associated with the account.
        std::vector<Payment> incomes;      ///< Incomes associated with the account.
    public:
        /**
         * @brief Parameterized constructor.
         * @param accNum Account number.
         * @param date Date of account assembly.
         * @param own Owner of the account.
         * @param bal Balance of the account.
         */
        Account(int accNum, Date date, Owner own, double bal) :
            accountNumber(accNum), owner(own), date_of_assembly(date), balance(bal) {};

        void setOwnerName(std::string newName); ///< Setter for the owner name.
        void setOwnerAdress(std::string newAdress); ///< Setter for the owner address.
        void setOwnerPhone(std::string newPhone);   ///< Setter for the owner phone number.
        int getAccountNumber() const;              ///< Getter for the account number.
        double getBalance() const;                  ///< Getter for the account balance.
        Date getDateOfAssebly() const;             ///< Getter for the date of account assembly.
        Owner getOwner() const;                     ///< Getter for the account owner.
        int numberOfPartOwners() const;             ///< Getter for the number of part owners.
        std::vector<Owner> getPartOwners() const;   ///< Getter for the part owners.
        int numberOfTargets();                      ///< Getter for the number of targets.
        std::vector<Target> getTargets() const;     ///< Getter for the targets.
        int numberOfMonthlyPayments() const;        ///< Getter for the number of monthly payments.
        std::vector<Payment> getMontlyPays() const; ///< Getter for the monthly payments.
        int numberOfPayments() const;               ///< Getter for the number of payments.
        std::vector<Payment> getPayments() const;   ///< Getter for the payments.
        int numberOfIncomes() const;                ///< Getter for the number of incomes.
        std::vector<Payment> getIncomes() const;    ///< Getter for the incomes.
        void addPartOwner(Owner part_owner);        ///< Adds a part owner to the account.
        void addTargets(Target target);             ///< Adds a target to the account.
        void addPayment(Payment pay);               ///< Adds a payment to the account.
        void addMonthlyPays(Payment monthly_payments); ///< Adds a monthly payment to the account.
        void addFunds(Payment fund);                ///< Adds funds to the account.
        void addTargetFund(std::string name, double Amount); ///< Adds funds to a target.
        void printMonthly();                         ///< Prints monthly payments.
        void printPayments();                        ///< Prints all payments.
        void printTargets();                         ///< Prints all targets.
        void printIncomes();                         ///< Prints all incomes.
        void printPartOwners();                      ///< Prints all part owners.
        void removeTarget(std::string name);         ///< Removes a target.
        void removePartOwner(std::string name);      ///< Removes a part owner.
        void printInformationAccount();              ///< Prints account information.
        void monthsToTarget(std::vector<std::pair<std::string, std::pair<int, bool>>>& monthsRemaining, const std::string& targetName); ///< Calculates months remaining to reach a target.
        void prettyPrintAccount();                   ///< Prints account details in a formatted manner.
        double calculateTotalExpenses();             ///< Calculates total expenses.
        double calculateTotalIncome();               ///< Calculates total income.
        void generateSpendingHabitsReport();         ///< Generates spending habits report.
        std::string generateSpendingHabitsReportJson(); ///< Generates spending habits report in JSON format.
};

