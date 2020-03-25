#include "basic_personal.h"
#include "basic_credit_card.h"
#include "advanced_credit_card.h"
#include "error_codes.h"



Basic_Personal::Basic_Personal():
    Account()
{  }

Basic_Personal::Basic_Personal(float _balance, std::string _owner):
    Account(_balance, _owner)
{  }

Basic_Personal::~Basic_Personal()
{  }

int Basic_Personal::withdraw(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;
    if (_v > balance) return NEGATIVE_BALANCE_WITHDRAW;

    balance -= _v;
    return SUCCESS;
}

int Basic_Personal::deposit(float _v)
{
    if (_v <= 0) return NEGATIVE_VALUE;

    balance += _v;
    return SUCCESS;
}

void Basic_Personal::add_interest() {  }//Do nothing

void Basic_Personal::add_basic_credit_card()
{
    cr_card_list.push_back(std::make_unique<Basic_Credit_Card>(this));
}
void Basic_Personal::add_advanced_credit_card(float _amount)
{
    cr_card_list.push_back(std::make_unique<Advanced_Credit_Card>(this, _amount));
}


Credit_Card& Basic_Personal::get_credit_card(int _index)
{
    return *(cr_card_list[_index]);
}




