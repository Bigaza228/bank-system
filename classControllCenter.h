#pragma once
#include "classAccount.h"
#include<map>
#include<memory>



class ControllCenter{
private:
    std::map<std::string, std::unique_ptr<Account>> accountDatabase;
    std::map<std::string, std::unique_ptr<Account>> newaccountDatabase;
    bool deleted = false;
    
    class interfaceprogram{
    private:
        
        
    public:
        
    };
public:
    ControllCenter();
    ~ControllCenter();
    void addAccount();
    void deleteAccount();
    void showAccounts(); //for admin
    void loginAccount();
    void adminmenu();    
};

VIPAccount gay("qwe","123");