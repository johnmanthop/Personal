#include "saving.h"
#include "error_codes.h"

Saving::Saving(float _balance, std::string _owner):
    Account(_balance, _owner),
    interest(0.02),
    count(0)
{  }//Standard interest

Saving::~Saving()
{  }

int Saving::withdraw(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;
    if (_v > balance) return NEGATIVE_BALANCE_WITHDRAW;

    if (count < 2)
    {
        count++;
        balance -= _v;
        return SUCCESS;
    }
    else if (count == 2)
    {
        is_active = false;
        balance = 0;//Zero the balance at last withdraw
        return ACCOUNT_WITHDRAW_LIMIT_REACHED;
    }
    else
    {
        is_active = false;
        return ACCOUNT_WITHDRAW_LIMIT_REACHED;
    }
}

int Saving::deposit(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;

    balance += _v;
    return SUCCESS;
}

void Saving::add_interest() { balance += balance*interest; }


