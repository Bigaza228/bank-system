#include "classControllCenter.h"

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
    auto itfornew = newaccountDatabase.find(login);

    if(itforDBALL != accountDatabase.end()){
        // itfornew is an iterator into a different container; only check membership
        if(itfornew != newaccountDatabase.end()){
            deleted = true;
        }
        if(itforDBALL->second->checkmoney()){
            std::cout << "The account cannot be deleted because it holds funds.\n";
        } else {
            accountDatabase.erase(itforDBALL);
            if(itfornew != newaccountDatabase.end()){
                newaccountDatabase.erase(itfornew);
            }
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
        clearinterface();
        std::cout << "1. View account information\n";
        std::cout << "2. Show all deposits\n";
        std::cout << "3. View specific deposit: Enter 3 \"id_deposit\"\n";
        std::cout << "4. Create new deposit: Enter 4 \"name\"\n";
        std::cout << "5. Add money to deposit: Enter 5 \"id_deposit\" \"summa\"\n";
        std::cout << "6. Withdraw money from deposit: Enter 6 \"id_deposit\" \"summa\"\n";
        std::cout << "7. Delete deposit: Enter 7 \"id_deposit\"\n";
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
                double summ = std::stoi(arg3);
                it_account->add_for_deposit(id_dep, summ);
            } catch(...){
                std::cout << "It didn't work; please enter it again.\n";
            }
        } else if(arg1 == "6" && !arg2.empty() && !arg3.empty()){
            try{
                size_t id_dep = std::stoi(arg2);
                double summ = std::stoi(arg3);
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
        } else if(arg1 == "0"){
            std::cout << "You have logged out of your account.\n";
            return;
        }
    }
}

void ControllCenter::adminmenu()
{

}
