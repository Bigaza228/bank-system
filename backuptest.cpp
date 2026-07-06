#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
#include<memory>

struct Variable_Deposit
{
    int id;
    std::string name;
    double cash_account = 0;
    Variable_Deposit(int id, std::string name) : id(id), name(name){};
    Variable_Deposit(int id, std::string name, double cash_account) : id(id), name(name), cash_account(cash_account){};
};


class Account{
protected:
    std::string login, password;
    std::vector<Variable_Deposit> deposits;
    size_t id_new_dep = 1, status = 0;
    bool blocked = false;
public:
    Account(std::string login, std::string password) 
    : login(login), password(password){};

    Account(std::string login, std::string password, bool blocked, std::vector<Variable_Deposit> &deposits) 
    : login(std::move(login)), password(std::move(password)), blocked(std::move(blocked)) , deposits(deposits){};

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
    std::string returnDataForBackUP();
};

class VIPAccount : public Account{
public:
    VIPAccount(std::string login, std::string password) : Account(login, password){};
    VIPAccount(std::string login, std::string password, bool blocked, std::vector<Variable_Deposit> &deposits) : Account(login, password, blocked, deposits){};
    void create_deposit(std::string &name) override;
};

class DefaultAccount : public Account{
public:
    DefaultAccount(std::string login, std::string password) : Account(login, password){};
    DefaultAccount(std::string login, std::string password, bool blocked, std::vector<Variable_Deposit> &deposits) : Account(login, password, blocked, deposits){};
    void create_deposit(std::string &name) override;
};

void Account::get_info_account()
{
    std::cout << "Login: " << login << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "number of deposits: " << deposits.size() << std::endl;
    std::cout << std::endl << "Deposits: " << std::endl;
    show_all_deposit();
    std::cout << std::endl;
}

void Account::show_all_deposit()
{
    if(deposits.empty()){
        std::cout << "missing" << std::endl;
        return;
    }

    for(const auto &i : deposits){
        std::cout << "id: " << i.id << " , name: " << i.name
        << " , check: " << i.cash_account << std::endl;
    }
}

void Account::show_deposit(size_t &id_deposit)
{
    const auto it = std::find_if(deposits.begin(), deposits.end(),
    [id_deposit](Variable_Deposit i_dep){
        return i_dep.id == id_deposit;
    });

    if(it != deposits.end()){
        std::cout << "id: " << it->id << " , name: "
        << it->name
        << " , check: " << it->cash_account << std::endl;
    } else std::cout << "Id not found\n";
}

void Account::add_for_deposit(size_t &id_deposit, double &summ)
{
    auto it = std::find_if(deposits.begin(), deposits.end(),
    [id_deposit](Variable_Deposit i_dep){
        return i_dep.id == id_deposit;
    });

    if(it != deposits.end()){
        it->cash_account += summ;
    } else std::cout << "Id not found\n";
}

void Account::delete_for_deposit(size_t &id_deposit, double &summ)
{
    auto it = std::find_if(deposits.begin(), deposits.end(),
    [id_deposit](Variable_Deposit i_dep){
        return i_dep.id == id_deposit;
    });

    if(it != deposits.end()){
        if(it->cash_account >= summ){
            it->cash_account -= summ;
        } else std::cout << "Insufficient funds in the account\n";

    } else std::cout << "Id not found\n";
}

void Account::delete_deposit(size_t &id_deposit)
{
    auto it = std::find_if(deposits.begin(), deposits.end(),
    [id_deposit](Variable_Deposit i_dep){
        return i_dep.id == id_deposit;
    });

    if(it == deposits.end()){
        std::cout << "Id not found\n";
        return;
    }

    if(deposits.size() == 1 && it->cash_account > 0){
        std::cout << "You can't delete a deposit if it's the only one and there's money in it.\n";
        return;
    }

    double cash_to_transfer = it->cash_account;

    deposits.erase(it);

    if(cash_to_transfer > 0 && !deposits.empty()) {
        deposits[0].cash_account += cash_to_transfer;
        std::cout << "Remaining funds transferred to deposit ID: " << deposits[0].id << "\n";
    }
}


bool Account::checkmoney()
{
    if(deposits.empty()) return false;

    if(deposits[0].cash_account > 0){
        return true;
    } else return false;
}

bool Account::checkpassword(std::string input_password)
{
    return password == input_password;
}

bool Account::checkblocked()
{
    return blocked == true;
}

void DefaultAccount::create_deposit(std::string &name){
    if(deposits.size() < 3){
    deposits.push_back(Variable_Deposit(id_new_dep++, name));
    std::cout << "Deposit " << name << " , was successfully created\n";
    
    } else std::cout << "You have exceeded your deposit limit.\n";
}

void VIPAccount::create_deposit(std::string &name){
    deposits.push_back(Variable_Deposit(deposits.size() + 1, name));
    std::cout << "Deposit " << name << " , was successfully created\n";
}


int main(){
    std::map<std::string, std::unique_ptr<Account>> database;
    std::string text = "gty";

    database.emplace("qwerty", std::make_unique<VIPAccount>("qwerty", "22812345"));
    auto it = database.find("qwerty");
    it->second->create_deposit(text);

    std::ifstream file("databaseBackUP.txt");
    if(!file.is_open()) {
        std::cout << "ERror" << std::endl;
        return 0;
    }
    std::string status, line, login, password, bloked, SIZEdepos, deposits;
    bool resultBloked;
    size_t resultSIZEdepos;
    std::vector<Variable_Deposit> MassivDeposits;
    std::string lineDep, id, name, cash;
    int resultID;
    double resultCash;

    while(std::getline(file, line)){
        login.clear(); password.clear(); bloked.clear(); SIZEdepos.clear(); deposits.clear();
        resultBloked = false; resultBloked = 0;
        MassivDeposits.clear();

        std::stringstream ss(line);
        std::getline(ss, status, ';');
        std::getline(ss, login, ';');
        std::getline(ss, password, ';');
        std::getline(ss, bloked, ';');
        std::getline(ss, SIZEdepos, ';');
        resultBloked = std::stoi(bloked);
        resultSIZEdepos = std::stoi(SIZEdepos);
        std::getline(ss, deposits, ';');
        std::stringstream SSdepos(deposits);
        resultBloked = std::stoi(bloked);

        for(size_t i = 0; i < resultSIZEdepos; i++){
            id.clear(); name.clear(); cash.clear();
            resultID = 0; resultCash = 0.0f;
            std::getline(SSdepos, lineDep, ':');
            std::stringstream SSlineDep(lineDep);
            std::getline(SSlineDep, id, '|');
            std::getline(SSlineDep, name, '|');
            std::getline(SSlineDep, cash, '|');
            resultID = std::stoi(id);
            resultCash = std::stod(cash);
            MassivDeposits.push_back(Variable_Deposit(resultID, name, resultCash));
        }
        if(status == "1"){
            database.emplace(login, std::make_unique<VIPAccount>(login, password, resultBloked, MassivDeposits));
        } else {
            database.emplace(login, std::make_unique<DefaultAccount>(login, password, resultBloked, MassivDeposits));
        }
    }

    std::cout << "" << std::endl;
    for(auto &i : database){
        std::cout << std::endl << "______________________________\n";
        i.second->get_info_account();
        std::cout << i.second->returnDataForBackUP() << std::endl;
        std::cout << "______________________________\n";
    }


    std::ofstream file2("databaseBackUP.txt", std::ios::out);
    if(!file.is_open()){
        std::cout << "Error\n";
        return 0;
    }
    for(auto &i : database){
        file2 << i.second->returnDataForBackUP() << std::endl;
    }

    file.close();
    file2.close();

    return 0;
}


std::string Account::returnDataForBackUP()
{
    std::string resulttext;
    resulttext += std::to_string(status);
    resulttext.push_back(';');
    resulttext += login;
    resulttext.push_back(';');
    resulttext += password;
    resulttext.push_back(';'); 
    resulttext += std::to_string(blocked);
    resulttext.push_back(';'); 
    resulttext += std::to_string(deposits.size());
    resulttext.push_back(';');
    if(deposits.size() > 0){
        for(const auto &i : deposits){
            resulttext += std::to_string(i.id);
            resulttext.push_back('|');
            resulttext += i.name;
            resulttext.push_back('|');
            resulttext += std::to_string(i.cash_account);
            resulttext.push_back('|');
            resulttext.push_back(':');
        }
    }
    resulttext.push_back(';');
    return resulttext;
}

/*
    database.emplace("negr", std::make_unique<DefaultAccount>("negr", "1234545"));
    database.emplace("penes", std::make_unique<VIPAccount>("penes", "1234545"));
    database.emplace("nefr", std::make_unique<DefaultAccount>("nefr", "1234545"));
    auto it = database.find("negr");
    std::string name = "qwe";
    it->second->create_deposit(name);
    name = "asd";
    it->second->create_deposit(name);

    it = database.find("penes");
    name = "qwe";
    it->second->create_deposit(name);
    name = "asd";
    it->second->create_deposit(name);
    name = "zxc";
    it->second->create_deposit(name);
    name = "rty";
    it->second->create_deposit(name);
    name = "fgh";
    it->second->create_deposit(name);
    name = "vbn";
    it->second->create_deposit(name);

*/

/*

    std::ofstream file("databaseBackUP.txt", std::ios::out);
    if(!file.is_open()){
        std::cout << "Error\n";
        return 0;
    }
    for(auto &i : database){
        file << i.second->returnDataForBackUP() << std::endl;
    }
*/