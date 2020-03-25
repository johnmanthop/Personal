#include "deposit.h"
#include "error_codes.h"


Deposit::Deposit(float _balance, std::string _owner):
    Saving(_balance, _owner)
{  }

Deposit::~Deposit()
{  }


int Deposit::withdraw(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;
    if (_v > balance) return NEGATIVE_BALANCE_WITHDRAW;

    if (!count)
    {
        count++;
        balance -= _v;
        return SUCCESS;
    }
    else
    {
        balance = 0;
        is_active = false;
        return ACCOUNT_WITHDRAW_LIMIT_REACHED;
    }
}

int Deposit::deposit(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;

    balance += _v;
    return SUCCESS;
}

void Deposit::add_interest() { balance += balance*(interest + 0.08); }//Add more interest
