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
    bool show_id_deposits();
    std::string& getlogin(){return login;}
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

void Account::get_info_account()
{
    std::cout << "Login: " << login << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "number of deposits: " << SIZEdeposit << std::endl;
    std::cout << std::endl << "Deposits: " << std::endl;
    show_all_deposit();
    std::cout << std::endl;
}

void Account::show_all_deposit()
{
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
    if(SIZEdeposit > 0) --SIZEdeposit;

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
    if(SIZEdeposit < 3){
    deposits.push_back(Variable_Deposit(id_new_dep, name));
    ++id_new_dep, ++SIZEdeposit;
    std::cout << "Deposit " << name << " , was successfully created\n";
    
    } else std::cout << "You have exceeded your deposit limit.\n";
}

void VIPAccount::create_deposit(std::string &name){
    deposits.push_back(Variable_Deposit(id_new_dep, name));
    ++id_new_dep, ++SIZEdeposit;
    std::cout << "Deposit " << name << " , was successfully created\n";
}


#include<map>
#include<memory>
#include<cstdlib>

void clearinterface(){
#if defined(__APPLE__) || defined(__linux__)
    std::system("clear");
#elif defined(_WIN32)
    std::system("cls");
#endif
}

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
    void interfaceprogram(std::unique_ptr<Account> &it_account);
    void adminmenu();    //for admin
    void moneytransfer(std::unique_ptr<Account> &it_account1, std::unique_ptr<Account> &it_account2);
};




ControllCenter::ControllCenter()
{
}

ControllCenter::~ControllCenter()
{
}

void ControllCenter::addAccount(const std::string &login, const std::string &password, const std::string &status)
{
    auto it = accountDatabase.find(login);
    if(it == accountDatabase.end()){
        if(status == "vip"){
            accountDatabase.emplace(login, std::make_unique<VIPAccount>(login, password));
        } else {
            accountDatabase.emplace(login, std::make_unique<DefaultAccount>(login, password));
        }
        std::cout << "Account successfully created.\n";
    } else {
        std::cout << "That username is already taken.\n";
    }
}

void ControllCenter::deleteAccount(const std::string &login, const std::string &password)
{
    auto itforDBALL = accountDatabase.find(login);

    if(itforDBALL != accountDatabase.end()){
        // Проверяем пароль перед удалением, чтобы чужой человек не удалил аккаунт
        if(!itforDBALL->second->checkpassword(password)) {
            std::cout << "Incorrect password for deletion.\n";
            return;
        }

        if(itforDBALL->second->checkmoney()){
            std::cout << "The account cannot be deleted because it holds funds.\n";
        } else {
            accountDatabase.erase(itforDBALL);
            std::cout << "Account successfully deleted.\n";
        }
    } else {
        std::cout << "That account does not exist.\n";
    }
}


void ControllCenter::showAccounts()
{
    for(const auto &it : accountDatabase){
        it.second->get_info_account();
    }
}

void ControllCenter::loginAccount(const std::string &login, const std::string &password)
{
    auto itforDBALL = accountDatabase.find(login);
    if(itforDBALL != accountDatabase.cend()){
        if(itforDBALL->second->checkpassword(password)){
            if(itforDBALL->second->checkblocked()){
                std::cout << "Your account has been blocked; you cannot access it.\n";
                return;
            }
            std::cout << "You have successfully logged into your account.\n";
            return interfaceprogram(itforDBALL->second);
        } else {
            std::cout << "The password is incorrect.\n";
        }
    } else {
        std::cout << "login not found\n";
    }
}

void ControllCenter::interfaceprogram(std::unique_ptr<Account> &it_account)
{
    std::string request, arg1,arg2,arg3;
    while (true)
    {
        request.clear();
        arg1.clear();
        arg2.clear();
        arg3.clear();
        std::cout << std::endl;
        std::cout << "1. View account information\n";
        std::cout << "2. Show all deposits\n";
        std::cout << "3. View specific deposit: Enter 3 \"id_deposit\"\n";
        std::cout << "4. Create new deposit: Enter 4 \"name\"\n";
        std::cout << "5. Add money to deposit: Enter 5 \"id_deposit\" \"summa\"\n";
        std::cout << "6. Withdraw money from deposit: Enter 6 \"id_deposit\" \"summa\"\n";
        std::cout << "7. Delete deposit: Enter 7 \"id_deposit\"\n";
        std::cout << "8. Transfer money to another account: Enter 8 \"login_account1\" \"login_account2\"\n";
        std::cout << "0. Logout\n";
        std::cout << "\n==========================================\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, request);
        std::stringstream ss(request);
        ss >> arg1 >> arg2 >> arg3;

        if(arg1 == "1"){
            it_account->get_info_account();
        } else if(arg1 == "2"){
            it_account->show_all_deposit();
        } else if(arg1 == "3" && !arg2.empty()){
            try{
                size_t id_dep = std::stoi(arg2);
                it_account->show_deposit(id_dep);
            } catch(...){
                std::cout << "It didn't work; please enter it again.\n";
            }
        } else if(arg1 == "4" && !arg2.empty()){
            it_account->create_deposit(arg2);
        } else if(arg1 == "5" && !arg2.empty() && !arg3.empty()){
            try{
                size_t id_dep = std::stoi(arg2);
                double summ = std::stod(arg3);
                it_account->add_for_deposit(id_dep, summ);
            } catch(...){
                std::cout << "It didn't work; please enter it again.\n";
            }
        } else if(arg1 == "6" && !arg2.empty() && !arg3.empty()){
            try{
                size_t id_dep = std::stoi(arg2);
                double summ = std::stod(arg3);
                it_account->delete_for_deposit(id_dep, summ);
            } catch(...){
                std::cout << "It didn't work; please enter it again.\n";
            }
        } else if(arg1 == "7" && !arg2.empty()){
            try{
                size_t id_dep = std::stoi(arg2);
                it_account->delete_deposit(id_dep);
            } catch(...){
                std::cout << "It didn't work; please enter it again.\n";
            }
        } else if(arg1 == "8" && !arg2.empty() && !arg3.empty()){
            if(arg2 == it_account->getlogin()){
                auto it_account2 = accountDatabase.find(arg3);
                if(it_account2 != accountDatabase.cend()){
                    ControllCenter::moneytransfer(it_account, it_account2->second);
                } else {
                    std::cout << "login account 2 not found\n";
                }
            }
        } else if(arg1 == "0"){
            std::cout << "You have logged out of your account.\n";
            return;
        }
    }
}

void ControllCenter::adminmenu()
{
    std::string request, arg1,arg2;
    while (true)
    {
        request.clear();
        arg1.clear();
        arg2.clear();
        std::cout << "1. to withdraw all users\n";
        std::cout << "2. login in account: Enter 2 \"login\"\n";
        std::cout << "3. block account: Enter 3 \"login\"\n";
        std::cout << "4. logout\n";

        std::getline(std::cin, request);
        std::stringstream ss(request);
        ss >> arg1 >> arg2;

        if(arg1 == "1"){
            showAccounts();
        } else if(arg1 == "2" && !arg2.empty()){
            auto it = accountDatabase.find(arg2);
            if(it != accountDatabase.end()){
                std::cout << "You have successfully logged into your account - " << arg2 << std::endl;
                return interfaceprogram(it->second);
            } else {
                std::cout << "Account not found\n";
            }
        } else if(arg1 == "3" && !arg2.empty()){
            auto it = accountDatabase.find(arg2);
            if(it != accountDatabase.end()){
                it->second->blockptr() = true;
                std::cout << "Account - " << arg2 << " , has blocked\n";
            } else {
                std::cout << "Account not found\n";
            }
        } else if(arg1 == "4"){
            std::cout << "Admin menu closed.\n";
            return;
        }
    }
}

bool checkLogOrPas(std::string &arg){
    for(size_t i = 0; i < arg.size(); ++i){
        if(i > 7) return false;
        if(arg[i] == ' ' || std::tolower(arg[i]) < 'a' || std::tolower(arg[i]) > 'z'){
            return false;
        }
    }
    return true;
}


int main(){


    std::string request, arg1,arg2,arg3;
    ControllCenter controllbase;

    while (true)
    {
        request.clear();
        arg1.clear();
        arg2.clear();
        arg3.clear();


        std::cout << "Enter your choice: ";
        std::getline(std::cin, request);
        std::stringstream ss(request);
        ss >> arg1 >> arg2 >> arg3;

        if((arg1 == "1" || arg1 == "1vip") && !arg2.empty() && !arg3.empty()){
            if(!checkLogOrPas(arg2) && !checkLogOrPas(arg3)){
                std::cout << "Your username or password does not meet the standards.\n";
                std::cout << "use up to 8 characters inclusive, and do not use characters\n";
                std::cout << "Try again.\n";
                continue;
            }
            if(arg1 == "1vip"){
                controllbase.addAccount(arg2, arg3, "vip");
            } else {
                controllbase.addAccount(arg2, arg3, "def");
            }

        } else if(arg1 == "2" && !arg2.empty() && !arg3.empty()){
            controllbase.deleteAccount(arg2, arg3);

        } else if(arg1 == "3" && !arg2.empty() && !arg3.empty()){
            controllbase.loginAccount(arg2, arg3);

        } else if(arg1 == "admin" && arg2 == "admin"){
            std::cout << "start admin menu:\n";
            controllbase.adminmenu();

        } else if(arg1 == "0"){
            std::cout << "Good bay!\n";
            return 0;
        }
    }
    return 0;
}

void ControllCenter::moneytransfer(std::unique_ptr<Account> &it_account1, std::unique_ptr<Account> &it_account2)
{
    if(!it_account1->checkmoney()){
        std::cout << "you have no deposits\n";
        return;
    }
    if(!it_account2->checkmoney()){
        std::cout << "the user has no deposits\n";
        return;
    }

    std::cout << "From which deposit do you want to transfer money?\n";
    it_account1->show_all_deposit();
    std::cin.ignore();
    size_t id_account1;
    std::cin >> id_account1;

    std::cout << "Which deposit do you want to transfer money to?\n";
    it_account2->show_id_deposits();
    size_t id_account2;
    std::cin >> id_account2;

    std::cout << "How much do you want to transfer?: ";
    double sizetransfer;
    std::cin >> sizetransfer;
    

    try{
        it_account1->delete_for_deposit(id_account1, sizetransfer);
        it_account2->add_for_deposit(id_account2, sizetransfer);
    } catch(...){
        std::cout << "Error\n" << std::endl;
    }
}

bool Account::show_id_deposits()
{
    if(deposits.empty()){
        std::cout << "no deposits\n";
        return false;
    }
    for(auto &i : deposits){
        std::cout << i.id << " ";
    }
    std::cout << std::endl;
    return true;
}
