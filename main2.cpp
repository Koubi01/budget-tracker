#include <iostream>
#include <fstream>
#include "lib.h" 
#include "Huff.h"


char displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Load data from file\n";
    std::cout << "2. Display account information\n";
    std::cout << "3. Change something to account\n";
    std::cout << "4. New account dont work i lost it \n";
    std::cout << "5. Add to account\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

int main() {
    std::vector<Account> ac;

    char choice;
    do {
        choice = displayMenu(); // Display menu and get user choice
        switch (choice) {
            case '1': {
                // Load data from file     
                loadFromFile("buff.huff", ac);
                break;
            }
            case '2': {
                    int count = 1;
                    for (auto& account : ac) {
                        std::cout << count << " - " << account.getAccountNumber() << std::endl;
                        count++;
                    }                    
                    std::cout << "0. Everyone\n";
                    std::cout << "1. Only one\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    switch (choice) {
                        char acc;
                        case '0': {
                            for (auto& account : ac) {
                                std::cout << "---------------------------------------" << std::endl;
                                account.prettyPrintAccount();
                                account.generateSpendingHabitsReport();
                                std::cout << "---------------------------------------" << std::endl;
                            }                       
                            break;
                        }
                        case '1': {
                            std::cout << "Which one: ";
                            std::cin >> acc;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                            int accI = (int)acc - '0';
                            if (accI >= 1 && accI <= ac.size()) {
                                char subChoice;
                                do {
                                    std::cout << "What do you want to see?\n";
                                    std::cout << "0. Everything\n";
                                    std::cout << "1. Part Owners\n";
                                    std::cout << "2. Targets\n";
                                    std::cout << "3. Monthly Pays\n";
                                    std::cout << "4. Payments\n";
                                    std::cout << "5. Incomes\n";
                                    std::cout << "6. Spending habits\n";
                                    std::cout << "7. Months to Target\n";
                                    std::cout << "Enter your choice (or 'x' to go back): ";
                                    std::cin >> subChoice;
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    switch (subChoice) {
                                        case '0': {
                                            ac[accI - 1].prettyPrintAccount();
                                            ac[accI - 1].generateSpendingHabitsReport();
                                            break;
                                        }
                                        case '1': {
                                            ac[accI - 1].printInformationAccount();
                                            ac[accI - 1].printPartOwners();
                                            break;
                                        }
                                        case '2': {
                                            ac[accI - 1].printInformationAccount();
                                            ac[accI - 1].printTargets();
                                            break;
                                        }
                                        case '3': {
                                            ac[accI - 1].printInformationAccount();
                                            ac[accI - 1].printMonthly();
                                            break;
                                        }
                                        case '4': {
                                            ac[accI - 1].printInformationAccount();
                                            ac[accI - 1].printPayments();
                                            break;
                                        }
                                        case '5': {
                                            ac[accI - 1].printInformationAccount();
                                            ac[accI - 1].printIncomes();
                                            break;
                                        }
                                        case '6': {
                                            ac[accI - 1].printInformationAccount();
                                            ac[accI - 1].generateSpendingHabitsReport();
                                            break;
                                        }
                                        case '7': {
                                                std::string namesInput;
                                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                ac[accI - 1].printInformationAccount();
                                                std::cout << "Available targets:\n";
                                                for (auto& tar : ac[accI - 1].getTargets()) {
                                                    std::cout << "- "<< tar.getName() << std::endl;
                                                }
                                                std::cout << "Enter target names separated by commas: ";
                                                std::getline(std::cin, namesInput);
                                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                                std::vector<std::string> targetNames;
                                                std::istringstream iss(namesInput);
                                                std::string name;
                                                while (std::getline(iss, name, ',')) {
                                                    
                                                    name.erase(0, name.find_first_not_of("\t\r\n"));
                                                    name.erase(name.find_last_not_of("\t\r\n") + 1);
                                                    targetNames.push_back(name);
                                                }
                                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                                std::vector<std::pair<std::string, std::pair<int, bool>>> monthsAccount;

                                                for (const auto& targetName : targetNames) {
                                                    ac[accI - 1].monthsToTarget(monthsAccount, targetName);                                                    
                                                }

                                                for (const auto& target : monthsAccount) {
                                                        std::cout<<"- " << target.first << ": " << target.second.first << " months, "
                                                                << (target.second.second ? "Target reached" : "Target not reached") << " in time." << std::endl;
                                                    }
                                                break;
                                        }
                                        case 'x': {
                                            break;
                                        }
                                        default: {
                                            std::cout << "Invalid choice. Please try again.\n";
                                            break;
                                        }
                                    }
                                } while (subChoice != 'x');
                            } else {
                                std::cout << "Invalid account number.\n";
                            }
                            break;
                        }
                        default: {
                            std::cout << "Invalid choice. Please try again.\n";
                            break;
                        }
                    }
                    break;
                }
            case '3': {
                    int count = 1;
                    for (auto& account : ac) {
                        std::cout << count << " - " << account.getAccountNumber() << std::endl;
                        count++;
                    }
                    
                    std::cout << "Which account u want to change?\n";
                    std::cout << "Which one: ";
                    char acc;
                    std::cin >> acc;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    int accI = (int)acc - '0';
                    if (accI >= 1 && accI <= ac.size()) {
                        char subChoice;
                        do {
                            std::cout << "What do you want to change?\n";
                            std::cout << "0. Account Owner\n";
                            std::cout << "1. Part owner\n";
                            std::cout << "2. Target\n";
                            std::cout << "3. Monthly Pay\n";
                            std::cout << "4. Payment\n";
                            std::cout << "5. Income\n";
                            std::cout << "Enter your choice (or 'x' to go back): ";
                            std::cin >> subChoice;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                            switch (subChoice) {
                                case '0' : {
                                    char subsubChoice;
                                    std::cout << "- " << ac[accI - 1].getOwner() << std::endl;
                                    std::cout << "What do u want to change?\n";
                                    std::cout << "0. everything\n";
                                    std::cout << "1. name\n";
                                    std::cout << "2. address\n";
                                    std::cout << "3. phone number\n";
                                    std::cin >> subsubChoice;
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    switch (subsubChoice)
                                    {
                                    case '0':{
                                        std::string Input;
                                        std::cout << "Enter changes separated by commas in this order: name, address, phone number: ";
                                        std::getline(std::cin, Input);
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                        std::vector<std::string> Changes;
                                        std::istringstream iss(Input);
                                        std::string change;
                                        while (std::getline(iss, change, ',')) {
                                            
                                            change.erase(0, change.find_first_not_of("\t\r\n"));
                                            change.erase(change.find_last_not_of("\t\r\n") + 1);
                                            Changes.push_back(change);
                                        }
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                        ac[accI - 1].setOwnerName(Changes[0]);
                                        ac[accI - 1].setOwnerAdress(Changes[1]);
                                        ac[accI - 1].setOwnerPhone(Changes[2]);

                                        std::cout << "Owner was changes to this:\n";
                                        std::cout << "- " << ac[accI - 1].getOwner() << std::endl;
                                        break;
                                    }
                                    case '1':{
                                        std::string Input;
                                        std::cout << "Enter changes name: ";
                                        std::getline(std::cin, Input);
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                        ac[accI - 1].setOwnerName(Input);
                                        std::cout << "Owner was changes to this:\n";
                                        std::cout << "- " << ac[accI - 1].getOwner() << std::endl;
                                        break;
                                    }
                                    case '2':{
                                        std::string Input;
                                        std::cout << "Enter changes address: ";
                                        std::getline(std::cin, Input);
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                        ac[accI - 1].setOwnerAdress(Input);
                                        std::cout << "Owner was changes to this:\n";
                                        std::cout << "- " << ac[accI - 1].getOwner() << std::endl;
                                        break;
                                    }
                                    case '3':{
                                        std::string Input;
                                        std::cout << "Enter changes phone number: ";
                                        std::getline(std::cin, Input);
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                        ac[accI - 1].setOwnerPhone(Input);
                                        std::cout << "Owner was changes to this:\n";
                                        std::cout << "- " << ac[accI - 1].getOwner() << std::endl;
                                        break;
                                    }                                        
                                    
                                    default:
                                        std::cout << "Invalid choice. Please try again.\n";
                                        break;
                                    }
                                    break;

                                }
                                case '1' : {
                                    char subsubChoice;
                                    if(ac[accI - 1].numberOfPartOwners() == 0){
                                        std::cout << "None Part Owner" << std::endl;
                                        break;
                                    }
                                    for(auto& par : ac[accI - 1].getPartOwners()){
                                        std::cout << "- " << par << std::endl;
                                    }
                                    std::cout <<"Which one u want to change: \n";
                                    std::string nameFromAcc;
                                    std::string nameFromInp;
                                    std::getline(std::cin, nameFromInp);
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    for(auto& par : ac[accI - 1].getPartOwners()){
                                        nameFromAcc = par.getName();
                                        if(nameFromAcc == nameFromInp)
                                        {   
                                            std::cout << "- " << par << std::endl;
                                            std::cout << "What do u want to change?\n";
                                            std::cout << "0. name\n";
                                            std::cout << "1. address\n";
                                            std::cout << "2. phone number\n";
                                            std::cin >> subsubChoice;
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                            switch (subsubChoice)
                                            {
                                                case'0':{
                                                    std::string Input;
                                                    std::cout << "Enter changes name: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setName(Input);
                                                    std::cout << "Owner was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'1':{
                                                    std::string Input;
                                                    std::cout << "Enter changes address: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setAddress(Input);
                                                    std::cout << "Owner was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'2':{
                                                    std::string Input;
                                                    std::cout << "Enter changes phone number: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setPhoneNumber(Input);
                                                    std::cout << "Owner was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                default:{
                                                    std::cout << "Invalid choice. Please try again.\n";
                                                    break;
                                                }
                                                
                                            }
                                        }
                                    }
                                    break;                                
                                }
                                case '2' : {
                                    char subsubChoice;
                                    if(ac[accI - 1].numberOfTargets() == 0){
                                        std::cout << "None Target" << std::endl;
                                        break;
                                    }
                                    for(auto& par : ac[accI - 1].getTargets()){
                                        std::cout << "- " << par << std::endl;
                                    }
                                    std::cout <<"Which one u want to change: \n";
                                    std::string nameFromAcc;
                                    std::string nameFromInp;
                                    std::getline(std::cin, nameFromInp);
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    for(auto& par : ac[accI - 1].getTargets()){
                                        nameFromAcc = par.getName();
                                        if(nameFromAcc == nameFromInp)
                                        { 
                                            std::cout << "- " << par << std::endl;
                                            std::cout << "What do u want to change?\n";
                                            std::cout << "0. name\n";
                                            std::cout << "1. date\n";
                                            std::cout << "2. limit\n";
                                            std::cin >> subsubChoice; 
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                            switch (subsubChoice)
                                            {
                                                case'0':{
                                                    std::string Input;
                                                    std::cout << "Enter changes name: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setTargetName(Input);
                                                    std::cout << "Target was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'1':{
                                                    std::string Input;
                                                    std::cout << "Enter changes date in this format dd,mm,yyyy: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    std::vector<std::string> Changes;
                                                    std::istringstream iss(Input);
                                                    std::string change;
                                                    while (std::getline(iss, change, ',')) {
                                                        
                                                        change.erase(0, change.find_first_not_of("\t\r\n"));
                                                        change.erase(change.find_last_not_of("\t\r\n") + 1);
                                                        Changes.push_back(change);
                                                    }
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setTargetDate(Date(Changes[0],Changes[1],Changes[2]));
                                                    std::cout << "Target was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'2':{
                                                    std::string Input;
                                                    std::cout << "Enter changes limnit: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    double limit = atof(Input.c_str());
                                                    par.setTagetLimit(limit);
                                                    std::cout << "Target was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                default:{
                                                    std::cout << "Invalid choice. Please try again.\n";
                                                    break;
                                                }
                                            }
                                        }
                                        
                                    } 
                                    break;
                                }
                                case '3' : {
                                    char subsubChoice;
                                    if(ac[accI - 1].numberOfMonthlyPayments() == 0){
                                        std::cout << "None Monthly Payment" << std::endl;
                                        break;
                                    }
                                    for(auto& par : ac[accI - 1].getMontlyPays()){
                                        std::cout << "- " << par << std::endl;
                                    }
                                    std::cout <<"Which one u want to change: \n";
                                    std::string nameFromAcc;
                                    std::string nameFromInp;
                                    std::getline(std::cin, nameFromInp);
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    for(auto& par : ac[accI - 1].getMontlyPays()){
                                        nameFromAcc = par.getName();
                                        if(nameFromAcc == nameFromInp)
                                        { 
                                            std::cout << "- " << par << std::endl;
                                            std::cout << "What do u want to change?\n";
                                            std::cout << "0. name\n";
                                            std::cout << "1. date\n";
                                            std::cout << "2. amount\n";
                                            std::cin >> subsubChoice; 
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                            switch (subsubChoice)
                                            {
                                                case'0':{
                                                    std::string Input;
                                                    std::cout << "Enter changes name: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setName(Input);
                                                    std::cout << "MontlyPay was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'1':{
                                                    std::string Input;
                                                    std::cout << "Enter changes date in this format dd,mm,yyyy: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    std::vector<std::string> Changes;
                                                    std::istringstream iss(Input);
                                                    std::string change;
                                                    while (std::getline(iss, change, ',')) {
                                                        
                                                        change.erase(0, change.find_first_not_of("\t\r\n"));
                                                        change.erase(change.find_last_not_of("\t\r\n") + 1);
                                                        Changes.push_back(change);
                                                    }
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setDate(Date(Changes[0],Changes[1],Changes[2]));
                                                    std::cout << "MontlyPay was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'2':{
                                                    std::string Input;
                                                    std::cout << "Enter changes limnit: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    double limit = atof(Input.c_str());
                                                    par.setAmnt(limit);
                                                    std::cout << "MontlyPay was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                default:{
                                                    std::cout << "Invalid choice. Please try again.\n";
                                                    break;
                                                }
                                            }
                                        }
                                        
                                    } 
                                    break;
                                }
                                case '4' : {
                                    char subsubChoice;
                                    if(ac[accI - 1].numberOfPayments() == 0){
                                        std::cout << "None Payment" << std::endl;
                                        break;
                                    }

                                    for(auto& par : ac[accI - 1].getPayments()){
                                        std::cout << "- " << par << std::endl;
                                    }
                                    std::cout <<"Which one u want to change: \n";
                                    std::string nameFromAcc;
                                    std::string nameFromInp;
                                    std::getline(std::cin, nameFromInp);
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    for(auto& par : ac[accI - 1].getPayments()){
                                        nameFromAcc = par.getName();
                                        if(nameFromAcc == nameFromInp)
                                        { 
                                            std::cout << "- " << par << std::endl;
                                            std::cout << "What do u want to change?\n";
                                            std::cout << "0. name\n";
                                            std::cout << "1. date\n";
                                            std::cout << "2. amount\n";
                                            std::cin >> subsubChoice; 
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                            switch (subsubChoice)
                                            {
                                                case'0':{
                                                    std::string Input;
                                                    std::cout << "Enter changes name: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setName(Input);
                                                    std::cout << "Payment was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'1':{
                                                    std::string Input;
                                                    std::cout << "Enter changes date in this format dd,mm,yyyy: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    std::vector<std::string> Changes;
                                                    std::istringstream iss(Input);
                                                    std::string change;
                                                    while (std::getline(iss, change, ',')) {
                                                        
                                                        change.erase(0, change.find_first_not_of("\t\r\n"));
                                                        change.erase(change.find_last_not_of("\t\r\n") + 1);
                                                        Changes.push_back(change);
                                                    }
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setDate(Date(Changes[0],Changes[1],Changes[2]));
                                                    std::cout << "Payment was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'2':{
                                                    std::string Input;
                                                    std::cout << "Enter changes limnit: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    double limit = atof(Input.c_str());
                                                    par.setAmnt(limit);
                                                    std::cout << "Payment was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                default:{
                                                    std::cout << "Invalid choice. Please try again.\n";
                                                    break;
                                                }
                                            }
                                        }
                                        
                                    } 
                                    break;
                                }
                                case '5' : {
                                    char subsubChoice;
                                    if(ac[accI - 1].numberOfIncomes() == 0){
                                        std::cout << "None Inocmes" << std::endl;
                                        break;
                                    }

                                    for(auto& par : ac[accI - 1].getIncomes()){
                                        std::cout << "- " << par << std::endl;
                                    }
                                    std::cout <<"Which one u want to change: \n";
                                    std::string nameFromAcc;
                                    std::string nameFromInp;
                                    std::getline(std::cin, nameFromInp);
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                                    for(auto& par : ac[accI - 1].getIncomes()){
                                        nameFromAcc = par.getName();
                                        if(nameFromAcc == nameFromInp)
                                        { 
                                            std::cout << "- " << par << std::endl;
                                            std::cout << "What do u want to change?\n";
                                            std::cout << "0. name\n";
                                            std::cout << "1. date\n";
                                            std::cout << "2. amount\n";
                                            std::cin >> subsubChoice; 

                                            switch (subsubChoice)
                                            {
                                                case'0':{
                                                    std::string Input;
                                                    std::cout << "Enter changes name: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setName(Input);
                                                    std::cout << "Income was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'1':{
                                                    std::string Input;
                                                    std::cout << "Enter changes date in this format dd,mm,yyyy: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    std::vector<std::string> Changes;
                                                    std::istringstream iss(Input);
                                                    std::string change;
                                                    while (std::getline(iss, change, ',')) {
                                                        
                                                        change.erase(0, change.find_first_not_of("\t\r\n"));
                                                        change.erase(change.find_last_not_of("\t\r\n") + 1);
                                                        Changes.push_back(change);
                                                    }
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    par.setDate(Date(Changes[0],Changes[1],Changes[2]));
                                                    std::cout << "Income was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                case'2':{
                                                    std::string Input;
                                                    std::cout << "Enter changes limnit: ";
                                                    std::getline(std::cin, Input);
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                                    double limit = atof(Input.c_str());
                                                    par.setAmnt(limit);
                                                    std::cout << "Income was changes to this:\n";
                                                    std::cout << "- " << par << std::endl;
                                                    break;
                                                }
                                                default:{
                                                    std::cout << "Invalid choice. Please try again.\n";
                                                    break;
                                                }
                                            }
                                        }
                                        
                                    } 
                                    break;
                                }
                                case 'x' : {
                                    break;
                                }
                                default : {
                                    std::cout << "Invalid choice. Please try again.\n";
                                    break;
                                }
                            }

                        } while (subChoice != 'x');
                    }else{
                        std::cout << "Invalid account number: " << acc << std::endl;
                    }
                    

            }
            case '4': {
                char num;
                std::string balance;
                std::vector<std::string> V_Input;
                std::vector<std::string> V_date;

                std::string input;
                std::string ldate;

                std::cout << "Enter account number:\n";
                std::cin >> num;
                int I_Num = (int)num - '0';
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                
                std::cout << "Enter account balance:\n";
                std::getline(std::cin, balance);
                double D_Balance = atof(balance.c_str());
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << balance <<std::endl; 

                std::cout << "Enter account Owner in this format: name,address,phoneNumber:\n";                
                std::getline(std::cin, input);                
                std::istringstream isso(input);
                std::cout << input << std::endl;
                std::string newO;
                while (std::getline(isso, newO, ',')) {
                    newO.erase(0, newO.find_first_not_of("\t\r\n"));
                    newO.erase(newO.find_last_not_of("\t\r\n") + 1);    
                    std::cout << newO << std::endl;                
                    V_Input.push_back(newO);
                }            
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                std::cout << "Enter account Date of assembly in this format: dd,mm,yyyy:\n";
                std::getline(std::cin, ldate);                
                std::istringstream iss1(ldate);
                std::cout << ldate << std::endl;
                std::string new1;
                while (std::getline(iss1, new1, ',')) {
                    new1.erase(0, new1.find_first_not_of("\t\r\n"));
                    new1.erase(new1.find_last_not_of("\t\r\n") + 1);
                    std::cout << new1 << std::endl;
                    V_date.push_back(new1);
                }            
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << V_date[0] << std::endl;
                std::cout << V_date[1] << std::endl;
                std::cout << V_date[2] << std::endl;
                std::cout << V_Input[0] << std::endl;
                std::cout << V_Input[1] << std::endl;
                std::cout << V_Input[2] << std::endl;

                ac.push_back(Account(I_Num, Date(V_date[0],V_date[1],V_date[2]), Owner(V_Input[0],V_Input[1],V_Input[2]), D_Balance));
                
                for(auto& a : ac){
                    if(a.getAccountNumber() == I_Num){
                        a.prettyPrintAccount();
                    }
                }

            }
            case '5': {
                int count = 1;
                for (auto& account : ac) {
                    std::cout << count << " - " << account.getAccountNumber() << std::endl;
                    count++;
                }
                
                std::cout << "Which account u want to add something?\n";
                std::cout << "Which one: ";
                char acc;
                std::cin >> acc;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                int accI = (int)acc - '0';
                if (accI >= 1 && accI <= ac.size()) {
                    char subChoice;
                    do {
                        std::cout << "What do you want to add?\n";
                        std::cout << "0. Part owner\n";
                        std::cout << "1. Target\n";
                        std::cout << "2. Monthly Pay\n";
                        std::cout << "3. Payment\n";
                        std::cout << "4. Income\n";
                        std::cout << "Enter your choice (or 'x' to go back): ";
                        std::cin >> subChoice;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                        switch (subChoice) {
                            case '0' : {
                                std::vector<std::string> V_Owner;
                                std::string owner;
                                std::cout << "Enter account Part owner in this format: name,address,phoneNumber: ";                
                                std::getline(std::cin, owner);                
                                std::istringstream isso(owner);
                                std::string newO;
                                while (std::getline(isso, newO, ',')) {
                                    
                                    newO.erase(0, newO.find_first_not_of("\t\r\n"));
                                    newO.erase(newO.find_last_not_of("\t\r\n") + 1);
                                    V_Owner.push_back(newO);
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                ac[accI - 1].addPartOwner(Owner(V_Owner[0],V_Owner[1],V_Owner[2]));
                                std::cout << "This part owner was add" << std::endl;
                                std::cout << Owner(V_Owner[0],V_Owner[1],V_Owner[2]) << std::endl;
                            }
                            case '1' : {
                                std::string name;
                                std::string limit;
                                std::string amount;
                                std::vector<std::string> V_Date;
                                std::string date;
                                std::cout << "Enter account target name: ";
                                std::getline(std::cin, name);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account target limit: ";
                                std::getline(std::cin, limit);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                double D_limit = atof(limit.c_str());
                                std::cout << "Enter account target date in this format: dd,mm,yy: ";                
                                std::getline(std::cin, date);     
                                std::istringstream isso(date);
                                std::string newO;
                                while (std::getline(isso, newO, ',')) {
                                    
                                    newO.erase(0, newO.find_first_not_of("\t\r\n"));
                                    newO.erase(newO.find_last_not_of("\t\r\n") + 1);
                                    V_Date.push_back(newO);
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account target amount: ";
                                std::getline(std::cin, amount);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                double D_amount = atof(amount.c_str());
                                ac[accI - 1].addTargets(Target(name, D_limit, Date(V_Date[0],V_Date[1],V_Date[2]), D_amount));
                                std::cout << "This target was add" << std::endl;
                                std::cout << Target(name, D_limit, Date(V_Date[0],V_Date[1],V_Date[2]), D_amount) << std::endl;
                            }
                            case '2' : {
                                std::string name;
                                std::string amount;
                                std::vector<std::string> V_Date;
                                std::string date;
                                std::cout << "Enter account Monthly pay name: ";
                                std::getline(std::cin, name);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account Monthly pay date in this format: dd,mm,yy: ";                
                                std::getline(std::cin, date);  
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');               
                                std::istringstream isso(date);
                                std::string newO;
                                while (std::getline(isso, newO, ',')) {
                                    
                                    newO.erase(0, newO.find_first_not_of("\t\r\n"));
                                    newO.erase(newO.find_last_not_of("\t\r\n") + 1);
                                    V_Date.push_back(newO);
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account Monthly pay amount: ";
                                std::getline(std::cin, amount);    
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                             
                                double D_amount = atof(amount.c_str());
                                ac[accI - 1].addMonthlyPays(Payment(name, D_amount, Payment_type::expens, Date(V_Date[0],V_Date[1],V_Date[2])));
                                std::cout << "This Monthly pay was add" << std::endl;
                                std::cout << Payment(name, D_amount, Payment_type::expens, Date(V_Date[0],V_Date[1],V_Date[2])) << std::endl;                           
                            }
                            case '3' : {
                                std::string name;
                                std::string amount;
                                std::vector<std::string> V_Date;
                                std::string date;
                                std::cout << "Enter account Payment name: ";
                                std::getline(std::cin, name);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account Payment date in this format: dd,mm,yy: ";                
                                std::getline(std::cin, date);    
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');             
                                std::istringstream isso(date);
                                std::string newO;
                                while (std::getline(isso, newO, ',')) {
                                    
                                    newO.erase(0, newO.find_first_not_of("\t\r\n"));
                                    newO.erase(newO.find_last_not_of("\t\r\n") + 1);
                                    V_Date.push_back(newO);
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account Payment amount: ";
                                std::getline(std::cin, amount);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                                 
                                double D_amount = atof(amount.c_str());
                                ac[accI - 1].addPayment(Payment(name, D_amount, Payment_type::expens, Date(V_Date[0],V_Date[1],V_Date[2])));
                                std::cout << "This Payment was add" << std::endl;
                                std::cout << Payment(name, D_amount, Payment_type::expens, Date(V_Date[0],V_Date[1],V_Date[2])) << std::endl;
                            }
                            case '4' : {
                                std::string name;
                                std::string amount;
                                std::vector<std::string> V_Date;
                                std::string date;
                                std::cout << "Enter account Income name: ";
                                std::getline(std::cin, name);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account Income date in this format: dd,mm,yy: ";                
                                std::getline(std::cin, date);
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 
                                std::istringstream isso(date);
                                std::string newO;
                                while (std::getline(isso, newO, ',')) {
                                    
                                    newO.erase(0, newO.find_first_not_of("\t\r\n"));
                                    newO.erase(newO.find_last_not_of("\t\r\n") + 1);
                                    V_Date.push_back(newO);
                                }
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                std::cout << "Enter account Income amount: ";
                                std::getline(std::cin, amount);   
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                              
                                double D_amount = atof(amount.c_str());
                                ac[accI - 1].addMonthlyPays(Payment(name, D_amount, Payment_type::incomes, Date(V_Date[0],V_Date[1],V_Date[2])));
                                std::cout << "This Income was add" << std::endl;
                                std::cout << Payment(name, D_amount, Payment_type::incomes, Date(V_Date[0],V_Date[1],V_Date[2])) << std::endl;
                            }
                            case 'x' : {
                                break;
                            }
                            default : {
                                std::cout << "Invalid choice. Please try again.\n";
                                break;
                            }
                        }

                    } while (subChoice != 'x');
                }else{
                    std::cout << "Invalid account number: " << acc << std::endl;
                }
            }
            case '6':
                std::cout << "Exiting program.\n";
                writeToTheFile("buff.huff", ac);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '6');

    return 0;
}
