#include <iostream>
#include <fstream>
#include "lib.h"
#include "Huff.h"

int main() {

        // Vytvoření vlastníka účtu
        Owner owner1("John Doe", "123 Main Street", "+1234567890");
        Owner owner2("Jane Smith", "456 Oak Avenue", "+1987654321");

        // Vytvoření účtu 1
        Date assemblyDate1("01", "01", "2022");
        Account account1(1001, assemblyDate1, owner1, 700);

        // Vytvoření účtu 2
        Date assemblyDate2("01", "01", "2022");
        Account account2(1002, assemblyDate2, owner2, 800);

        // Přidání cílů účtu 1
        Date targetDate1_1("01", "01", "2025");
        Target target1_1("Retirement Fund", 10000, targetDate1_1, 800);
        account1.addTargets(target1_1);

        Date targetDate1_2("01", "01", "2027");
        Target target1_2("House Down Payment", 20000, targetDate1_2, 1200);
        account1.addTargets(target1_2);

        Date targetDate1_3("01", "01", "2030");
        Target target1_3("Children Education", 15000, targetDate1_3, 1000);
        account1.addTargets(target1_3);

        Date targetDate1_4("01", "01", "2032");
        Target target1_4("Emergency Fund", 5000, targetDate1_4, 500);
        account1.addTargets(target1_4);

        Date targetDate1_5("01", "01", "2035");
        Target target1_5("Dream Vacation", 8000, targetDate1_5, 700);
        account1.addTargets(target1_5);

        // Přidání cílů účtu 2
        Date targetDate2_1("01", "01", "2030");
        Target target2_1("Travel Fund", 5000, targetDate2_1, 1000);
        account2.addTargets(target2_1);

        Date targetDate2_2("01", "01", "2033");
        Target target2_2("New Car", 25000, targetDate2_2, 1500);
        account2.addTargets(target2_2);

        Date targetDate2_3("01", "01", "2035");
        Target target2_3("Home Renovation", 30000, targetDate2_3, 2000);
        account2.addTargets(target2_3);

        Date targetDate2_4("01", "01", "2037");
        Target target2_4("Early Retirement", 200000, targetDate2_4, 2500);
        account2.addTargets(target2_4);

        Date targetDate2_5("01", "01", "2040");
        Target target2_5("Education Fund", 50000, targetDate2_5, 1800);
        account2.addTargets(target2_5);

        // Přidání měsíčního příspěvku k cílům účtu 1
        Payment monthlyContribution1_1("Retirement Fund", 500, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_1);

        Payment monthlyContribution1_2("House Down Payment", 600, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_2);

        Payment monthlyContribution1_3("Children Education", 300, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_3);

        Payment monthlyContribution1_4("Emergency Fund", 200, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_4);

        Payment monthlyContribution1_5("Dream Vacation", 400, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_5);

        Payment monthlyContribution1_6("Additional Savings", 100, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_6);

        Payment monthlyContribution1_7("Entertainment Budget", 150, Payment_type::expens, Date("01", "01", "2024"));
        account1.addMonthlyPays(monthlyContribution1_7);

        // Přidání měsíčního příspěvku k cílům účtu 2
        Payment monthlyContribution2_1("Travel Fund", 200, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_1);

        Payment monthlyContribution2_2("New Car", 300, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_2);

        Payment monthlyContribution2_3("Home Renovation", 500, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_3);

        Payment monthlyContribution2_4("Early Retirement", 800, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_4);

        Payment monthlyContribution2_5("Education Fund", 400, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_5);

        Payment monthlyContribution2_6("Investment Portfolio", 700, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_6);

        Payment monthlyContribution2_7("Emergency Fund", 150, Payment_type::expens, Date("01", "01", "2024"));
        account2.addMonthlyPays(monthlyContribution2_7);

        // Přidání příjmu na účet 1
        Payment income1_1("Salary", 2000, Payment_type::incomes, Date("15", "04", "2024"));
        account1.addFunds(income1_1);

        Payment income1_2("Bonus", 1000, Payment_type::incomes, Date("20", "05", "2024"));
        account1.addFunds(income1_2);

        Payment income1_3("Investment Dividends", 300, Payment_type::incomes, Date("25", "06", "2024"));
        account1.addFunds(income1_3);

        Payment income1_4("Side Gig Earnings", 500, Payment_type::incomes, Date("15", "07", "2024"));
        account1.addFunds(income1_4);

        Payment income1_5("Rent Income", 1000, Payment_type::incomes, Date("01", "08", "2024"));
        account1.addFunds(income1_5);

        Payment income1_6("Tax Refund", 200, Payment_type::incomes, Date("05", "09", "2024"));
        account1.addFunds(income1_6);

        Payment income1_7("Gift Money", 300, Payment_type::incomes, Date("10", "10", "2024"));
        account1.addFunds(income1_7);

        // Přidání příjmu na účet 2
        Payment income2_1("Freelance Income", 1500, Payment_type::incomes, Date("20", "04", "2024"));
        account2.addFunds(income2_1);

        Payment income2_2("Investment Returns", 700, Payment_type::incomes, Date("25", "05", "2024"));
        account2.addFunds(income2_2);

        Payment income2_3("Rental Income", 800, Payment_type::incomes, Date("30", "06", "2024"));
        account2.addFunds(income2_3);

        Payment income2_4("Business Profits", 1200, Payment_type::incomes, Date("15", "07", "2024"));
        account2.addFunds(income2_4);

        Payment income2_5("Lottery Winnings", 500, Payment_type::incomes, Date("01", "08", "2024"));
        account2.addFunds(income2_5);

        Payment income2_6("Birthday Gift", 100, Payment_type::incomes, Date("05", "09", "2024"));
        account2.addFunds(income2_6);

        Payment income2_7("Interest Earned", 200, Payment_type::incomes, Date("10", "10", "2024"));
        account2.addFunds(income2_7);

        // Přidání výdaje z účtu 1
        Payment expense1_1("Rent", 800, Payment_type::expens, Date("01", "04", "2024"));
        account1.addPayment(expense1_1);

        Payment expense1_2("Utilities", 150, Payment_type::expens, Date("05", "04", "2024"));
        account1.addPayment(expense1_2);

        Payment expense1_3("Groceries", 300, Payment_type::expens, Date("10", "04", "2024"));
        account1.addPayment(expense1_3);

        Payment expense1_4("Dining Out", 200, Payment_type::expens, Date("15", "04", "2024"));
        account1.addPayment(expense1_4);

        Payment expense1_5("Entertainment", 100, Payment_type::expens, Date("20", "04", "2024"));
        account1.addPayment(expense1_5);

        Payment expense1_6("Transportation", 200, Payment_type::expens, Date("25", "04", "2024"));
        account1.addPayment(expense1_6);

        Payment expense1_7("Clothing", 150, Payment_type::expens, Date("30", "04", "2024"));
        account1.addPayment(expense1_7);

        // Přidání výdaje z účtu 2
        Payment expense2_1("Utilities", 200, Payment_type::expens, Date("10", "04", "2024"));
        account2.addPayment(expense2_1);

        Payment expense2_2("Groceries", 300, Payment_type::expens, Date("15", "04", "2024"));
        account2.addPayment(expense2_2);

        Payment expense2_3("Dining Out", 150, Payment_type::expens, Date("20", "04", "2024"));
        account2.addPayment(expense2_3);

        Payment expense2_4("Entertainment", 100, Payment_type::expens, Date("25", "04", "2024"));
        account2.addPayment(expense2_4);

        Payment expense2_5("Transportation", 250, Payment_type::expens, Date("30", "04", "2024"));
        account2.addPayment(expense2_5);

        Payment expense2_6("Clothing", 200, Payment_type::expens, Date("05", "05", "2024"));
        account2.addPayment(expense2_6);

        Payment expense2_7("Healthcare", 100, Payment_type::expens, Date("10", "05", "2024"));
        account2.addPayment(expense2_7);

        // Zápis informací o účtech do souboru
        std::vector<Account> acounts;
        acounts.push_back(account1);
        acounts.push_back(account2);
        account1.prettyPrintAccount();
        account2.prettyPrintAccount();

        // Zápis pokroku směrem k finančním cílům do souboru
        // Zobrazí seznam cílů a jejich aktuální stav
        // Zápis počtu zbývajících měsíců k dosažení cíle do souboru
        // Zápis počtu zbývajících měsíců k dosažení cíle do souboru
        std::vector<std::pair<std::string, std::pair<int, bool>>> monthsAccoutn1;
        std::vector<std::pair<std::string, std::pair<int, bool>>> monthsAccoutn2;
        account1.monthsToTarget(monthsAccoutn1,"Retirement Fund");
        account1.monthsToTarget(monthsAccoutn1,"House Down Payment");
        account1.monthsToTarget(monthsAccoutn1,"Children Education");
        account1.monthsToTarget(monthsAccoutn1,"Emergency Fund");
        account1.monthsToTarget(monthsAccoutn1,"Dream Vacation");

        account2.monthsToTarget(monthsAccoutn2,"Travel Fund");
        account2.monthsToTarget(monthsAccoutn2,"New Car");
        account2.monthsToTarget(monthsAccoutn2,"Home Renovation");
        account2.monthsToTarget(monthsAccoutn2,"Early Retirement");
        account2.monthsToTarget(monthsAccoutn2,"Education Fund");

        // Výpis počtu zbývajících měsíců do dosažení cíle
        std::cout << "Months remaining to reach targets for account 1:" << std::endl;
        for(const auto& target : monthsAccoutn1) {
            std::cout << target.first << ": " << target.second.first << " months, " << (target.second.second ? "Target reached" : "Target not reached") << " in time."<< std::endl;
        }
        std::cout << std::endl;
        std::cout << "Months remaining to reach targets for account 2:" << std::endl;
        for(const auto& target : monthsAccoutn2) {
            std::cout << target.first << ": " << target.second.first << " months, " << (target.second.second ? "Target reached" : "Target not reached") << " in time." << std::endl;
        }
        std::cout << std::endl;

        // Generování zprávy o platebních návycích pro účet 1 a 2
        
        std::cout << account1.generateSpendingHabitsReportJson() << std::endl;
        std::cout << account2.generateSpendingHabitsReportJson() << std::endl;

        writeToTheFile("buff.huff", acounts);

    return 0;
}
