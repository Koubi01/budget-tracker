#include "lib.h"

/**
 * @brief Overloaded stream insertion operator to output a Value object to an output stream.
 * 
 * This operator allows printing a Value object to an output stream.
 * 
 * @param os The output stream to which the Value object will be printed.
 * @param vall The Value object to be printed.
 * @return std::ostream& The reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Value& vall) {
    std::visit(overloaded{        
        /**
         * @brief Lambda function to output an Account object.
         * 
         * This lambda function outputs the details of an Account object to the provided output stream.
         * 
         * @param acc The Account object to be printed.
         */
        [&os](const Account& acc) { 
            os << "{";
            os << "Account number: " << acc.getAccountNumber()<< ",";
            os << "Owner: " << "{" << acc.getOwner() << "}" << ",";
            os << "Date of Assembly: " << acc.getDateOfAssebly()<< ",";
            os << "Account balance: " << acc.getBalance()<< ",";
            os << "Part owners: ";
            os << "[";
            for(auto n :  acc.getPartOwners()){
                os << "{";
                os << n;
                os << "}";
                os << ",";
            }
            os << "]"<< ",";
            os << "Targets: ";
            os << "[";
            for(auto n :  acc.getTargets()){
                os << "{";
                os << n;
                os << "}";
                os << ",";
            }                               
            os << "]"<< ",";
            os << "Incomes: ";
            os << "[";
            for(auto n :  acc.getIncomes()){
                os << "{";
                os << n;
                os << "}";
                os << ",";
            }
            os << "]"<< ",";
            os << "Monthly Contribution: ";
            os << "[";
            for(auto n :  acc.getMontlyPays()){
                os << "{";
                os << n;
                os << "}";
                os << ",";
            }                         
            os << "]"<< ",";
            os << "Payments: ";
            os << "[";
            for(auto n :  acc.getPayments()){
                os << "{";
                os << n;
                os << "}";
                os << ",";
            }
            os << "]";
            os << "}" << std::endl;
        },
        /**
         * @brief Lambda function to output a Date object.
         * 
         * This lambda function outputs the date details to the provided output stream.
         * 
         * @param date The Date object to be printed.
         */
        [&os](const Date& date){os << date.getDay() + "/" + date.getMonth() + "/" + date.getYear();},
        /**
         * @brief Lambda function to output a Target object.
         * 
         * This lambda function outputs the details of a Target object to the provided output stream.
         * 
         * @param target The Target object to be printed.
         */
        [&os](const Target& target) {
            os << "Name: " << target.getName() << ",";
            os << "Amount: " << target.getAmount() << ",";
            os << "Limit: " << target.getLimit() <<" $"<< ",";
            os << "Target Date: " << target.getDate(); 
        },
        /**
         * @brief Lambda function to output an Owner object.
         * 
         * This lambda function outputs the details of an Owner object to the provided output stream.
         * 
         * @param owner The Owner object to be printed.
         */
        [&os](const Owner& owner) { 
            os << "Name: " << owner.getName()<< ",";
            os << "Address: "<< owner.getAddress()<< ",";
            os << "Phone Number: " << owner.getPhoneNumber(); 
        },
        /**
         * @brief Lambda function to output a Payment object.
         * 
         * This lambda function outputs the details of a Payment object to the provided output stream.
         * 
         * @param payment The Payment object to be printed.
         */
        [&os](const Payment& payment) {
            os << "Name: " << payment.getName()<< ",";
            os << "Amount: "<< payment.getAmount()<< ",";
            os << "Type: " << (payment.getType() ? "expens" : "incomes" )<< ",";
            os << "Date: " << payment.getDate();                                    
        }
         }, vall);
    return os;
}


/**
 * @brief Writes account information to a file, compresses it using Huffman coding, and deletes the temporary file.
 *
 * This function writes account information to a file specified by fileName, then compresses the file using Huffman coding 
 * and deletes the temporary file after compression.
 *
 * @param fileName The name of the file to write the account information to.
 * @param accounts A vector of Account objects containing the account information to be written to the file.
 */
void writeToTheFile(const std::string& fileName, std::vector<Account>& accounts) {
    // Create a temporary file name for compression
    std::string temporaryFileName = "Boo.txt";
    
    // Open the file for writing
    std::ofstream file(temporaryFileName);
    
    // Check if the file is successfully opened
    if (file.is_open()) {
        // Write account information to the file
        for(auto& account : accounts){
            file << account;
        }
        
        // Close the file
        file.close();
        
        // Compress the file using Huffman coding
        Huffman huffman;
        huffman.Compres(temporaryFileName, fileName);
        
        // Inform the user about successful file creation
        std::cout << "Soubor byl vytvořen.\n";
    } else {
        // Inform the user if file creation fails
        std::cout << "Nelze vytvořit soubor.\n";
    }

    // Delete the temporary file
    if (std::remove(temporaryFileName.c_str()) != 0) {
        // Inform the user if file deletion fails
        std::cout << "Nepodařilo se smazat soubor.\n";
    } else {
        // Inform the user about successful file deletion
        std::cout << "Soubor byl smazán.\n";
    }
}


/**
 * @brief Loads account data from a file and populates a vector of Account objects.
 * 
 * This function reads data from a file containing account information in a specific format.
 * It parses the data and creates Account objects, populating them with the parsed information,
 * and then adds these Account objects to the provided vector.
 * It decompresses the file by using Huffman coding and deletes the temporary file after decompression.
 *  
 * @param filename The name of the file from which to load account data.
 * @param accounts A vector of Account objects where the loaded data will be stored.
 */
void loadFromFile(const std::string& filename, std::vector<Account>& acounts) {

    Huffman huffman;
    std::string ScaryFileName = "Boo.txt";
    huffman.Decompres(filename, ScaryFileName);

    int count = 0;
    std::ifstream file(ScaryFileName);
    if (!file.is_open()) {
        std::cerr << "Nelze otevřít soubor " << filename << std::endl;
    }
    else{
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if(iss.peek() != EOF){
                iss.ignore(17);
                int num = 0;
                char c = iss.peek();
                do {
                    num *= 10;
                    num += c - '0';
                    iss.get();
                    c = iss.peek();
                } while (std::isdigit(c));
                iss.ignore(15);
                std::string name;
                std::string adress;
                std::string phoneNumber;
                c = iss.peek();
                do {
                    name.push_back(c);
                    iss.get();
                    c = iss.peek();
                } while (c != ',');
                iss.ignore(10);
                c = iss.peek();
                do {
                    adress.push_back(c);
                    iss.get();
                    c = iss.peek();
                } while (c != ',');
                iss.ignore(15);
                if((c = iss.peek()) == '+')
                {
                    iss.get();
                    c = iss.peek();
                }            
                do {
                    phoneNumber.push_back(c);
                    iss.get();
                    c = iss.peek();
                } while (c != '}');
                iss.ignore(20);
                std::string day;
                std::string month;
                std::string year;
                c = iss.peek();
                do {
                    day.push_back(c);
                    iss.get();
                    c = iss.peek();
                } while (c != '/');
                iss.get();
                c = iss.peek();
                do {
                    month.push_back(c);
                    iss.get();
                    c = iss.peek();
                } while (c != '/');
                iss.get();
                c = iss.peek();
                do {
                    year.push_back(c);
                    iss.get();
                    c = iss.peek();
                } while (c != ',');

                iss.ignore(18);
                double balance = 0.0;
                c = iss.peek();
                do {
                    balance *= 10;
                    balance += c - '0';
                    iss.get();
                    c = iss.peek();
                } while (std::isdigit(c));
              //!!!!!!
              Account acc(num, Date(day, month, year), Owner(name, adress, phoneNumber), balance);
              count++;
              //!!!!!!
                iss.ignore(15);
                c = iss.peek();
                while (c != ']'){
                    name.clear();
                    adress.clear();
                    phoneNumber.clear();
                    for(int i = 0; i < 7;i++){
                        iss.get();
                    }
                    c = iss.peek();
                    do {
                        name.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != ',');
                    iss.ignore(10);
                    c = iss.peek();
                    do {
                        adress.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != ',');
                    iss.ignore(15);
                    if((c = iss.peek()) == '+')
                    {
                        iss.get();
                        c = iss.peek();
                    }            
                    do {
                        phoneNumber.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '}');
                    iss.get();
                    iss.get();
                    c = iss.peek();
                    acc.addPartOwner(Owner(name, adress, phoneNumber));
                } 
                iss.ignore(12);
                c = iss.peek();
                while (c != ']'){
                    std::string nameT;
                    double amountT = 0.0;
                    double limitT = 0.0;                
                    day.clear();
                    month.clear();
                    year.clear();
                    iss.ignore(7);
                    c = iss.peek();
                    do {
                        nameT.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != ',');
                    iss.ignore(9);
                    c = iss.peek();
                    do {
                        amountT *= 10;
                        amountT += c - '0';
                        iss.get();
                        c = iss.peek();
                    } while (std::isdigit(c));
                    iss.ignore(8);
                    c = iss.peek();
                    do {
                        limitT *= 10;
                        limitT += c - '0';
                        iss.get();
                        c = iss.peek();
                    } while (std::isdigit(c));
                    iss.ignore(16);
                    c = iss.peek();
                    do {
                        day.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        month.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        year.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '}');
                    iss.get();
                    iss.get();
                    c = iss.peek();
                    acc.addTargets(Target(nameT, limitT, Date(day, month, year), amountT));               
                }
                iss.ignore(12);
                c = iss.peek();
                while(c != ']'){
                    std::string nameI;
                    double amountI = 0.0;
                    day.clear();
                    month.clear();
                    year.clear();
                    iss.ignore(7);
                    c = iss.peek();
                    do {
                        nameI.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != ',');
                    iss.ignore(9);
                    c = iss.peek();
                    do {
                        amountI *= 10;
                        amountI += c - '0';
                        iss.get();
                        c = iss.peek();
                    } while (std::isdigit(c));
                    iss.ignore(21);
                    c = iss.peek();
                    do {
                        day.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        month.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        year.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '}');
                    iss.get();
                    iss.get();
                    c = iss.peek();                
                    acc.addFunds(Payment(nameI, amountI, Payment_type::incomes, Date(day,month,year)));
                }

                iss.ignore(25);
                c = iss.peek();
                while(c != ']'){
                    std::string nameM;
                    double amountM = 0.0;
                    day.clear();
                    month.clear();
                    year.clear();
                    iss.ignore(7);
                    c = iss.peek();
                    do {
                        nameM.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != ',');
                    iss.ignore(9);
                    c = iss.peek();
                    do {
                        amountM *= 10;
                        amountM += c - '0';
                        iss.get();
                        c = iss.peek();
                    } while (std::isdigit(c));
                    iss.ignore(20);
                    c = iss.peek();
                    do {
                        day.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        month.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        year.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '}');
                    iss.get();
                    iss.get();
                    c = iss.peek();                
                    acc.addMonthlyPays(Payment(nameM, amountM, Payment_type::expens, Date(day,month,year)));
                }

                iss.ignore(13);
                c = iss.peek();
                while(c != ']'){
                    std::string nameP;
                    double amountP = 0.0;
                    day.clear();
                    month.clear();
                    year.clear();
                    iss.ignore(7);
                    c = iss.peek();
                    do {
                        nameP.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != ',');
                    iss.ignore(9);
                    c = iss.peek();
                    do {
                        amountP *= 10;
                        amountP += c - '0';
                        iss.get();
                        c = iss.peek();
                    } while (std::isdigit(c));
                    iss.ignore(20);
                    c = iss.peek();
                    do {
                        day.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        month.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '/');
                    iss.get();
                    c = iss.peek();
                    do {
                        year.push_back(c);
                        iss.get();
                        c = iss.peek();
                    } while (c != '}');
                    iss.get();
                    iss.get();
                    c = iss.peek();                
                    acc.addPayment(Payment(nameP, amountP, Payment_type::expens, Date(day,month,year)));
                }
                iss.get();
                iss.get();
                acounts.push_back(acc);
            }else{
                std::cout << "Fail" << std::endl;
            }
        }
        std::cout <<count<< " accountu bylo nacteno" << std::endl;
        file.close();
    }

    if (std::remove("Boo.txt") != 0) {
        std::cout << "Nepodařilo se smazat soubor.\n";
        
    } else {
        std::cout << "Soubor byl smazán.\n";
    }
}


/**
 * @brief Retrieves the day component of the date.
 * @return The day component of the date as a string.
 */
std::string Date::getDay() const { return day; }

/**
 * @brief Retrieves the month component of the date.
 * @return The month component of the date as a string.
 */
std::string Date::getMonth() const { return month; }

/**
 * @brief Retrieves the year component of the date.
 * @return The year component of the date as a string.
 */   
std::string Date::getYear() const { return year; }

/**
 * @brief Retrieves the full date in the format "day/month/year".
 * @return The full date as a string.
 */
std::string Date::getDate() const { return day + "/" + month + "/" + year; }

/**
 * @brief Retrieves the name of the target.
 * @return The name of the target as a string.
 */
std::string Target::getName() const  { return name; }

/**
 * @brief Retrieves the limit set for the target.
 * @return The limit set for the target.
 */
double Target::getLimit() const { return limit; }

/**
 * @brief Retrieves the target date.
 * @return The target date as a Date object.
 */
Date Target::getDate() const { return target_date; }

/**
 * @brief Sets a new target date.
 * @param NewDate The new target date.
 */
void Target::setTargetDate(Date NewDate){ target_date = NewDate; }

/**
 * @brief Sets a new limit for the target.
 * @param limit The new limit for the target.
 */
void Target::setTagetLimit(double limit){this->limit = limit;}

/**
 * @brief Sets a new name for the target.
 * @param NewName The new name for the target.
 */
void Target::setTargetName(std::string NewName){ name = NewName; }

/**
 * @brief Sets a new amount for the target.
 * @param n The new amount for the target.
 */
void Target::setTargetAmount(double n) { amount = n; }

/**
 * @brief Calculates and retrieves the difference between the limit and the current amount.
 * @return The difference between the limit and the current amount.
 */
double Target::getDifferences() { return limit - amount; }

/**
 * @brief Retrieves the current amount set for the target.
 * @return The current amount set for the target.
 */
double Target::getAmount() const { return amount; }

/**
 * @brief Adds a value to the current amount.
 * @param value The value to be added to the current amount.
 */
void Target::addAmount(double value){ amount += value; }

/**
 * @brief Checks if the target has been reached.
 * @return True if the amount is greater than or equal to the limit, otherwise false.
 */
bool Target::reached() { return amount >= limit; }

/**
 * @brief Converts the target information to a string format.
 * @return A string containing the target information in the format "name, date, limit".
 */
std::string Target::toString() { return name + "," + target_date.getDate() + "," + std::to_string(limit); }


/**
 * @brief Get the name associated with the payment.
 * @return The name of the payment as a string.
 */
std::string Payment::getName() const {return name;}

/**
 * @brief Get the amount of the payment.
 * @return The amount of the payment as a double.
 */
double Payment::getAmount() const  {return amount;}

/**
 * @brief Get the type of the payment.
 * @return The type of the payment as a Payment_type enum.
 */
Payment_type Payment::getType() const  {return ptyp;}

/**
 * @brief Get the date of the payment.
 * @return The date of the payment as a Date object.
 */
Date Payment::getDate() const  {return date;}

/**
 * @brief Set the amount of the payment.
 * @param a The amount to set for the payment.
 */
void Payment::setAmnt(double a) {amount = a;}

/**
 * @brief Set the type of the payment.
 * @param t The type to set for the payment.
 */
void Payment::setType(Payment_type t) {ptyp = t;}

/**
 * @brief Set the date of the payment.
 * @param d The date to set for the payment.
 */
void Payment::setDate(Date d) {date=d;}

/**
 * @brief Set the name associated with the payment.
 * @param n The name to set for the payment.
 */
void Payment::setName(std::string n){name=n;}

/**
 * @brief Convert the payment information to a string representation.
 * @return The payment information as a string.
 */
std::string Payment::toString() { return name + std::to_string(amount) +","+ static_cast<char>(ptyp) +","+ date.getDate(); }

/**
 * @brief Get the name of the owner.
 * 
 * @return std::string The name of the owner.
 */
std::string Owner::getName() const {return name;}

/**
 * @brief Get the address of the owner.
 * 
 * @return std::string The address of the owner.
 */
std::string Owner::getAddress() const {return address;}

/**
 * @brief Get the phone number of the owner.
 * 
 * @return std::string The phone number of the owner.
 */
std::string Owner::getPhoneNumber() const {return phoneNumber;}

/**
 * @brief Set the name of the owner.
 * 
 * @param n The new name of the owner.
 */
void Owner::setName(std::string n) {name = n;}

/**
 * @brief Set the address of the owner.
 * 
 * @param a The new address of the owner.
 */
void Owner::setAddress(std::string a) {address = a;}

/**
 * @brief Set the phone number of the owner.
 * 
 * @param pN The new phone number of the owner.
 */
void Owner::setPhoneNumber(std::string pN) {phoneNumber = pN;}

/**
 * @brief Generate a string representation of the owner.
 * 
 * This method concatenates the name, address, and phone number of the owner
 * and returns it as a single string.
 * 
 * @return std::string A string representation of the owner.
 */
std::string Owner::toString(){return getName() + getAddress() + getPhoneNumber();}


/**
 * @brief Sets the owner's name for the account.
 * 
 * @param newName The new name of the owner.
 */
void Account::setOwnerName(std::string newName){
    owner.setName(newName);
}

/**
 * @brief Sets the owner's address for the account.
 * 
 * @param newAddress The new address of the owner.
 */
void Account::setOwnerAdress(std::string newAdress){
    owner.setName(newAdress);
}

/**
 * @brief Sets the owner's phone number for the account.
 * 
 * @param newPhone The new phone number of the owner.
 */
void Account::setOwnerPhone(std::string newPhone){
    owner.setPhoneNumber(newPhone);
}

// Getters

/**
 * @brief Gets the account number.
 * 
 * @return int The account number.
 */
int Account::getAccountNumber() const {
    return accountNumber;
}

/**
 * @brief Gets the current balance of the account.
 * 
 * @return double The current balance.
 */
double Account::getBalance() const {
    return balance;
}

/**
 * @brief Gets the date of assembly of the account.
 * 
 * @return Date The date of assembly.
 */
Date Account::getDateOfAssebly() const {
    return date_of_assembly;
}

/**
 * @brief Gets the primary owner of the account.
 * 
 * @return Owner The primary owner.
 */
Owner Account::getOwner() const {
    return owner;
}

/**
 * @brief Gets the number of part owners associated with the account.
 * 
 * @return int The number of part owners.
 */
int Account::numberOfPartOwners() const {
    return part_owners.size();
}

/**
 * @brief Gets the list of part owners associated with the account.
 * 
 * @return std::vector<Owner> The list of part owners.
 */
std::vector<Owner> Account::getPartOwners() const {
    return  part_owners;
}

/**
 * @brief Gets the number of targets associated with the account.
 * 
 * @return int The number of targets.
 */
int Account::numberOfTargets()  {
    return targets.size();
}

/**
 * @brief Gets the list of targets associated with the account.
 * 
 * @return std::vector<Target> The list of targets.
 */
std::vector<Target> Account::getTargets() const {
    return  targets;
}

/**
 * @brief Gets the number of monthly payments associated with the account.
 * 
 * @return int The number of monthly payments.
 */
int Account::numberOfMonthlyPayments() const {
    return monthly_pays.size();
}

/**
 * @brief Gets the list of monthly payments associated with the account.
 * 
 * @return std::vector<Payment> The list of monthly payments.
 */
std::vector<Payment> Account::getMontlyPays() const {
    return  monthly_pays;
}

/**
 * @brief Gets the number of payments associated with the account.
 * 
 * @return int The number of payments.
 */
int Account::numberOfPayments() const {
    return payments.size();
}

/**
 * @brief Gets the list of payments associated with the account.
 * 
 * @return std::vector<Payment> The list of payments.
 */
std::vector<Payment> Account::getPayments() const {
    return  payments;
}

/**
 * @brief Gets the number of incomes associated with the account.
 * 
 * @return int The number of incomes.
 */
int Account::numberOfIncomes() const {
    return incomes.size();
}

/**
 * @brief Gets the list of incomes associated with the account.
 * 
 * @return std::vector<Payment> The list of incomes.
 */
std::vector<Payment> Account::getIncomes() const {
    return  incomes;
}

// Add functions

/**
 * @brief Adds a part owner to the account.
 * 
 * @param part_owner The part owner to add.
 */
void Account::addPartOwner(Owner part_owner){
    part_owners.push_back(part_owner);
}

/**
 * @brief Adds a target to the account.
 * 
 * @param target The target to add.
 */
void Account::addTargets(Target target){
    targets.push_back(target);
}

/**
 * @brief Adds a payment to the account.
 * 
 * Checks if the payment already exists in the payments list, and if not, adds it to the list 
 * and deducts the payment amount from the balance.
 * 
 * @param pay The Payment object to be added.
 * @throw Throws an exception if the payment already exists.
 */
void Account::addPayment(Payment pay){
    for (auto &i : payments) {
        if (i.getName() == pay.getName() && i.getType() == pay.getType()) {
            throw "This payment already exists.";
        }
    }
    payments.push_back(pay);
    balance-=pay.getAmount();
}

/**
 * @brief Adds a monthly payment to the account.
 * 
 * Checks if the monthly payment already exists in the monthly_pays list, and if not, adds it to 
 * the list and deducts the payment amount from the balance.
 * 
 * @param monthly_payments The monthly Payment object to be added.
 * @throw Throws an exception if the monthly payment already exists.
 */
void Account::addMonthlyPays(Payment monthly_payments) {
    for (auto &i : monthly_pays) {
        if (i.getName() == monthly_payments.getName() && i.getType() == monthly_payments.getType()) {
            throw "This monthly payment already exists.";
        }
    }
    monthly_pays.push_back(monthly_payments);
    balance -= monthly_payments.getAmount();
}

/**
 * @brief Adds funds to the account.
 * 
 * Adds the given funds to the incomes list and updates the account balance accordingly.
 * 
 * @param fund The Payment object representing the funds to be added.
 */
void Account::addFunds(Payment fund){
    incomes.push_back(fund);
    balance+=fund.getAmount();
}

/**
 * @brief Adds funds to a specific target.
 * 
 * Searches for the target with the given name and adds the specified amount to it.
 * 
 * @param name The name of the target fund.
 * @param Amount The amount to be added to the target fund.
 */
void Account::addTargetFund(std::string name, double Amount){
    for(auto n : targets){
        if(n.getName()==name){
            n.addAmount(Amount);
        }
    }
}

/**
 * @brief Prints all monthly payments.
 * 
 * Prints each monthly payment in the monthly_pays list to the standard output.
 */
void Account::printMonthly(){
    for(auto n :  monthly_pays){
        std::cout << n << std::endl;
        
    }
    
}

/**
 * @brief Prints all payments.
 * 
 * Prints each payment in the payments list to the standard output.
 */
void Account::printPayments(){
    for(auto n :  payments){
        std::cout << n << std::endl;
        
    }
    
}

/**
 * @brief Prints all target funds.
 * 
 * Prints each target fund in the targets list to the standard output.
 */
void Account::printTargets(){
    for(auto n :  targets){
        std::cout << n << std::endl;
        
    }
    
}

/**
 * @brief Prints all incomes.
 * 
 * Prints each income in the incomes list to the standard output.
 */
void Account::printIncomes(){
    for(auto n :  incomes){
        std::cout << n << std::endl;
        
    }
    
}

/**
 * @brief Prints all partial owners.
 * 
 * Prints each partial owner in the part_owners list to the standard output.
 */
void Account::printPartOwners(){
    for(auto n :  part_owners){
        std::cout << n << std::endl;
        
    }
    
}

/**
 * @brief Removes a target fund.
 * 
 * Searches for the target fund with the given name and removes it from the targets list.
 * 
 * @param name The name of the target fund to be removed.
 */
void Account::removeTarget(std::string name){
    for (auto &i: targets) {
        if (i.getName() == name) {
            targets.pop_back();
            break;
        }
    }
}

/**
 * @brief Removes a partial owner.
 * 
 * Searches for the partial owner with the given name and removes it from the part_owners list.
 * 
 * @param name The name of the partial owner to be removed.
 */
void Account::removePartOwner(std::string name){
    for(auto &i : part_owners){
        if(i.getName() == name){
            part_owners.pop_back();
            break;
        }
    }
}

/**
 * @brief Print the information of the account.
 * 
 * This function prints the account number, owner, assembly date, and balance
 * of the account to the standard output.
 * 
 * @note This function assumes that the appropriate getters (getAccountNumber(),
 * getOwner(), getDateOfAssebly(), and getBalance()) are defined in the Account class.
 * 
 * @see Account
 */
void Account::printInformationAccount(){
    std::cout <<"- Account number: "<< getAccountNumber() <<std::endl;
    std::cout <<"- Account owner: " << getOwner() <<std::endl;
    std::cout <<"- Account assebly date: "<< getDateOfAssebly() <<std::endl;
    std::cout <<"- Account ballace: " << getBalance() <<std::endl;
}

/**
 * Calculates the remaining months needed to reach the target amount for a specific target,
 * and whether the target will be reached within that time frame.
 * 
 * @param monthsRemaining A vector to store pairs of target names and their remaining months needed to reach the target, along with a flag indicating whether the target will be reached.
 * @param targetName The name of the target for which the calculation is performed.
 */
void Account::monthsToTarget(std::vector<std::pair<std::string, std::pair<int, bool>>>& monthsRemaining, const std::string& targetName) {
    // Get the current date
    std::time_t currentTime = std::time(nullptr);
    std::tm* currentDate = std::localtime(&currentTime);

    int currentYear = currentDate->tm_year + 1900;
    int currentMonth = currentDate->tm_mon + 1;

    for (const auto& target : targets) {
        if (target.getName() == targetName) {
            double targetLimit = target.getLimit();
            double targetAmount = target.getAmount();
                        
            // Sum up all monthly contributions towards the target
            double monthlyContribution = 0.0;
            for (const auto& monthlyPay : monthly_pays) {
                if (monthlyPay.getName() == targetName) {
                    monthlyContribution += monthlyPay.getAmount();
                }
            }

            // Calculate the remaining time to reach the target
            if (targetAmount < targetLimit && monthlyContribution > 0) {
                // Calculate the required time in months based on the monthly contribution
                int monthsNeeded = static_cast<int>(std::ceil((targetLimit - targetAmount) / monthlyContribution));
                        
                // Extract month and year from the target date
                int targetYear = std::stoi(target.getDate().getYear());
                int targetMonth = std::stoi(target.getDate().getMonth());

                // Calculate the number of months to the target date
                int monthsToTargetDate = (targetYear - currentYear) * 12 + (targetMonth - currentMonth);

                // Determine if the target will be reached or not
                bool targetReached = monthsNeeded <= monthsToTargetDate;

                // Add a pair to the output vector
                monthsRemaining.push_back(std::make_pair(targetName, std::make_pair(monthsNeeded, targetReached)));
            }
        }
    }
}

/**
 * @brief Prints the details of the account including account number, owner, date of assembly, balance, targets, monthly pays, incomes, and payments.
 */
void Account::prettyPrintAccount(){std::cout << "Account number: " << std::to_string(accountNumber) << std::endl;
                            std::cout << "Owner: " << owner << std::endl;
                            std::cout << "Date of assembly: " << date_of_assembly.getDate()<<std::endl;
                            std::cout << "Balance: " << std::to_string(balance) << std::endl;
                            std::cout << std::endl;
                            std::cout << "Targets: " << std::endl;
                            if(targets.size() > 0){
                                printTargets();
                            }else{
                                std::cout <<"None"<< std::endl;
                            }
                            std::cout << std::endl;
                            std::cout << "Monthly pays: " << std::endl;                                  
                            if(monthly_pays.size() > 0){
                                printMonthly();
                            }else{
                                std::cout <<"None"<< std::endl;
                            }
                            std::cout << std::endl;
                            std::cout << "Incomes: " << std::endl;                                  
                            if(incomes.size() > 0){
                                printIncomes();
                            }else{
                                std::cout <<"None"<< std::endl;
                            }
                            std::cout << std::endl;
                            std::cout << "Payments: " << std::endl;
                            
                            if(payments.size() > 0){
                                printPayments();
                            }else{
                                std::cout <<"None"<< std::endl;
                            }

                            std::cout << "__________________" << std::endl;                             
}

/**
 * @brief Calculates the total expenses in the account.
 * 
 * This function iterates through all payments associated with the account
 * and sums up the amounts of payments categorized as expenses.
 * 
 * @return The total expenses in the account.
 */
double Account::calculateTotalExpenses() {
    double totalExpenses = 0.0;
    for (const Payment& payment : getPayments()) {
        if (payment.getType() == Payment_type::expens) {
            totalExpenses += payment.getAmount();
        }
    }
    return totalExpenses;
}

/**
 * @brief Calculates the total income in the account.
 * 
 * This function iterates through all payments associated with the account
 * and sums up the amounts of payments categorized as income.
 * 
 * @return The total income in the account.
 */
double Account::calculateTotalIncome() {
    double totalIncome = 0.0;
    for (const Payment& payment : getIncomes()) {
        totalIncome += payment.getAmount();
    }
    return totalIncome;
}

/**
 * @brief Generates a spending habits report for the account.
 * 
 * This function generates a report detailing the spending habits of the account.
 * It prints the total expenses, total income, and completion percentage for each target.
 */
void Account::generateSpendingHabitsReport() {
    std::cout << "Spending Habits Report for Account " << getAccountNumber() << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Total Expenses: $" << calculateTotalExpenses() << std::endl;
    std::cout << "Total Income: $" << calculateTotalIncome() << std::endl;        
    // Calculate and print percentage completion for each target
    std::cout << "Targets:" << std::endl;
    for (const auto& target : getTargets()) {
        double completionPercentage = (target.getAmount() / target.getLimit()) * 100.0;
        std::cout << "- " << target.getName() << ": " << completionPercentage << "% done." << std::endl;
    }        
    std::cout << "---------------------------------------" << std::endl;
}

/**
 * @brief Generates a spending habits report in JSON format for the account.
 * 
 * This function generates a spending habits report in JSON format, including
 * information such as total expenses, total income, and completion percentage
 * for each target.
 * 
 * @return A string containing the spending habits report in JSON format.
 */
std::string Account::generateSpendingHabitsReportJson() {
    std::string result;
    result.append("Spending Habits Report for Account " + std::to_string(getAccountNumber()) + '\n');
    result.append("---------------------------------------\n");

    std::ostringstream stream; // Declare ostringstream object outside the loop

    // Format and append total expenses
    stream << std::fixed << std::setprecision(2) << calculateTotalExpenses();
    result.append("Total Expenses: $" + stream.str() + '\n');
    stream.str(""); // Clear stringstream for reuse

    // Format and append total income
    stream << std::fixed << std::setprecision(2) << calculateTotalIncome();
    result.append("Total Income: $" + stream.str() + '\n');
    stream.str(""); // Clear stringstream for reuse

    // Append Targets header
    result.append("Targets:\n");

    // Format and append completion percentage for each target
    for (const auto& target : getTargets()) {
        double completionPercentage = (target.getAmount() / target.getLimit()) * 100.0;
        stream << std::fixed << std::setprecision(2) << completionPercentage;
        result.append("- " + target.getName() + ": " + stream.str() + "% done.\n");
        stream.str(""); // Clear stringstream for reuse
    }

    result.append("---------------------------------------\n");

    return result;
}