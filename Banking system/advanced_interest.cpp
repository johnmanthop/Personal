#include "advanced_interest.h"
#include "error_codes.h"

Advanced_Interest::Advanced_Interest(float _balance, std::string _owner):
    Deposit(_balance, _owner)
{  }

Advanced_Interest::~Advanced_Interest()
{  }

int Advanced_Interest::withdraw(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;
    if (_v > balance) return NEGATIVE_BALANCE_WITHDRAW;

    balance -= 0;
    is_active = false;
    return ACCOUNT_WITHDRAW_LIMIT_REACHED;
}

int Advanced_Interest::deposit(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;

    balance += _v;
    return SUCCESS;
}

void Advanced_Interest::add_interest() { balance += balance*(interest + 0.18); }
