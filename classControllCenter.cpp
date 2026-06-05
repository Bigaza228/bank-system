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
        if(itforDBALL != itfornew){
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

}

void ControllCenter::interfaceprogram(auto &it_account)
{

}

void ControllCenter::adminmenu()
{

}
