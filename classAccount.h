#pragma once 
#include<iostream>
#include<sstream>
#include<fstream>
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
    bool blocked = false;
public:
    Account(std::string login, std::string password) 
    : login(login), password(password){};

    virtual ~Account() = default;
    virtual void create_deposit(std::string &name) = 0;
    
    void get_info_account();
    void show_all_deposit();
    void show_deposit(size_t &id_deposit);
    void add_for_deposit(size_t &id_deposit, double &summ);
    void delete_for_deposit(size_t &id_deposit, double &summ);
    void delete_deposit(size_t &id_deposit);
    bool checkmoney();
    bool checkpassword(std::string input_password);
    bool checkblocked();
    bool& blockptr(){return blocked;}
};

class VIPAccount : public Account{
public:
    VIPAccount(std::string login, std::string password) : Account(login, password){};
    void create_deposit(std::string &name) override;
};

class DefaultAccount : public Account{
public:
    DefaultAccount(std::string login, std::string password) : Account(login, password){};
    void create_deposit(std::string &name) override;
};