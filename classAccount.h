#pragma once 
#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<vector>

struct Variable_Deposit
{
    int id;
    std::string name;
    double cash_account = 0;
    Variable_Deposit(int id, std::string name) : id(id), name(name){};
};


class Account{
protected:
    std::string login, password;
    size_t SIZEdeposit = 0, id_new_dep = 1;
    std::vector<Variable_Deposit> deposits;
public:
    Account(std::string login, std::string password) 
    : login(login), password(password){};

    virtual ~Account() = default;
    virtual void create_deposit() = 0;
    
    void show_all_deposit();
    void show_deposit(size_t &id_deposit);
    void add_for_deposit(size_t &id_deposit, double &summ);
    void delete_for_deposit(size_t &id_deposit, double &summ);
    void delete_deposit(size_t &id_deposit);
};

class VIPAccount : public Account{
public:
    VIPAccount(std::string login, std::string password) : Account(login, password){};
    void create_deposit(std::string &name){
        deposits.push_back(Variable_Deposit(id_new_dep, name));
        ++id_new_dep, ++SIZEdeposit;
        std::cout << "Deposit " << name << " , was successfully created\n";
    }
};

class DefaultAccount : public Account{
public:
    DefaultAccount(std::string login, std::string password) : Account(login, password){};
    void create_deposit(std::string &name){
        if(SIZEdeposit <= 3){
        deposits.push_back(Variable_Deposit(id_new_dep, name));
        ++id_new_dep, ++SIZEdeposit;
        std::cout << "Deposit " << name << " , was successfully created\n";
        
        } else std::cout << "You have exceeded your deposit limit.\n";
    }
};