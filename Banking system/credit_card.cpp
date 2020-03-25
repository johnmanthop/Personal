#include <iostream>
#include <memory>
#include "error_codes.h"
#include "credit_card.h"


Credit_Card::Credit_Card(Account* _owner, float _max_withdraw_allowed):
    max_withdraw_allowed(_max_withdraw_allowed),
    withdrawn(0)
{
    owner = _owner;
}


Credit_Card::~Credit_Card()
{  }//Do NOT delete the owner pointer at destruction
    //Since this object does not own it


int Credit_Card::withdraw(float _amount)
{
    if (withdrawn + _amount <= max_withdraw_allowed)
    {
        withdrawn += _amount;
        return owner->withdraw(_amount);
    }
    else
    {
        return CREDIT_CARD_LIMIT_REACHED;
    }
}
