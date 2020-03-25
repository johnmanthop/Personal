#include "account.h"
#include <string>

Account::Account()
{
    balance = 0;
    owner = std::string();
    is_active = true;
    id = rand()%9000 + 1000;
}

Account::Account(float _balance, std::string _owner)
{
    balance = _balance;
    owner = _owner;
    is_active = true;
}

Account::~Account()
{  }


