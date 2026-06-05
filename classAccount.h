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
};


class Account{
protected:
    std::string login, password;
    size_t SIZEdeposit = 0, id_new_dep = 0;
    std::vector<Variable_Deposit> deposits;
public:
    Account(std::string login, std::string password){
        this->login = login;
        this->password = password;
    }
    virtual void create_deposit() = 0;
    void show_all_deposit();
    void show_deposit(size_t &id_deposit);
    void add_for_deposit(size_t &id_deposit, double &summ);
    void delete_for_deposit(size_t &id_deposit, double &summ);
    void delete_deposit(size_t &id_deposit);
};