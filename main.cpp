#include "crow.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "lib.h"
#include "Huff.h"
#include <winrt/base.h>
#include <crow/mustache.h>
#include <chrono>
#include <format>
#include <thread>


int main() {

    std::vector<Account> ac;

    loadFromFile("yes.huff", ac);

    crow::SimpleApp app;

    CROW_ROUTE(app, "/").methods("GET"_method)(
        [&](){
            int p;
            std::string result;
            for(auto& n : ac){
                p = n.getAccountNumber();
                result += std::to_string(p) + '\n';
            }
            
            return result;
        }
    );

    CROW_ROUTE(app, "/account")
    .methods("GET"_method)
    ([&](const crow::request& req) {
        if (req.url_params.get("cislo") != nullptr) {
            
            std::ostringstream oss;
            std::string result;
            std::string accountNumberStr = req.url_params.get("cislo");

            int accountNumber = std::stoi(accountNumberStr);            
            int p;
            for(auto& n : ac){
                p = n.getAccountNumber();
                if(p == accountNumber){

                    oss << p << std::endl;
                    oss << n.getOwner() << std::endl;
                    oss << n.getDateOfAssebly() << std::endl;
                    oss << n.getBalance() << std::endl;

                    if(req.url_params.get("Par") != nullptr){
                        oss << "Part Owners: " << std::endl; 
                        for(auto& p : n.getPartOwners())
                        {
                            oss << p << std::endl;
                        }                
                    }if(req.url_params.get("Tar") != nullptr){
                        oss << "Targets: " << std::endl; 
                        for(auto& p : n.getTargets())
                        {
                            oss << p << std::endl;
                        }   

                    }if(req.url_params.get("Mon") != nullptr){
                        oss << "Monthly pays: " << std::endl; 
                        for(auto& p : n.getMontlyPays())
                        {
                            oss << p << std::endl;
                        }   

                    }if(req.url_params.get("Pay") != nullptr){
                        oss << "Payments: " << std::endl; 
                        for(auto& p : n.getPayments())
                        {
                            oss << p << std::endl;
                        }   

                    }if(req.url_params.get("Inc") != nullptr){
                        oss << "Incomes: " << std::endl; 
                        for(auto& p : n.getIncomes())
                        {
                            oss << p << std::endl;
                        } 
                    }if(req.url_params.get("Sta") != nullptr){
                        oss << n.generateSpendingHabitsReportJson() << std::endl;
                    }
                    result = oss.str();                    
                }
            }
            return result;            
        } else {
            std::string result ="Chybejici query parameter 'cislo'";
            return result;
        }
    });



    CROW_ROUTE(app, "/account")
    .methods("POST"_method)
    ([&](const crow::request& req) {
        try {
            int AccN = 0;
            // Zpracování dat z těla požadavku
            auto json = crow::json::load(req.body);
            if (!json) {
                // Chyba při parsování JSON dat
                return crow::response(400, "Invalid JSON data");
            }
            if(req.url_params.get("cislo") == "new"){
                int AccNum = json["accNum"].d();
                std::string ownerName = json["ownerName"].s();
                std::string ownerAddress = json["ownerAddress"].s();
                std::string ownerPhoneNumber = json["ownerPhoneNumber"].s();
                double initialBalance = json["initialBalance"].d();
                std::string accday =json["AccDay"].s();
                std::string accmonth=json["AccMonth"].s();
                std::string accyear=json["AccYear"].s();
                Account account(AccNum,Date(accday,accmonth,accyear),Owner(ownerName, ownerAddress, ownerPhoneNumber),initialBalance);
                
                AccN = AccNum;
            }
            if(req.url_params.get("Par") || req.url_params.get("Tar") ||req.url_params.get("Mon") ||req.url_params.get("Pay")||req.url_params.get("Inc")){
                if(AccN == 0){
                    std::string accountNumberStr = req.url_params.get("cislo");
                    AccN = std::stoi(accountNumberStr);
                }

                int p;
                for(auto& n : ac){
                    p = n.getAccountNumber();
                    if(p == AccN){
                        if(req.url_params.get("Par") != nullptr){
                            std::string ParName = json["ParName"].s();
                            std::string ParAddress = json["ParAddress"].s();
                            std::string ParPhoneNumber = json["ParPhoneNumber"].s();
                            n.addPartOwner(Owner(ParName, ParAddress, ParPhoneNumber));
                        }
                        if(req.url_params.get("Tar") != nullptr){
                            std::string TarName =json["TarName"].s();
                            std::string Tarday =json["TarDay"].s();
                            std::string Tarmonth=json["TarMonth"].s();
                            std::string Taryear=json["TarYear"].s();
                            double Tarlim = json["TarLim"].d();
                            n.addTargets(Target(TarName, Tarlim, Date(Tarday,Tarmonth,Taryear), 0));
                        }
                        if(req.url_params.get("Mon") != nullptr){
                            std::string MonName =json["MonName"].s();
                            std::string Monday =json["MonDay"].s();
                            std::string Monmonth=json["MonMonth"].s();
                            std::string Monyear=json["MonYear"].s();
                            double MonAmnt = json["MonAmnt"].d();
                            n.addMonthlyPays(Payment(MonName, MonAmnt, Payment_type::expens, Date(Monday, Monmonth, Monyear)));
                        }
                        if(req.url_params.get("Pay") != nullptr){
                            std::string PayName =json["PayName"].s();
                            std::string Payday =json["PayDay"].s();
                            std::string Paymonth=json["PayMonth"].s();
                            std::string Payyear=json["PayYear"].s();
                            double PayAmnt = json["PayAmnt"].d();
                            n.addPayment(Payment(PayName, PayAmnt, Payment_type::expens, Date(Payday, Paymonth, Payyear)));
                        }
                        if(req.url_params.get("Inc") != nullptr){
                            std::string IncName =json["IncName"].s();
                            std::string Incday =json["IncDay"].s();
                            std::string Incmonth=json["IncMonth"].s();
                            std::string Incyear=json["IncYear"].s();
                            double IncAmnt = json["IncAmnt"].d();
                            n.addFunds(Payment(IncName, IncAmnt, Payment_type::incomes, Date(Incday, Incmonth, Incyear)));
                        }
                    }
                }
            } 
            return crow::response(201, "Vytvoreno");
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });



    CROW_ROUTE(app, "/account").methods("PUT"_method)
    ([&](const crow::request& req) {
        if (req.url_params.get("cislo") != nullptr) {

            std::string accountNumberStr = req.url_params.get("cislo");
            auto json = crow::json::load(req.body);

            if (!json) {
                return crow::response(400, "Invalid JSON data");
            }

            int accountNumber = std::stoi(accountNumberStr);            
            int p;
            for(auto& n : ac){
                p = n.getAccountNumber();
                if(p == accountNumber){
                    if(req.url_params.get("Own") != nullptr){
                        if(json.has("ownerName")){
                            n.setOwnerName(json["ownerName"].s());               
                        }
                        if(json.has("ownerAddress")){
                             n.setOwnerAdress(json["ownerAddress"].s());
                        }
                        if(json.has("ownerPhoneNumber")){
                             n.setOwnerPhone(json["ownerPhoneNumber"].s());
                        }
                    }
                    if(req.url_params.get("Par") != nullptr){
                        
                        std::string nameP = req.url_params.get("Par");

                        for(auto& p : n.getPartOwners())
                        {
                            if(p.getName() == nameP){
                                if(json.has("PaOwnerName")){
                                    p.setName(json["PaOwnerName"].s());               
                                }
                                if(json.has("PaOwnerAddress")){
                                    p.setAddress(json["PaOwnerAddress"].s());
                                }
                                if(json.has("PaOwnerPhoneNumber")){
                                    p.setPhoneNumber(json["PaOwnerPhoneNumber"].s());
                                }
                            }
                        }                
                    }
                    if(req.url_params.get("Tar") != nullptr){

                        std::string nameT = req.url_params.get("Tar");

                        for(auto& p : n.getTargets())
                        {
                            if(p.getName() == nameT){
                                if(json.has("addFunds")){
                                    p.addAmount(json["addFunds"].d());
                                }
                                if(json.has("TargetName")){
                                    p.setTargetName(json["TargetName"].s());               
                                }
                                if(json.has("TargetLimit")){
                                    p.setTagetLimit(json["TargetLimit"].d());
                                }
                                if(json.has("TagetDate")){
                                    std::string day =json["TargetDay"].s();
                                    std::string month=json["TargetMonth"].s();
                                    std::string year=json["TargetYear"].s();
                                    p.setTargetDate(Date(day,month,year));
                                }
                                if(json.has("TargetAmnt")){
                                    p.setTargetAmount(json["TargetAmnt"].d());
                                }
                            }                            
                        }   
                    }
                    if(req.url_params.get("Mon") != nullptr){

                       std::string nameM = req.url_params.get("Mon");

                        for(auto& p : n.getMontlyPays())
                        {
                           if(p.getName() == nameM){

                                if(json.has("MonthlyName")){
                                    p.setName(json["MonthlyName"].s());               
                                }
                                if(json.has("MonthlyAmnt")){
                                    p.setAmnt(json["MonthlyAmnt"].d());
                                }
                                if(json.has("MonthlyDate")){
                                    std::string day =json["MonthlyDay"].s();
                                    std::string month=json["MonthlyMonth"].s();
                                    std::string year=json["MonthlyYear"].s();
                                    p.setDate(Date(day,month,year));
                                }
                           }
                        }   

                    }
                    if(req.url_params.get("Pay") != nullptr){
                       
                        std::string nameP = req.url_params.get("Pay");

                        for(auto& p : n.getMontlyPays())
                        {
                           if(p.getName() == nameP){

                                if(json.has("PayName")){
                                    p.setName(json["PayName"].s());               
                                }
                                if(json.has("PayAmnt")){
                                    p.setAmnt(json["PayAmnt"].d());
                                }
                                if(json.has("PayDate")){
                                    std::string day =json["PayDay"].s();
                                    std::string month=json["PayMonth"].s();
                                    std::string year=json["PayYear"].s();
                                    p.setDate(Date(day,month,year));
                                }
                           }
                        }   

                    }
                    if(req.url_params.get("Inc") != nullptr){
                        
                        std::string nameI = req.url_params.get("Inc");

                        for(auto& p : n.getMontlyPays())
                        {
                           if(p.getName() == nameI){

                                if(json.has("IncomName")){
                                    p.setName(json["IncomName"].s());               
                                }
                                if(json.has("IncomAmnt")){
                                    p.setAmnt(json["IncomAmnt"].d());
                                }
                                if(json.has("IncomDate")){
                                    std::string day =json["IncomDay"].s();
                                    std::string month=json["IncomMonth"].s();
                                    std::string year=json["IncomYear"].s();
                                    p.setDate(Date(day,month,year));
                                }
                           }
                        }   
                    }
                                  
                }
            }
            //return "PUT Done";          
        }
        //return "PUT Nope"; 
    });

    CROW_ROUTE(app, "/account")
    .methods("DELETE"_method)
    ([&](const crow::request& req) {        
        if(req.url_params.get("cislo") != nullptr &&(req.url_params.get("Tar") != nullptr || req.url_params.get("Par") != nullptr)){
            
            std::string accountNumberStr = req.url_params.get("cislo");
            int num = std::stoi(accountNumberStr);

            for(auto& i: ac){
                if(i.getAccountNumber() == num){
                    if(req.url_params.get("Tar") != nullptr){
                        std::string TarNam = req.url_params.get("Tar");
                        i.removeTarget(TarNam);
                    }
                    if(req.url_params.get("Par") != nullptr){
                        std::string ParNam = req.url_params.get("Par");
                        i.removeTarget(ParNam);
                    }
                }
            }
        }
        if(req.url_params.get("cislo") != nullptr){

            std::string accountNumberStr = req.url_params.get("cislo");
            int num = std::stoi(accountNumberStr);

            for(auto& i: ac){
                if(i.getAccountNumber() == num){
                    ac.pop_back();
                }
            }
        }
        else{
            return "nope";
        }
        return "Delete done";
    });

    
    // Spustíme Crow server
    app.bindaddr("127.0.0.1").port(18080).run();
    return 0;
}
