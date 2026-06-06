#include "classAccount.h"

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
        if(it->cash_account > summ){
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

    if(it != deposits.end()){
        if(SIZEdeposit == 1 && it->cash_account > 0){
            std::cout << "You can't delete a deposit if it's the only one and there's money in it.\n";
            
        } else {
            if(it != deposits.begin()){
                deposits[0].cash_account += it->cash_account;
                deposits.erase(it);
                --SIZEdeposit;
                return;
            }
            if(it != deposits.begin() + 1){
                deposits[1].cash_account += it->cash_account;
                deposits.erase(it);
                --SIZEdeposit, --id_new_dep;
            }
        }
    }
}

bool Account::checkmoney()
{
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
    if(SIZEdeposit <= 3){
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