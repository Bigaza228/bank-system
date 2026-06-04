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
    if(id_deposit > deposits.size()){
        std::cout << "Id not found\n";
        return;
    }
    std::cout << "id: " << deposits[id_deposit].id << " , name: "
    << deposits[id_deposit].name
    << " , check: " << deposits[id_deposit].cash_account << std::endl;
}

void Account::create_new_deposit()
{
}

void Account::add_for_deposit(size_t &id_deposit)
{
}

void Account::delete_deposit(size_t &id_deposit)
{
}
