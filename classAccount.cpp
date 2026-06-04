#include "classAccount.h"

void Account::show_all_deposit()
{
    for(const auto &i : deposits){
        std::cout << "id: " << i.id << " , name: " << i.name
        << " , check: " << i.cash_account << std::endl;
    }
}

void Account::show_deposit(size_t &id_deposit)
{
    const auto &it = std::find_if(deposits.begin(), deposits.end(),
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
    const auto &it = std::find_if(deposits.begin(), deposits.end(),
    [id_deposit](Variable_Deposit i_dep){
        return i_dep.id == id_deposit;
    });

    if(it != deposits.end()){
        it->cash_account += summ;
    } else std::cout << "Id not found\n";
}

void Account::delete_deposit(size_t &id_deposit)
{
    const auto &it = std::find_if(deposits.begin(), deposits.end(),
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
            }
            if(it != deposits.begin() + 1){
                deposits[1].cash_account += it->cash_account;
                deposits.erase(it);
            }
        }
    }
}
