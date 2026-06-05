#pragma once
#include "classAccount.h"
#include<map>
#include<memory>



class ControllCenter{
private:
    std::map<std::string, std::unique_ptr<Account>> accountDatabase;
    std::map<std::string, std::unique_ptr<Account>> newaccountDatabase;
    bool deleted = false;
    

public:
    ControllCenter();
    ~ControllCenter();
    void addAccount(const std::string &login, const std::string &password, const std::string &status);
    void deleteAccount(const std::string &login, const std::string &password);
    void showAccounts(); //for admin
    void loginAccount(const std::string &login, const std::string &password);
    void interfaceprogram(auto &it_account);
    void adminmenu();    //for admin
};

